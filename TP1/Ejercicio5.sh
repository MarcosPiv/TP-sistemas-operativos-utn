#!/bin/bash

#mostrar procesos activos antes de iniciar la busqueda
ps

#realiza la busqueda en segundo plano
echo "Se esta generando una lista de archivos que comienzan con c"
find / -type f -iname "c*" > $1 &

#Obtiene el ID del proceso de busqueda en segundo plano
pid_buscador=$(pidof find)

#muestra procesos activos
ps 

#solicita al usuario el ID
echo "Ingrese el ID del proceso de busqueda de archivos que inician con la letra c:"
read pid_usuario

#verifica que el ID sea valido y pertenezca al proceso de busqueda
if [ "$pid_usuario" -eq "$pid_buscador"  ]; then
	#envia senal sigkill para finalizar
	pkill $pid_buscador	
	echo "Senal enviada para finalizar la busqueda."
	ps
else
	echo "el ID del proceso no es valido o no corresponde a la busqueda"
fi


