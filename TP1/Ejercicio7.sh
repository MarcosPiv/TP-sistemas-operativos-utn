#!/bin/bash

comando="$1"

man "$comando" | col -b > manfile.txt

#filtar lineas que comienzan con vocales y numeros, incluidos los tabuladores y espacios
grep -P "^[ \t]*[AEIOUaeiou]" manfile.txt > vocales.txt
grep -P "^[ \t]*[0-9]" manfile.txt > numeros.txt

#funcion para mostrar la informacion
mostrar_informacion() {
	archivo="$1"
	nombre=$(basename "$archivo")
	lineas=$(wc -l < "$archivo")
	palabras=$(wc -w < "$archivo")
	caracteres=$(wc -m < "$archivo")
	echo "Archivo: $nombre"
	echo "Lineas: $lineas $nombre"
	echo "Palabras: $palabras $nombre"
	echo "Caracteres: $caracteres $nombre"
	}

#muestra la informacion de los archivos generados
mostrar_informacion "manfile.txt"
if [ -s "vocales.txt" ]; then
	mostrar_informacion "vocales.txt"
	echo "Archivo contiene vocales"
fi
if [ -s "numeros.txt" ]; then 
	mostrar_informacion "numeros.txt"
	echo "Archivo contiene numeros"
fi

#eliminar archivos temporales
rm manfile.txt
