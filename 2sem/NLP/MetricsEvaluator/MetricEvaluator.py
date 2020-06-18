from metric.Precision import Precision
from metric.Dcg import Dcg
from metric.Ndcg import Ndcg
from metric.Err import Err

metric = Err()
level = 5

lines = open("labl2_stats/yandex.txt").readlines()
print('--\n' + str(metric.evaluate(lines, level)))
print('------')

lines = open("labl2_stats/google.txt").readlines()
print('--\n' + str(metric.evaluate(lines, level)))


print('------')

lines = open("labl2_stats/wikipedia.txt").readlines()
print('--\n' + str(metric.evaluate(lines, level)))

print('------')

lines = open("labl2_stats/my.txt").readlines()
print('--\n' + str(metric.evaluate(lines, level)))
