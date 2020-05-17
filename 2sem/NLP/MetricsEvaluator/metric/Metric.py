import numpy


class MetricInterface:

    def evaluate(self, values, level: int, separator: str = '.', print_res: bool = True):
        pass
