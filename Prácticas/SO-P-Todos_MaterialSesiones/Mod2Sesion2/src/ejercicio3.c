#include <sys/types.h> //Primitive system data types for abstraction of implementation-dependent data types.
// POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h> //Needed for open
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h> //POSIX Standard: 2.10 Symbolic Constants         <unistd.h>

#define S_IREGRO 0000044
// S_IRGRP S_IROTH
void buscar();

int main(int argc, char const *argv[]) {
  int n_nodos;
  int cont;
  struct stat atributos;
  char ruta[246];
  DIR *dp;
  struct dirent *dirp;
  long int octal;
  long int t_bytes;
  mode_t mode;
  unsigned int printable_mode;

  if (argc < 3) {
    printf("El número de argumentos debe ser 3.\n");
    exit(-1);
  }

  if ((dp = opendir(argv[1])) < 0) {
    printf("Error al abrir el archivo: %d\n", errno);
    perror("Error en open\n");
    exit(-1);
  }
  octal = strtol(argv[2], 0, 8);

  printf("Los i-nodo son:\n");

  while ((dirp = readdir(dp)) != NULL) {
    // printf("Entrada de nombre: %s\n", dirp->d_name);
    strcpy(ruta, argv[1]);
    strcmp(ruta, "/");
    strcat(ruta, dirp->d_name);
    if (stat(ruta, &atributos) < 0) {
      printf("Error al intentar acceder a los atributos del arvhico %s\n",
             ruta);
      perror("Error en lstat");
      exit(-1);
    }
    mode = atributos.st_mode;
    printf("%s %lu\n", dirp->d_name, dirp->d_ino);
    if (mode & octal) {
      cont += 1;
    }
    t_bytes += atributos.st_size;
  }

  printf("Hay %d archivos regulares con permiso %lo para grupo y otros.\n",
         cont, octal);
  printf("El tamaño total ocupado por dichos archivos es %lo\n", t_bytes);

  closedir(dp);
  return 0;
}
