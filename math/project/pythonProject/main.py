import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline, BSpline
import numpy as np


def print_hi(name):
    x = np.array([1, 2, 3, 4, 6, 12, 24])
    y = np.array([1.1, 0.656305, 0.473213, 0.361699, 0.259871, 0.182186, 0.17634])
    xNew = np.linspace(x.min(), x.max(), 300)
    spl = make_interp_spline(x, y, k=1)
    plt.figure(dpi=200)
    plt.plot(xNew, spl(xNew))
    plt.title('Зависимость времени выполнения от количества потоков.')
    plt.savefig("gr11.png")

if __name__ == '__main__':
    print_hi('PyCharm')
