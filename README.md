# PDyTR

## Posibles errores y posibles soluciones

### Error porque la máquina está usando kvm en modo root
Ejecutar en la terminal:
```bash
sudo rmmod kvm_intel
sudo rmmod kvm
```

### No se ejecutan los scripts del punto 4
Ejecutar en la terminal:
```bash
sudo chmod +x ejecutar-todo.sh
sudo chmod +x script.sh
```

### Error porque está mal apuntada la direccion del default gateway de la maquina del punto4-b