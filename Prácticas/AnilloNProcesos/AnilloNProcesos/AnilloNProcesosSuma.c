// Programa que crea argv[1] procesos en total (contando el inicial)
// Se configuran en anillo,
// Calculo de la suma de los pids de todos los procesos

#include <stdio.h>	
#include <stdlib.h>	
#include <unistd.h>	
#include <string.h>	
#include <errno.h>	
int main(int argc, char *argv[ ])	
{int i;			/* numero de este proceso (comenzando en 1) */	
int childpid;	/* para recibir el resultado de fork */	
int nprocs;		/* nº  total de procesos en el anillo */	
int fd[2];		
int error, ret, p, numero, nbytesint, limite,pidPrimero,valor,suma,j;
nbytesint=sizeof(int);
pidPrimero = getpid();
if ( (argc!= 2 ) || ((nprocs=atoi(argv[1])) <= 0)   ) {	
	fprintf(stderr, "Error desde %s con los arguementos:\n",argv[0]);
	fprintf(stderr, "\t\t 	Debe dar como argumento 1 el nº de procesos nprocs\n");
	exit(1); 
}
if (pipe (fd) == -1) {	
	perror("No se puede crear pipe");
	exit(1);		
}		
if ((dup2(fd[0], STDIN_FILENO) == -1) ||		
	(dup2(fd[1], STDOUT_FILENO) == -1)) {	
	perror("Could not dup pipes");	
	exit(1);	
}		
if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {		
	perror("Could not close extra descriptors");	
	exit(1);	
}		
// crea los restantes procesos y sus conexiones	
for (i = 1; i <nprocs; i++) {		
	if (pipe (fd) == -1) {	
		fprintf(stderr,"Could not create pipe %d: %s\n",i,strerror(errno));
		exit(1);
	}	
	if ((childpid= fork()) == -1) {	
		fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
		exit(1);
	}	
	if (childpid> 0) 
		error = dup2(fd[1], STDOUT_FILENO);
	else	
		error = dup2(fd[0], STDIN_FILENO);
	if (error == -1) {	
		fprintf(stderr, "Could not dup pipes for iteration %d: %s\n",i,strerror(errno));
		exit(1);
	}	
	if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {	
		fprintf(stderr, "Could not close extra descriptors %d: %s\n",i,strerror(errno));
		exit(1);
	}	
	if (childpid)	
		break;
}// for		
////  ACTUACION DE CADA PROCESO   ///////////////////
valor=getpid()	;
fprintf(stderr,"Proceso con i= %d, pid %d y padre %d\n",i, 	(int)getpid(), (int)getppid());		
suma=valor;
for (j=1;j<=nprocs-1;j++){
	if(write(STDOUT_FILENO,&valor,nbytesint)<0)          {fprintf(stderr,"error al escribir%d\n",errno);};
	if(read (STDIN_FILENO, &valor,nbytesint)!=nbytesint) {fprintf(stderr,"error al leer%d\n",errno); };
	suma=suma+valor;					
}

fprintf(stderr, "Soy pid %d,SUMA= %d\n",valor, suma  );

exit(0);/////////
}
