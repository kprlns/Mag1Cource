from metric.Metric import MetricInterface
import numpy


class Precision(MetricInterface):
    def __init__(self):
        pass

    @staticmethod
    def __parse(value: str):
        return numpy.array(value.split(',')).astype(numpy.int)

    def evaluate(self, values, level: int, separator: str = '.', print_res: bool = True):
        positive_cnt: int = 0
        all_cnt: int = 0
        for value in values:
            parsed = self.__parse(value)
            for i in range(min(level, len(parsed))):
                all_cnt += 1
                positive_cnt += parsed[i]
        if print_res is True:
            print(positive_cnt)
            print(all_cnt)
        return float(positive_cnt) / float(all_cnt)
