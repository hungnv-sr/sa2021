  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int pid = 0;
int childPid;
void handler(int signal_num){
  	switch (signal_num) {
  	case SIGTSTP:
    	printf("\npaused\n");
    break;
	case SIGINT:
		printf("\nSIGNINT\n");
  	case SIGTERM:
    	printf("\nSIGTERM\n");
    	exit(0);
    break;
  }
}

void split(str) {


}

void doexec(args) {
	int pipefds[2];
	pipe (pipefds);
	switch (fork ()) {
		case -1: perror ("fork"); exit (1);
		case 0:
			dup2 (pipefds[1], 1);
			close(pipefds[0]);
			close(pipefds[1]);
			execvp("/bin/bash", args);
		break;
		default:
			dup2(pipefds[0], 0);
			close(pipefds[0]);
			close(pipefds[1]);
		break;
	}
}

void execute_cmd(cmd) {

}

int main(int argc, char const *argv[]) {
	char input[100];
    signal(SIGTSTP, handler);
	signal(SIGINT, handler);
	signal(SIGTERM, handler);
	while (1) {
		// ask for command
		printf("Enter command:");
		fgets(input, sizeof(input), stdin);
		char *args[100];
		// initialization of args everytime
		memset(args, 0, sizeof(args));
		
		// transform the input string
		// to array of args
		// so that execvp can use
		int argc = 0;
		int len = strlen(input);
		int prevArgPos = 0;
		for (int i = 0; i < len; i++) {
			if (input[i] == ' ' || i == len - 1) {
				args[argc++] = &input[prevArgPos];
				input[i] = 0;
				prevArgPos = i+1;
			}
		}
		if (strcmp(input,"quit") == 0) {
            printf("User quit.");
            break;
        }
		// for (int i = 0; i <argc; i++) {
		// 	if (strcmp(args[i], "|")) {
		// 		pipePos = i;
		// 		args[i] = 0;
		// 		break;
		// 	}
		// }
		// detect if we have a pipe |
		int pipePos = -1;
		for (int i = 0; i < argc; i++) {
			if (strcmp(args[i], "|") == 0) {
				pipePos = i;
				args[i] = 0;
				break;		// one pipe at the moment only
			}
		}
		if (pipePos < 0) {
			pid = fork ();
			if (pid) {
				childPid = pid;
				waitpid(pid, NULL, 0); 
			} else {
				// child, exec				
				execvp(args[0], args);
			}
		} else {
			int pipefds[2];
			pipe (pipefds);

			int pid1 = fork();
			if (pid1 == 0) {
				dup2(pipefds[1], 1);
				close(pipefds[0]);
				close(pipefds[1]);
				execvp(args[0], args);
			}
			int pid2 = fork();
			if (pid2 == 0) {
				dup2 (pipefds[0], 0);
				close(pipefds[0]);
				close(pipefds[1]);
				execvp(args[pipePos+1], &args[pipePos + 1]);
			}
			close(pipefds[0]);
			close(pipefds[1]);
			waitpid(pid1, NULL, 0);	
			waitpid(pid2, NULL, 0);
		}

	}
	printf("End.\n");
	return 0;
}