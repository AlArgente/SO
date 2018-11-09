#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* Primitive system data types for abstraction\
			   of implementation-dependent data types.
#include<unistd.h>
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define S_ISREG(mode) (mode & S_IFMT == S_ISREG)
