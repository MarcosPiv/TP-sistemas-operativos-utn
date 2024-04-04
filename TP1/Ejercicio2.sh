#!/bin/bash

if [ -d "$1" ]; then 

	echo "Total directorio: $(du -s "$1" | cut -f1)"	

else 

	echo "$1 no es un directorio valido, ingrese uno correcto:"

	read nuevoDirectorio

	if [ -d "$nuevoDirectorio" ]; then 

		echo "Total directorio: $(du -s "$nuevoDirectorio" | cut -f1)"	

	else 

		echo "$1 no es un directorio valido"

	fi

fi
