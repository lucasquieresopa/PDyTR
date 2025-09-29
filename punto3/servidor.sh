#!/bin/bash

echo "PUNTO 3: SERVIDOR"
cd /opt/pdytr/punto3
gcc -o servidor server3.c
nohup ./servidor 6902 > /home/vagrant/servidor_6902.log 2>&1 &
