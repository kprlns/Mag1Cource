import subprocess
import os

out = subprocess.Popen('./a.sh',
           stdout=subprocess.PIPE,
           stderr=subprocess.STDOUT, shell=True)

print(out.communicate()[0].decode('utf-8'))
print('---')
