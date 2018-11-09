#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int arch, char **argc) {

  pid_t childpid;
  int nprocs = 21;
  int i = 0;
  /*
  Jerarquía de procesos tipo 1
  */
  for (i = 1; i < nprocs; i++) {
    if ((childpid = fork()) == -1) {
      fprintf(stderr, "Could not create child %d: %s\n", i, strerror(errno));
      exit(-1);
    } else if (childpid == 0) { // proceso hijo
      printf("Soy el proceso hijo %d y mi padre es %d.\n", getpid(), getppid());
    }
    if (!childpid)
      break;
  }
  /*
  Jerarquía de procesos tipo 2
  */
  /*for (i = 1; i < nprocs; i++) {
    if ((childpid = fork()) == -1) {
      fprintf(stderr, "Could not create child %d: %s\n", i, strerror(errno));
      exit(-1);
    } else if (childpid == 0) { // proceso hijo
      printf("Soy el proceso hijo %d y mi padre es %d.\n", getpid(), getppid());
    } else { // proceso padre
      // printf("Soy el proceso padre %d y mi hijo es %d\n", getpid(),
      // childpid);
    }
    if (!childpid)
      break;
  }*/
}
