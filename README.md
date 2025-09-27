# PDyTR

## Posibles errores y posibles soluciones

### Error porque la máquina está usando kvm en modo root
Ejecutar en la terminal:
```bash
sudo rmmod kvm_intel
sudo rmmod kvm
```

### Error porque está mal apuntada la direccion del default gateway de la maquina del punto4-b