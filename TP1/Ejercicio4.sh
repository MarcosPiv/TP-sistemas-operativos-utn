#!/bin/bash
#ingreso de datos
read -p "Ingresa el nro1 --> " num1
read -p "Ingresa el nro2 -> " num2

#realiza la operacion correspondiente
case "$1" in 
	suma) 
		resultado=$((num1 + num2))
		operacion="+";;
	resta)
		resultado=$((num1 - num2))
		operacion="-";;
	multiplicar) 
		resultado=$((num1 * num2))
		operacion="*";;
	dividir) 
		if [ "$num2" -eq 0 ]; then
			echo "No se puede dividir por cero"
			exit 1
		fi
		resultado=$((num1 / num2))
		operacion="/";;
esac

#imprimir resultado
echo "$num1 $operacion $num2 = $resultado"
