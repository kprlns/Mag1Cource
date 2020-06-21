from metric.Precision import Precision
from metric.Dcg import Dcg
from metric.Ndcg import Ndcg
from metric.Err import Err

metric1 = Precision()
metric2 = Dcg()
metric3 = Ndcg()
metric4 = Err()

level = 5
print('Precision')
lines = open("labl2_stats/snippet.txt").readlines()
print('--\n' + str(metric1.evaluate(lines, level)))
print('------')

print('Dcg')
lines = open("labl2_stats/snippet.txt").readlines()
print('--\n' + str(metric2.evaluate(lines, level)))
print('------')

print('Ndcg')
lines = open("labl2_stats/snippet.txt").readlines()
print('--\n' + str(metric3.evaluate(lines, level)))
print('------')

print('Err')
lines = open("labl2_stats/snippet.txt").readlines()
print('--\n' + str(metric4.evaluate(lines, level)))
print('------')

# lines = open("labl2_stats/google.txt").readlines()
# print('--\n' + str(metric.evaluate(lines, level)))
#
#
# print('------')
#
# lines = open("labl2_stats/wikipedia.txt").readlines()
# print('--\n' + str(metric.evaluate(lines, level)))
#
# print('------')
#
# lines = open("labl2_stats/my.txt").readlines()
# print('--\n' + str(metric.evaluate(lines, level)))
#
# print('------')
#
# lines = open("labl2_stats/boolean.txt").readlines()
# print('--\n' + str(metric.evaluate(lines, level)))
