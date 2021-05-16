from scipy import *
from scipy import stats

from data import initArray
import matplotlib.pyplot as plt
import numpy as np
from latextable import *


def task():
    n = initArray.size
    step = (initArray.max() - initArray.min()) / (1 + 3.322 * np.log(initArray.size))
    step = np.round(step, 3)
    intervals = create_intervals(step)
    intervalMiddles = create_interval_middles(intervals)
    frequencies = create_frequencies(intervals)
    relativeFrequencies = np.array([x / initArray.size for x in frequencies])
    frequenciesOfDensities = np.array([x / step for x in frequencies])
    distributionFunction = create_distribution_function(relativeFrequencies)
    Exini = np.sum(np.array([intervalMiddles[i] * frequencies[i] for i in range(intervalMiddles.size)]))
    Exi2ni = np.sum(np.array([(intervalMiddles[i] ** 2) * frequencies[i] for i in range(intervalMiddles.size)]))
    En = np.sum(frequencies)
    X = Exini / En
    D = (Exi2ni / En) - (X ** 2)
    sigma = D ** 0.5
    S2 = En / (En - 1) * D
    S = S2 ** 0.5

    a = 0.05

    t = 1.975
    alpha = (X - t * S / (n ** 0.5), X + t * S / (n ** 0.5))
    print("Доверительный интервал alpha:", alpha)
    delta = (np.sqrt((n - 1) / stats.chi2.ppf((1 - a)/2, df=n)) * S, np.sqrt((n - 1) / stats.chi2.ppf(a / 2, df=n)) * S)
    print("Доверительный интервал delta:", delta)

    laplassianAplphas = np.array([(intervals[i] - X) / sigma for i in range(intervals.size)])
    laplassians = np.array(
        [laplas_integral(laplassianAplphas[i]) - laplas_integral(laplassianAplphas[i - 1])
         for i in range(1, intervals.size)])

    npi = np.array([x * n for x in laplassians])
    merge_config = create_merge_config(5, frequencies)
    mergedFrequencies = merge_limits(merge_config, frequencies)
    mergedNpi = merge_limits(merge_config, npi)

    niNpiDeltas = np.array([mergedNpi[i] - mergedFrequencies[i] for i in range(mergedNpi.size)])
    niNpiSquaredDeltas = np.array([(mergedNpi[i] - mergedFrequencies[i]) ** 2 for i in range(mergedNpi.size)])
    niNpiSquaredDividedDeltas = np.array([niNpiSquaredDeltas[i] / mergedNpi[i] for i in range(mergedNpi.size)])

    xSquaredWatched = np.sum(niNpiSquaredDividedDeltas)
    k = niNpiDeltas.size - 2 - 1

    print("k =", k)
    X2Crit = stats.chi2.ppf(1 - a, df=k)
    print("X^2Watched =", xSquaredWatched)
    print("X^2Crit =", X2Crit, xSquaredWatched < X2Crit)

    hypotheticalFunction = np.array([laplas_integral(laplassianAplphas[i]) for i in range(1, laplassianAplphas.size)])
    hypotheticalDistributionFunctionDifferences = np.array(
        [np.abs(distributionFunction[i] - hypotheticalFunction[i])
         for i in range(distributionFunction.size)])
    maxDifference = np.max(hypotheticalDistributionFunctionDifferences)
    print(hypotheticalFunction)
    print(distributionFunction)

    lambdaWatched = (n ** 0.5) * maxDifference
    print("lambdaWatched =", lambdaWatched)
    lambdaCrit = 1.36
    print("lambdaCrit =", lambdaCrit, lambdaWatched < lambdaCrit)

    print(X - 3*S, X + 3 * S)

    def print_values1():
        print(f"Xв = {X}")
        print(f"Dв = {D}")
        print(f"Dв ^ 0.5 = {D ** 0.5}")
        print(f"S ^ 2 = {S2}")
        print(f"S = {S}")

    def draw_graphs1():
        plt.figure(dpi=200)
        plt.bar(intervalMiddles, frequenciesOfDensities, width=step, edgecolor="black", color='white')
        plt.title('Гистограмма частот')
        plt.savefig("gr11.png")

        plt.figure(dpi=200)
        plt.plot(intervalMiddles, frequencies)
        plt.title('Полигон частот')
        plt.savefig("gr12.png")

        plt.figure(dpi=200)
        x = np.insert(intervalMiddles, 0, [intervalMiddles[0] - 100])
        x = np.append(x, [intervalMiddles[-1] + 100])
        y = np.insert(distributionFunction, 0, [0])
        plt.title('Эмпирическая функция распределения')
        for i in range(1, y.size):
            plt.arrow(x[i + 1], y[i], x[i] - x[i + 1] + 20, 0, head_width=0.01, head_length=20)
        plt.arrow(x[1], y[0], x[0] - x[1], 0)
        plt.savefig("gr13.png")

    def draw_graphs2():
        plt.figure(dpi=200)
        plt.title('Плотность вероятности нормального распределения')
        x = np.linspace(X - 3 * sigma, X + 3 * sigma, 100)
        plt.plot(x, stats.norm.pdf(x, X, sigma))
        plt.savefig("gr21.png")

        plt.figure(dpi=200)
        plt.title('Теоретическая интегральная функция распределения')
        plt.plot(intervalMiddles, hypotheticalFunction)
        plt.savefig("gr22.png")

    def print_tables1():
        table = Texttable()
        table.set_cols_align(["l", "l", "l", "l", "l", "l", "l"])
        table.header(['start', 'end', 'ni', 'Wi', 'Wi / h', 'F\'(x)', 'xi'])
        for i in range(intervalMiddles.size):
            table.add_row(
                [intervals[i], intervals[i + 1], frequencies[i], relativeFrequencies[i],
                 frequenciesOfDensities[i], distributionFunction[i], intervalMiddles[i]])
        print(draw_latex(table))

    def print_tables2():
        table = Texttable()
        table.set_cols_align(["l", "l", "l", "l"])
        table.header(['start', 'end', 'ni', 'n\' = npi'])
        for i in range(intervalMiddles.size):
            table.add_row(
                [intervals[i], intervals[i + 1], frequencies[i], npi[i]])
        print(draw_latex(table))

        table = Texttable()
        table.set_cols_align(["l", "l", "l"])
        table.header(['Частоты', 'Выравнивающие частоты', '(n\'i - ni) / n\'i'])
        for i in range(mergedFrequencies.size):
            table.add_row(
                [mergedFrequencies[i], mergedNpi[i], niNpiSquaredDividedDeltas[i]])
        print(draw_latex(table))

        table = Texttable()
        table.set_cols_align(["l", "l", "l", "l"])
        table.header(
            ['Частоты', 'Эмпирическая функция распределения', 'Теоретическая функция распределения', 'Разности'])
        for i in range(intervalMiddles.size):
            table.add_row(
                [frequencies[i], distributionFunction[i], hypotheticalFunction[i],
                 hypotheticalDistributionFunctionDifferences[i]])
        print(draw_latex(table))

    print_values1()
    print_tables1()
    draw_graphs1()
    draw_graphs2()
    print_tables2()


def create_merge_config(count: int, array: np.ndarray) -> []:
    left = 0
    right = 0
    acc = 0
    for i in range(array.size):
        acc += array[i]
        if acc >= count:
            left = i + 1
            break
    acc = 0
    for i in reversed(range(array.size)):
        acc += array[i]
        if acc >= count:
            right = i
            break
    return [left, right]


def merge_limits(config: [], arr: np.ndarray):
    arr = np.split(arr, config)
    return np.array([np.sum(arr[0]), *arr[1], np.sum(arr[2])])


def laplas_integral(x: float) -> float:
    return stats.norm.cdf(x)


def gaussian(x: float) -> float:
    return 1 / np.sqrt(2 * np.pi) * np.exp(-x ** 2 / 2)


def create_frequencies(intervals: np.ndarray) -> np.ndarray:
    frequencies = np.zeros(intervals.size - 1)
    for i in range(intervals.size - 1):
        if i == intervals.size - 1:
            ni = np.count_nonzero((initArray >= intervals[i]) & (initArray <= intervals[i + 1]))
        else:
            ni = np.count_nonzero((initArray >= intervals[i]) & (initArray < intervals[i + 1]))
        frequencies[i] = ni
    return frequencies


def create_intervals(step: float) -> np.ndarray:
    intervals = np.array([initArray.min()])
    while intervals.max() < initArray.max():
        intervals = np.append(intervals, intervals.max() + step)
    return intervals


def create_interval_middles(intervals: np.ndarray) -> np.ndarray:
    intervalMiddles = np.zeros(intervals.size - 1)
    for i in range(intervals.size - 1):
        intervalMiddles[i] = (intervals[i] + intervals[i + 1]) / 2
    return intervalMiddles


def create_distribution_function(relative_frequencies: np.ndarray) -> np.ndarray:
    distributionFunction = np.zeros(relative_frequencies.size)
    distributionFunction[0] = relative_frequencies[0]
    for i in range(1, relative_frequencies.size):
        distributionFunction[i] = distributionFunction[i - 1] + relative_frequencies[i]
    return distributionFunction


if __name__ == "__main__":
    task()
