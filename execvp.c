#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv){
	char* args[] = { "ls", "-lart", "/Users", NULL };
	int r = execvp("ls", args);
	// NOTE!  This will not run on error.  Why?!
	//strtock
	//cstring.h
	perror("Error: ");
}
