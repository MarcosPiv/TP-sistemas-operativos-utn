#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname systemInfo;

    if (uname(&systemInfo) != 0) {
        perror("uname");
        return 1;
    }

    printf("Tipo de Sistema: %s\n", systemInfo.sysname);
    printf("Nombre del Equipo: %s\n", systemInfo.nodename);
    printf("Version del Kernel: %s\n", systemInfo.release);
    printf("Version del S.O.: %s\n", systemInfo.version);
    printf("Arquitectura: %s\n", systemInfo.machine);

    return 0;
}

