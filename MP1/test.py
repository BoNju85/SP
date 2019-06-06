#!/usr/bin/env python3

import os
import shutil
import tempfile
import time

from subprocess import check_call, Popen, PIPE


check_call(['make'])

shutil.rmtree('client', ignore_errors=True)
shutil.rmtree('server', ignore_errors=True)

os.mkdir('client')
os.mkdir('server')

try:
    command = 'ulimit -v 65536; timeout 120s ./change_count'
    process = Popen(command, stdin=PIPE, stdout=PIPE, shell='/bin/bash')

    with tempfile.NamedTemporaryFile(mode='a', dir='client') as f:
        base = os.path.basename(f.name)
        update_command = 'update {}\n'.format(base)
        f.write(('a'*(1024*1024*100-1)+'\n'))
        f.flush()
        for i in range(10):
            process.stdin.write(update_command.encode('utf-8'))
            process.stdin.flush()
            add, delete = map(int, process.stdout.readline().split())
            print(add, delete)
            if (add != 1 and i == 0) or (add != 0 and i > 0) or (delete != 0):
                raise Exception("Wrong Answer")
            time.sleep(5)

    process.stdin.write('exit\n'.encode('utf-8'))
    process.stdin.flush()
    process.terminate()
finally:
    shutil.rmtree('client', ignore_errors=True)
    shutil.rmtree('server', ignore_errors=True)
