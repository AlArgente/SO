#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char argv[]) {
  pid_t pid;
  int i, estado;

  for (i = 0; i < 5; i++) {
    if ((pid = fork()) < 0) {
      perror("Error en el fork");
      exit(-1);
    } else if (pid == 0) {
      printf("Soy el hijo %d.\n", getpid());
      exit(0);
    }
  }

  for (i = 5; i > 0; i = i - 2) {
    pid = wait(&estado);
    printf("Acaba de finalizar mi hijo con PID: %d\n", pid);
    printf("Solo me quedan %d hijos vivos.\n", i);
  }

  for (i = 4; i > 0; i = i - 2) {
    pid = wait(&estado);
    printf("Acaba de finalizar mi hijo con PID: %d y con estado %d\n", pid,
           estado);
    printf("Solo me quedan %d hijos vivos.\n", i);
  }

  return (0);
}
