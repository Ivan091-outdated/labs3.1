import matplotlib.pyplot as plt
import numpy as np
from latextable import draw_latex
from scipy import stats
from texttable import Texttable

matrix = np.asarray([
    [4, 8, 6, 0, 0, 0, 0, 0],
    [0, 7, 14, 8, 0, 0, 0, 0],
    [0, 0, 0, 15, 13, 7, 0, 0],
    [0, 0, 0, 9, 18, 9, 6, 0],
    [0, 0, 0, 0, 0, 9, 5, 1],
    [0, 0, 0, 0, 0, 0, 6, 3],
])

stepX = 7.5
stepY = 1.2


def task():
    n = np.sum(matrix)
    xAxis = create_axis(12.5, stepX, 6)
    yAxis = create_axis(18.5, stepY, 8)
    Ui = np.array((xAxis - np.average(xAxis)) / stepX)
    Vj = np.array((yAxis - np.average(yAxis)) / stepY)
    Ni = np.array(matrix.sum(1)).flatten()
    Mj = np.array(matrix.sum(0)).flatten()
    NiUi = np.array(Ni * Ui)
    MjVj = np.array(Mj * Vj)

    sumNijVj = np.zeros(matrix.shape[0])
    for i in range(matrix.shape[0]):
        for j in range(matrix.shape[1]):
            sumNijVj[i] += Vj[j] * matrix.item((i, j))

    sumNijUi = np.zeros(matrix.shape[1])
    for i in range(matrix.shape[0]):
        for j in range(matrix.shape[1]):
            sumNijUi[j] += Ui[i] * matrix.item((i, j))

    MjVjpow2 = np.array(Mj * (Vj ** 2))
    NiUipow2 = np.array(Ni * (Ui ** 2))

    UiSumNijVj = np.array(sumNijVj * Ui)
    ViSumNijUi = np.array(sumNijUi * Vj)

    barU = NiUi.sum() / n
    barV = MjVj.sum() / n

    barX = np.average(xAxis) + stepX * barU
    barY = np.average(yAxis) + stepY * barV

    sigmaU = (NiUipow2.sum() / n - barU ** 2) ** 0.5
    sigmaV = (MjVjpow2.sum() / n - barV ** 2) ** 0.5

    sigmaX = sigmaU * stepX
    sigmaY = sigmaV * stepY

    rSquare = 1 / (sigmaU * sigmaV) * (UiSumNijVj.sum() / n - barU * barV)
    r = rSquare ** 0.5

    barYs = np.array([(matrix[i:i + 1] * yAxis).sum() / matrix[i:i + 1].sum() for i in range(matrix.shape[0])])
    barXs = np.array(
        [(matrix[:, i:i + 1].flatten() * xAxis).sum() / matrix[:, i:i + 1].sum() for i in range(matrix.shape[1])])

    sigmaBarX = ((1 / n) * np.sum(Mj * (barXs - barX) ** 2)) ** 0.5
    sigmaBarY = ((1 / n) * np.sum(Ni * (barYs - barY) ** 2)) ** 0.5

    NuyYtoX = sigmaBarY / sigmaY
    NuyXtoY = sigmaBarX / sigmaX

    XtoYRegressionA = r * sigmaX / sigmaY
    YtoXRegressionB = r * sigmaY / sigmaX

    B0 = YtoXRegressionB
    B1 = barY - barX * YtoXRegressionB
    a = 0.05
    t = 1.98
    sigmaYX = (n * sigmaY ** 2 * (1 - rSquare) / (n - 2)) ** 0.5
    bigSquareRoot = (1 / sigmaX) * ((sigmaX ** 2 + barX ** 2) / n) ** 0.5
    bigSquareRoot2 = 1 / (sigmaX * n ** 0.5)
    B0Interval = (B0 - t * sigmaYX * bigSquareRoot, B0 + t * sigmaYX * bigSquareRoot)
    B1Interval = (B1 - t * sigmaYX * bigSquareRoot2, B1 + t * sigmaYX * bigSquareRoot)

    TWatch = r * ((n - 2) / (1 - rSquare)) ** 0.5

    TCrit = 1.984

    print('barU', barU)
    print('barV', barV)
    print('barX', barX)
    print('barY', barY)
    print('sigmaU', sigmaU)
    print('sigmaV', sigmaV)
    print('sigmaX', sigmaX)
    print('sigmaY', sigmaY)
    print('r', r)
    print('rSquare', rSquare)
    print('sigmaBarX', sigmaBarX)
    print('sigmaBarY', sigmaBarY)
    print('NuyYtoX', NuyYtoX)
    print('NuyXtoY', NuyXtoY)
    print('sigmaBarX', sigmaBarX)
    print('sigmaBarY', sigmaBarY)
    print('XtoYRegressionA', XtoYRegressionA)
    print('YtoXRegressionB', YtoXRegressionB)
    print('B0', B0)
    print('B1', B1)
    print('t', t)
    print('sigmaYX', sigmaYX)
    print('bigSquareRoot', bigSquareRoot)
    print('bigSquareRoot2', bigSquareRoot2)
    print('B0Interval', B0Interval)
    print('B1Interval', B1Interval)
    print('Twatch', TWatch)
    print('TCrit', TCrit, TWatch < TCrit)

    def draw_correlation_field():
        plt.figure(dpi=200)
        plt.title('Корреляционное поле')

        x = np.linspace(0, 100, 2)

        y1 = (x - barX) * YtoXRegressionB + barY
        plt.plot(x, y1)

        y2 = (x - barX) / XtoYRegressionA + barY
        plt.plot(x, y2)

        plt.savefig("gr31.png")

    def print_tables():
        table = Texttable()
        table.set_cols_align(["l"] * (matrix.shape[1] + 2))
        table.add_row(['~', '~', *yAxis])
        table.add_row(['~', '~', *Vj])
        for i in range(Ui.size):
            table.add_row(
                [xAxis[i], Ui[i], *matrix[i]])
        print(draw_latex(table))

        table = Texttable()
        table.set_cols_align(["l"] * 5)
        table.add_row(['n_{i}', 'n_{i}u_{i}', 'sum', 'a', 'a'])
        for i in range(Ui.size):
            table.add_row(
                [Ni[i], NiUi[i], sumNijVj[i], NiUipow2[i], UiSumNijVj[i]]
            )
        print(draw_latex(table))

        table = Texttable()
        table.set_cols_align(["l"] * 5)
        table.add_row(['m_{i}', 'm_{i}v_{i}', 'sum', 'a', 'a'])
        for i in range(Vj.size):
            table.add_row(
                [Vj[i], MjVj[i], sumNijUi[i], MjVjpow2[i], ViSumNijUi[i]]
            )
        print(draw_latex(table))

        table = Texttable()
        table.set_cols_align(["l"] * (xAxis.size + 1))
        table.add_row(['$X$', *xAxis])
        table.add_row(['$\\bar{x_y}$', *barYs])
        print(draw_latex(table))

        table = Texttable()
        table.set_cols_align(["l"] * (yAxis.size + 1))
        table.add_row(['$Y$', *yAxis])
        table.add_row(['$\\bar{y_x}$', *barXs])
        print(draw_latex(table))

    print_tables()

def create_axis(start: float, step: float, count: int) -> np.ndarray:
    result = np.zeros(count)
    for i in range(count):
        result[i] = start + step * i
    return result

if __name__ == "__main__":
    task()
