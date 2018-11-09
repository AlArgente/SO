/*
Ejercicio 2
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Probar tras la ejecuci�n del programa: $>cat archivo y $> od -c archivo
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* Primitive system data types for abstraction\
			   of implementation-dependent data types.
#include<unistd.h>
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd, fsalida, cont;
  ssize_t success;
  char cad[1];
  char buff[80];

  if (argc < 2) {
    printf("\nError en el número de argumentos.");
    exit(-1);
  }

  fsalida =
      open("salidaej2.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

  // Si no podemos abrir el archivo
  if ((fd = open(argv[1], O_RDONLY)) < 0) {
    printf("\nError %d en open", errno);
    perror("\nError en open");
    exit(EXIT_FAILURE);
  }
  cont = 0;
  // Leemos los primeros 80 bytes del fichero pasado por parámetro.
  while ((success = read(fd, cad, 1)) != 0) {
    // printf("\nBytes leídos: %d", success);
    if (success == 0) {
      printf("\nSe ha alcanzado el final del fichero");
    }
    if (success < 0) {
      printf("\nError en la lectura del archivo");
      exit(EXIT_FAILURE);
    }
    sprintf(buff,
            "Bloque %d. Aquí van los 80 bytes leídos del archivo pasado como "
            "argumento\n",
            cont);

    if (write(fsalida, buff, strlen(buff)) != strlen(buff)) {
      printf("\nError en el write");
      exit(EXIT_FAILURE);
    }
    cont++;
    // i = i + 80;
  }

  if (close(fd) < 0) {
    printf("Error al cerrar el archivo\n");
  }

  if (close(fsalida) < 0) {
    printf("Error al cerrar el archivo\n");
  }

  printf("\nSuccess: %d\n", success);
  return EXIT_SUCCESS;
}
