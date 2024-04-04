#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Uso: $0 <directorio>"
    exit 1
fi

directorio="$1"
dir1="$directorio/dir1"
dir2="$directorio/dir2"
archivo1="ordenado_tp1_2023_dir1"
archivo2="ordenado_tp1_2023_dir2"

# Verificar si el directorio de salida existe y crearlo si no
if [ ! -d "$directorio" ]; then
    mkdir "$directorio"
fi

# Crear los directorios dir1 y dir2
mkdir "$dir1"
mkdir "$dir2"

# Obtener las 10 primeras líneas del archivo /etc/passwd y ordenarlas en orden inverso
head -n 10 /etc/passwd | tac > "$dir1/$archivo1"

# Obtener las 5 últimas líneas del archivo /etc/passwd y ordenarlas en orden inverso
tail -n 5 /etc/passwd | tac > "$dir2/$archivo2"

# Contar y mostrar cuántas líneas tiene el archivo /etc/passwd
lineas_passwd=$(wc -l < /etc/passwd)
echo "$lineas_passwd /etc/passwd"
