import open3d as o3d
import scipy.spatial.transform.rotation as R
import numpy as np
from pathlib import Path
import argparse

parser = argparse.ArgumentParser('')
parser.add_argument('dataDir', type=Path)
parser.add_argument('outputDir', type=Path)
args = parser.parse_args()

outputDir = args.outputDir
dataDir = args.dataDir
initCsv = outputDir / 'init.csv'
optCsv = outputDir / 'opt.csv'
srcCsv = dataDir / 'src.csv'
dstCsv = dataDir / 'dst.csv'

pcd_dst = o3d.geometry.PointCloud()
pcd_dst.points = o3d.utility.Vector3dVector(np.loadtxt(dstCsv.open()))
pcd_dst.paint_uniform_color([1, 0, 0])

R_init = R.Rotation.from_quat(np.loadtxt(initCsv.open())).as_dcm()
R_opt = R.Rotation.from_quat(np.loadtxt(optCsv.open())).as_dcm()

T_init = np.eye(4)
T_init[0:3, 0:3] = R_init

T_opt = np.eye(4)
T_opt[0:3, 0:3] = R_opt

print(T_init)
print(T_opt)

pcd_src = o3d.geometry.PointCloud()
pcd_src.points = o3d.utility.Vector3dVector(np.loadtxt(srcCsv.open()))
pcd_init = pcd_src.transform(T_init)
pcd_init.paint_uniform_color([0, 1, 0])

pcd_src = o3d.geometry.PointCloud()
pcd_src.points = o3d.utility.Vector3dVector(np.loadtxt(srcCsv.open()))
pcd_opt = pcd_src.transform(T_opt)
pcd_opt.paint_uniform_color([0, 0, 1])

o3d.visualization.draw_geometries([pcd_init, pcd_opt, pcd_dst])
