import subprocess
import os

out = subprocess.Popen('./search_bin /home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/queries.txt 3 1',
           stdout=subprocess.PIPE,
           stderr=subprocess.STDOUT, shell=True)

print(out.communicate()[0].decode('utf-8'))
print('---')
