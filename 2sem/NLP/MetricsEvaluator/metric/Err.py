from metric.Metric import MetricInterface
import numpy


class Err(MetricInterface):
    def __init__(self):
        pass

    @staticmethod
    def __parse(value: str):
        return numpy.array(value.split(',')).astype(numpy.int)

    @staticmethod
    def evaluate_one(values, level):
        res: float = 0
        val_sum = 0
        for i in range(min(level, len(values))):
            val_sum += values[i]

        if val_sum == 0:
            return 0
        values = values / val_sum

        values = values / sum(values)
        for i in range(min(level, len(values))):
            res += values[i] / (i + 1)
        return res

    def evaluate(self, values, level: int, separator: str = '.', print_res: bool = True):
        res: float = 0
        result = numpy.empty([len(values)])
        for i in range(len(values)):
            parsed = self.__parse(values[i])
            result[i] = self.evaluate_one(parsed, level)
            res += result[i]

        if print_res is True:
            for i in range(len(result)):
                print(str(result[i]).replace('.', separator))
        return res / len(values)
