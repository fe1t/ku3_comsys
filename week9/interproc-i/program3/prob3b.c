#include <unistd.h>		
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr, "usage: ./prob3b DIRECTORY\n");
        exit(-1);
    }
    int fda[2];	// file descriptors
    if ( pipe(fda) < 0 ) printf("create pipe failed\n"); 
    switch ( fork() ) {	// fork an identical sub-process 		
        case -1 : printf("fork failed\n"); 
        case 0:	// run ls in child process 
            close(1);
            dup(fda[1]);
            close(fda[0]);
            close(fda[1]);
            execlp("find", "find", argv[1], "-type", "f", (char *)0);
            printf("failed to execute find\n");
        default:	// run wc in parent
            close (0);						// close standard input				
            dup (fda[0] );					// duplicate pipe read end				
            close ( fda[0] );				// close read end of pipe				
            close (fda[1] );					// close write end of pipe		
            execlp ("wc", "wc", (char *)0);	// execute wc command
            printf ("failed to execute wc\n");
        break;
    }		
}
