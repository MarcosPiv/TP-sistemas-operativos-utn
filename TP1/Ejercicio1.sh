#!/bin/bash

tiempoRestante=$(expr 365 - $(date +"%j"))


echo "Hola $1, Ud. esta registrado como usuario $(whoami)!"
echo "Hoy es $(date +"%A"), $(date +"%d") de $(date +"%B") de $(date +"%Y")."
echo "Faltan $tiempoRestante dias para que termine el anio $(date +"%Y")."
echo "Si hoy fuera $(date +"%d/%m/%Y"), faltarian $tiempoRestante para que termine el anio $(date +"%Y")."
