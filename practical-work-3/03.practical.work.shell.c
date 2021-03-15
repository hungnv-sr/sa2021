#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define LENGTH_MAX 100

int main(int argc, char const *argv[]) {
	char input[100];
	char *args[10];
	while (1) {
		// ask for command
		printf("Enter command:");
		fgets(input, sizeof(input), stdin);

		// initialization of args everytime
		memset(args, 0, sizeof(args));
		
		// transform the input string
		// to array of args
		// so that execvp can use
		int argc = 0;
		int len = strlen(input);
		char *prevArg = input;
		for (int i = 0; i < len; i++) {
			if (input[i] == ' ') {
				args[argc++] = prevArg;
				prevArg = &input[i+1];
				input[i] = '\0';
			}
			if (input[i] == '\n') {
				input[i] = '\0';
			}
		}
		if (strcmp(input,"quit") == 0) {
            printf("User quit.");
            break;
        }
		
		args[argc++] = prevArg;

		// fork() + exec() combo
		int pid = fork();
		if (pid == 0) {
			execvp(args[0], args);
		}
		else {
			waitpid(pid, NULL, 0);
		}
	}
	printf("Terminating.\n");
	return 0;
}