import numpy as np
import scipy.spatial.transform.rotation as R
import random
from typing import Tuple


def generateData(N: int, r: float, t: float) -> Tuple[np.array, np.array]:
    src = np.zeros((N, 2))
    dst = np.zeros((N, 2))

    thetas = np.random.rand(N) * 2 * np.pi

    for i in range(N):
        theta = thetas[i]
        src[i] = r * np.array([np.cos(theta), np.sin(theta)])
        dst[i] = r * np.array([np.cos(theta + t), np.sin(theta + t)])

    return src, dst


if __name__ == "__main__":
    src, dst = generateData(3, 10.0, np.pi / 3)
    np.savetxt('src.csv', src)
    np.savetxt('dst.csv', dst)
