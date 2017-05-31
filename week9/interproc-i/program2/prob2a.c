#include <unistd.h>		
#include <stdio.h>
void main() {	
    int fda[2];	// file descriptors
    int fda_2[2];
    if ( pipe(fda) < 0 ) printf("create pipe failed\n"); 
    switch ( fork() ) {	// fork an identical sub-process 		
        case -1 : printf("fork failed\n"); 
        case 0:	// run ls in child process 
            if(pipe(fda_2) < 0) printf("create pipe_2 failed\n");
                switch( fork() ){
                    case -1: printf("fork_2 failed"); break;
                    case 0: 
                        close(1);
                        dup(fda_2[1]);
                        close(fda_2[0]);
                        close(fda_2[1]);
                        printf("in child_2\n");
                        execlp("cat", "cat", "4300.txt", (char *)0);
                        printf("failed to execute cat\n");
                    default:
                        close(0);
                        dup(fda_2[0]);
                        close(1);
                        dup(fda[1]);
                        close(fda[0]);
                        close(fda[1]);
                        close(fda_2[0]);
                        close(fda_2[1]);
                        execlp("grep", "grep", "ant", (char *)0);
                        printf("failed to execute grep\n");
                        break;
                }
        default:	// run wc in parent
            close (0);						// close standard input				
            dup (fda[0] );					// duplicate pipe read end				
            close ( fda[0] );				// close read end of pipe				
            close (fda[1] );					// close write end of pipe		
            execlp ("wc", "wc", (char *)0);	// execute wc command
            printf ("failed to execute4 wc\n");
            break;
    }		
}
