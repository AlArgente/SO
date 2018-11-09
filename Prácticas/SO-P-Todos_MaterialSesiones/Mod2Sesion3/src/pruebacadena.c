#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char *cadena;
  cadena = argv[1];

  printf("La cadena recibida es: %s.\n", cadena);
}
