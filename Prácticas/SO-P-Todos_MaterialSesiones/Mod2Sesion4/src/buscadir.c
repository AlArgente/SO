#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void busca_dir(char *pathname);

int main(int argc, char **argv) {
  busca_dir(argv[1]);
  exit(0);
}

void busca_dir(char *pathname) {
  struct dirent *dir;
  DIR *direct;
  struct stat atributos;
  char newpath[300];

  if ((direct = opendir(pathname)) == NULL) {
    perror("No se ha podido abrir el arvhico");
    exit(-1);
  }

  while ((dir = readdir(direct)) != NULL) {
    char path2[300];
    sprintf(path2, "%s/%s", pathname, dir->d_name);
    // sprintf(path2, "%s", dir->d_name); // CON ESTO NO FUNCIONA
    stat(path2, &atributos);
    printf("%s: %i\n", path2, (int)dir->d_ino);

    if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0)) {
      if (S_ISDIR(atributos.st_mode)) { // Es un directorio
        printf("Es un directorio\n");
        printf("%s: %i\n", dir->d_name, (int)dir->d_ino);
        sprintf(newpath, "%s/%s", pathname, dir->d_name);
        busca_dir(newpath);
        // printf("\n");
      } else {

        printf("Es un archivo\n");
        printf("\n");
      }
    }
  }
  closedir(direct);
}

/*

printf("%s\n", dir->d_name);

if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0)) {
  direct = opendir(dir->d_name);
  if (direct) {
    printf("Es un directorio\n");
    printf("%s\n", dir->d_name);
    printf("Su número de i-nodos es: %lu\n", dir->d_ino);
    dir = readdir(direct);
    busca_dir(dir->d_name);
    closedir(direct);
  } else {
    printf("Es un archivo.\n");
  }
}

*/
