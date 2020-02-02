import numpy as np
import open3d as o3d
import scipy.spatial.transform.rotation as R

src = np.loadtxt('data/src.csv')
dst = np.loadtxt('data/dst.csv')

# print(src)
# print(dst)

src_pcd = o3d.geometry.PointCloud()
src_pcd.points = o3d.utility.Vector3dVector(src)
dst_pcd = o3d.geometry.PointCloud()
dst_pcd.points = o3d.utility.Vector3dVector(dst)

src_pcd.paint_uniform_color([1, 0, 0])
dst_pcd.paint_uniform_color([0, 0, 1])

corres = o3d.utility.Vector2iVector()
for i in range(len(src)):
    corres.append(np.array([i, i]))

TE = o3d.registration.TransformationEstimationPointToPoint()
T = TE.compute_transformation(src_pcd, dst_pcd, corres)
# print(T)
# print(R.Rotation.from_dcm(T[0:3, 0:3]).as_quat())
quat = R.Rotation.from_dcm(T[0:3, 0:3]).as_quat()
np.savetxt('answer.csv', quat)
o3d.visualization.draw_geometries([src_pcd.transform(T), dst_pcd])


