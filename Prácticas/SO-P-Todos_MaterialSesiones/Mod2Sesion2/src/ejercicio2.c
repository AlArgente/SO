#include <sys/types.h> //Primitive system data types for abstraction of implementation-dependent data types.
// POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h> //Needed for open
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h> //POSIX Standard: 2.10 Symbolic Constants         <unistd.h>

#define SET_UID_BIT 0x4000
#define SET_GID_BIT 0x2000
#define STICKY_BIT 0x1000

// Readable USER bits defined here
#define USR_READ_BIT 0x400
#define USR_WRITE_BIT 0x200
#define USR_EXEC_BIT 0x100

// Readable GROUP bits defined here
#define GRP_READ_BIT 0x040
#define GRP_WRITE_BIT 0x020
#define GRP_EXEC_BIT 0x010

// Readable OTHER bits defined here
#define OTH_READ_BIT 0x004
#define OTH_WRITE_BIT 0x002
#define OTH_EXEC_BIT 0x001

int main(int argc, char const *argv[]) {
  int fd1, fd2;
  struct stat atributos;
  char ruta[246];
  DIR *dp;
  struct dirent *dirp;
  long int octal;
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
    } else {
      mode = atributos.st_mode;
      printable_mode = 0;
      if (mode & S_ISUID)
        printable_mode |= SET_UID_BIT;

      if (mode & S_ISGID)
        printable_mode |= SET_GID_BIT;

      if (mode & S_ISVTX)
        printable_mode |= STICKY_BIT;

      if (mode & S_IRUSR)
        printable_mode |= USR_READ_BIT;

      if (mode & S_IWUSR)
        printable_mode |= USR_WRITE_BIT;

      if (mode & S_IXUSR)
        printable_mode |= USR_EXEC_BIT;

      if (mode & S_IRGRP)
        printable_mode |= GRP_READ_BIT;

      if (mode & S_IWGRP)
        printable_mode |= GRP_WRITE_BIT;

      if (mode & S_IXGRP)
        printable_mode |= GRP_EXEC_BIT;

      if (mode & S_IROTH)
        printable_mode |= OTH_READ_BIT;

      if (mode & S_IWOTH)
        printable_mode |= OTH_WRITE_BIT;

      if (mode & S_IXOTH)
        printable_mode |= OTH_EXEC_BIT;
    }

    printf("%s : %d %lo\n", dirp->d_name, printable_mode, octal);
    // printf("%s %lo\n", dirp->d_name, octal);
    if (chmod(ruta, octal) < 0) {
      printf("%s : %d %lo\n", dirp->d_name, errno, printable_mode);
    }
  }

  closedir(dp);

  return 0;
}
