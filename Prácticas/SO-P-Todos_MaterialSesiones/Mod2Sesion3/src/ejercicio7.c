#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  pid_t pid;
  int estado;
  char bg[] = "Hola cómo estás";
  char cadena[100];
  // printf("Introduce la cadena a ejecutar.\n");
  // scanf("%s\n", cadena);

  if ((pid = fork()) < 0) {
    perror("Error en el fork().");
    exit(-1);
  } else if (pid == 0) {
    if ((execl("./pruebacadena", cadena, bg, NULL)) < 0) {
      perror("\nError en el execl");
      exit(-1);
    }
  }

  wait(&estado);
  printf("\nMi hijo %d ha finalizado con el estado %d\n", pid, estado >> 8);
  exit(0);
}
