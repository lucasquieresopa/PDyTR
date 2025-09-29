echo "#### Cliente : Ejecutando cliente4.sh ####"

cd /home/pdytr/punto5/escenario-4
gcc -o cliente client-full.c

while true; do
    ./cliente 192.168.56.14 6904
    rc=$?
    if [ $rc -eq 0 ]; then
        echo "#### Cliente : Escenario 4, conexión exitosa ####"
        break
    fi
    echo "CLIENTE: fallo al conectar. PERO NO ME RENDIRE! ESA CONEXION SE HARA DEMONIOS"
    sleep 1
done
