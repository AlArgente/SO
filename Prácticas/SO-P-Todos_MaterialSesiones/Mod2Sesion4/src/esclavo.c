#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int prime(int n) {
  int i;
  int limit = sqrt(n);
  int primo = 1;

  for (i = 2; i <= limit && primo; i++) {
    if (n % i == 0)
      primo = 0;
  }
  return primo;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    perror("El número de argumentos debe ser 3");
    exit(-1);
  }
  // Cálulo de los números primos.
  int min, max, nprimo = 0;
  min = atoi(argv[1]);
  max = atoi(argv[2]);
  int n, k = 0;

  for (n = min; n <= max; n++) {
    if (prime(n)) {
      if (write(STDOUT_FILENO, &n, sizeof(int)) < 0) {
        perror("Error en el write");
        exit(-1);
      }
    }
  }

  return 0;
}
