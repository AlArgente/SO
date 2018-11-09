// Argente del Castillo Garrido Alberto
// Variante 1

#include <sys/types.h>	
#include <unistd.h>		
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>	
#include <dirent.h>
#include <stdlib.h>
#include <sys/wait.h>	
#include <string.h>
#include <limits.h>


int main(int argc, char **argv) {


	// Comprobamos que se ejecuta con el número de argumentos correcto.
	if(argc!=3) {
		perror("El número de argumentos debe ser 2");
		exit(-1);
	}
	// Guardamos la cadena listabusqueda
	char lista_busqueda[NAME_MAX];
	strcpy(lista_busqueda, "listabusqueda");
	// Guardamos la orden
	char orden[strlen(argv[1])];
	strcpy(orden, argv[1]);
	// Variable para comprobar que se abre/crea el fichero
	int fd;
	// Recogemos el valor $PATH del sistema
	char *lista=getenv("PATH");
	// Var auxiliar buffer para escribir en listabusqueda
	char buff[strlen(lista)];
	strcpy(buff, lista);
	// Cauce
	int pcut[2];
	// Creamos el cauce
  if(pipe(pcut) < 0) {
    perror("\nError en pipe");
    exit(-1);
  }
	// Variable para crear hijos
	pid_t pid;
	// Cadena que usará el padre para leer el cauce
	char rutadir[PATH_MAX];

	if ((fd=open(lista_busqueda,O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR)) < 0) {
		perror("\nError al abrir/crear el archivo listabusqueda");
		exit(-1);
	}
	if (write(fd, lista, strlen(lista)) < 0){
		perror("\nError en el write");
		exit(-1);
	}
	
	if((pid = fork())<0){
		perror("\nError en el fork");
		exit(-1);
	}

	if(pid==0){ // Proceso hijo

		close(pcut[0]);

		dup2(pcut[1],STDOUT_FILENO);	
		
		//if( write(STDOUT_FILENO, execlp("cut", "cut","-d:", "-f", argv[2], "-z", lista_busqueda, NULL), PATH_MAX)){
		if((execlp("cut", "cut","-d:", "-f", argv[2], "-z", lista_busqueda, NULL)) < 0){ // Ejecución de cut
			perror("\nError en execl");
			exit(-1);
		}

	} else { // Proceso padre
		close(pcut[1]);
		// Para el read del padre
		int leer;
		if((leer = read(pcut[0], rutadir, PATH_MAX)) < 0){
			perror("\nError en el read del cauce");
			exit(-1);
		} else if (leer == 1) {
				printf("\nLa orden cut no ha encontrado el campo buscado");
				exit(0);
		} else if (leer > 1) {
				printf("\nLa orden cut se ha ejecutado con éxito\n");
				struct stat atributos;
				char ruta[PATH_MAX];
				// Accedemos a la ruta relativa
				strcpy(ruta, rutadir);
				strcat(ruta, "/");
				strcat(ruta, orden);
				// Accedemos a los atributos de la ruta
				if (stat(ruta, &atributos) < 0){
					perror("Error en stat");
					exit(-1);
				} else { // Mostramos el resultado
						printf("\nEl tamaño de bytes es %lu.", atributos.st_size);
						printf("\nEl identificativo de usuario propietario es %i.", atributos.st_uid);
						printf("\nEl identificativo de grupo propietario es %i.\n", atributos.st_gid);
						exit(0);
				}
		}
	}

	exit(0);

}

