#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {

  if (argc != 2) {
    perror("El número de argumento debe ser dos");
    exit(-1);
  }
  pid_t pid;
  int number;
  number = atoi(argv[1]);

  if ((pid = fork()) < 0) {
    perror("Error en el fork.");
  }
  // Proceso hijo
  if (pid == 0) {
    printf(
        "Soy el proceso hijo y mi pid es: %d, y el pid de mi padre es: %d. \n",
        getpid(), getppid());
    printf("Voy a calcular si el número %d es divisible por 4 o no.\n", number);
    if ((number % 4) == 0) {
      printf("El número %d es divisible por 4.\n", number);
    } else {
      printf("El número %d no es divisible por 4.\n", number);
    }
  } else if (pid) {
    printf("Soy el proceso padre y mi pid es: %d y el de mi hijo es: %d.\n",
           getpid(), pid);
    printf("Voy a calcular si el número %d es par o impar.\n", number);
    if ((number % 2) == 0) {
      printf("El número %d es par.\n", number);
    } else {
      printf("El número %d es impar.\n", number);
    }
  }
  return (0);
}
