import numpy

from metric.Metric import MetricInterface
from math import log2


class Ndcg(MetricInterface):
    def __init__(self):
        pass

    @staticmethod
    def __parse(value: str):
        return numpy.array(value.split(',')).astype(numpy.int)

    @staticmethod
    def __log_or_else_1(val):
        log: float = 1.
        if val > 0:
            log = log2(val + 1)
        return log

    @classmethod
    def __idgg(cls, level: int):
        result: float = 0
        for i in range(level):
            result += 1 / cls.__log_or_else_1(i)
        return result

    @classmethod
    def evaluate_one(cls, values, level: int):
        result: float = 0
        for i in range(min(len(values), level)):
            log = cls.__log_or_else_1(i)
            if values[i] != 0:
                result += values[i] / log
        return result

    def evaluate(self, values, level: int, separator: str = '.', print_res: bool = True):
        sum_cnt: float = 0
        result = numpy.empty([len(values)])
        for i in range(len(values)):
            parsed = self.__parse(values[i])
            result[i] = self.evaluate_one(parsed, level) / self.__idgg(min(level, len(parsed)))
            sum_cnt += result[i]

        if print_res is True:
            for i in range(len(result)):
                print(str(result[i]).replace('.', separator))
        return sum_cnt / len(values)
