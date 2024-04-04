#!/bin/bash

nuevoPrompt() {

export PS1='$(date +"%Y"):\h\w '

#Volver a iniciar sesion en Linux para volver al Bash por defecto
}

echo -e "Bienvenido usuario: $(whoami)\n"

echo "Usted se ha conectado en el dia $(date +"%d/%m/%Y")"
echo "a la hora: $(date +"%Hh:%Mm:%Ss")"
echo "En la terminal: $TERM del host: $HOSTNAME"
echo "Se encuentran conectados en este momento, los siguientes usuarios:"
who
echo "Su path es:"
echo $PATH
