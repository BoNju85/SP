#!/bin/bash
git clone https://github.com/SystemProgrammingatNTU/SP16MP1-B04902025.git b04902025
cd b04902025
make
rm -rf server
rm -rf client
mkdir server
mkdir client
echo abcdefg >> client/a.txt
echo update a.txt > input.txt
echo exit >> input.txt
ulimit -v 65536 # set memory limit: 65536 KB = 64 MB
timeout 120s ./change_count < input.txt
