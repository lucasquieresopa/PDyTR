#!/bin/bash

echo "PUNTO 3: SERVIDOR" 
cd /opt/pdytr/punto3
gcc -o servidor server3.c
./servidor 6902 
