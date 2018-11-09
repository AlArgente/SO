#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd[2];  // cauce para el primer hijo
  int fd1[2]; // cauce para el segundo hijo
  pid_t pid1, pid2;
  int min, max, medio, n1, n2, val1, val2;

  if (argc != 3) {
    perror("Error en el número de argumentos. Debe ser 3");
    exit(-1);
  }

  min = atoi(argv[1]);
  max = atoi(argv[2]);
  char minn[10];
  char maxn[10];
  medio = ((max - min) / 2) + min;
  char buffer[medio];

  pipe(fd);  // Creamos el cauce
  pipe(fd1); // Creamos el segundo cauce

  if ((pid1 = fork()) < 0) {
    perror("Error en el fork");
    exit(-1);
  }

  // Creo el hijo
  if (pid1 == 0) { // primer hijo
    close(fd[0]);  // Cerramos cauce para la lectura
    dup2(fd[1], STDOUT_FILENO);
    sprintf(minn, "%i", min);
    sprintf(maxn, "%i", medio);
    if (execlp("./esclavo", "./esclavo", minn, maxn, NULL) < 0) {
      perror("Error en el execl");
      exit(-1);
    }
  } else {
    close(fd[1]);
    while ((n1 = read(fd[0], &val1, sizeof(int))) > 0) {
      printf("%10d", val1);
    }
    close(fd[0]);
  }

  if ((pid2 = fork()) < 0) {
    perror("Error en el fork");
    exit(-1);
  }

  // Creo el hijo
  if (pid2 == 0) { // segundo hijo
    close(fd1[0]); // Cerramos cauce para la lectura
    dup2(fd1[1], STDOUT_FILENO);
    sprintf(minn, "%i", medio + 1);
    sprintf(maxn, "%i", max);
    if (execlp("./esclavo", "./esclavo", minn, maxn, NULL) < 0) {
      perror("Error en el execl");
      exit(-1);
    }
  } else {
    close(fd1[1]);
    while ((n2 = read(fd1[0], &val2, sizeof(int))) > 0) {
      printf("%10d", val2);
    }
    close(fd1[0]);
  }

  exit(0);
}
