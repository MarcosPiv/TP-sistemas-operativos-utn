#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

	int fifo;

	fifo = open("/tmp/datetime.fifo",O_WRONLY);

	write(fifo, "CERRAR", strlen("CERRAR")+1);
	close(fifo);


return 0;
}
