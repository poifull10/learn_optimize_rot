import numpy as np
import scipy.spatial.transform.rotation as R
import random
from typing import Tuple, List


def generateData(N: int, r: float,
                 t: List[float]) -> Tuple[np.array, np.array]:
    src = np.zeros((N, 3))
    dst = np.zeros((N, 3))

    thetas = 2 * np.pi * np.random.rand(N * 3).reshape(N, -1)
    rotation = R.Rotation.from_rotvec(t).as_matrix()

    for i in range(N):
        theta = thetas[i]
        print(theta)
        rMat = R.Rotation.from_rotvec(theta).as_matrix()
        t = r * np.array([1, 0, 0])
        src[i] = rMat @ t
        dst[i] = rotation @ rMat @ t

    return src, dst


if __name__ == "__main__":
    src, dst = generateData(3, 10.0, [-np.pi / 4, np.pi / 3, np.pi / 10])
    np.savetxt('src.csv', src)
    np.savetxt('dst.csv', dst)
