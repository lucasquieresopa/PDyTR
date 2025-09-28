#!/bin/bash

cd /home/pdytr/punto3
gcc -o cliente client3.c

while true; do
    ./cliente 192.168.56.11 6902
    rc=$?
    if [ $rc -eq 0 ]; then
        echo "CLIENTE: conexión/ejecución exitosa."
        break
    fi
    echo "CLIENTE: fallo al conectar (exit $rc). Reintentando en 1s..."
    sleep 1
done
