// closh.c - COSC 315, Winter 2020
// Courtney Gosselin, Ben Tisserand, Alex Qin

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>

#define TRUE 1
#define FALSE 0

void parallelTimeoutAlarm(time_t baseTime, int timeout){
	pid_t childId;
         if((childId = fork())!=0){
         	// If we are the parent, our job is to monitor the timeout until the process is done or times out
         	while(waitpid(-1,NULL,WNOHANG)>=0){
			//printf("%d\n",waitpid(id,NULL,WNOHANG));
         		if(baseTime - time(NULL) + timeout < 0){
         			kill(childId,SIGKILL);
         			printf("Process ID %d has timed out and been terminated.\n",childId);
         			break;
         		}
         	}
         	exit(1);
         }
         return;
}

// tokenize the command string into arguments - do not modify
void readCmdTokens(char* cmd, char** cmdTokens) {
    cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
    int i = 0;
    cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
    while (cmdTokens[i++] && i < sizeof(cmdTokens)) {
        cmdTokens[i] = strtok(NULL, " ");
    }
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
    char c = getchar();
    while (getchar() != '\n');
    return c;
}

// main method - program entry point
int main() {
    char cmd[81]; // array of chars (a string)
    char* cmdTokens[20]; // array of strings
    int count; // number of times to execute command
    int parallel; // whether to run in parallel or sequentially
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)
    
    while (TRUE) { // main shell input loop
        
        // begin parsing code - do not modify
        printf("closh> ");
        fgets(cmd, sizeof(cmd), stdin);
        if (cmd[0] == '\n') continue;
        readCmdTokens(cmd, cmdTokens);
        do {
            printf("  count> ");
            count = readChar() - '0';
        } while (count <= 0 || count > 9);
        
        printf("  [p]arallel or [s]equential> ");
        parallel = (readChar() == 'p') ? TRUE : FALSE;
        do {
            printf("  timeout> ");
            timeout = readChar() - '0';
        } while (timeout < 0 || timeout > 9);
        // end parsing code
        
        
        ////////////////////////////////////////////////////////
        //                                                    //
        // TODO: use cmdTokens, count, parallel, and timeout  //
        // to implement the rest of closh                     //
        //                                                    //
        // /////////////////////////////////////////////////////
        
	// Initialize time and child variables
	time_t baseTime;
	pid_t childId;

        // Loops through the fork command based on the number entered in count
	for(int i = 0; i < count; i++){
		
		if((childId = fork())==0){ //Check to see if process is a child. If so, leave loop
			parallelTimeoutAlarm(time(NULL),timeout);
			break;	
		}else if(parallel == FALSE){ //If not running in parallel mode, create while loop that monitors childs status
			time(&baseTime); // set basetime to now
			while(waitpid(-1,NULL,WNOHANG)>=0){ // We use WNOHANG to ensure our while loop runs while waiting for the child
				
				if(timeout>0 && baseTime - time(NULL) + timeout<0){ // If we have exceeded the basetime by the timeout, kill child
					kill(childId,SIGKILL);
					printf("Process ID %d has timed out and been terminated.\n",childId);
					break;
				}
			}
		}
		
	}
	
	if(childId==0){
        	execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program
        	// doesn't return unless the calling failed
        	printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
	}
	exit(1);        
    }
}

