#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define LENGTH_MAX 100

int main()
{
    char *input[100];
	char *args[100];

    while (1) {
		printf("Enter commands: ");
		fgets(input, sizeof(input), stdin);

		input[strcspn(input, "\n")] = 0;
		printf("Input: %s\n",input);

        if (strcmp(input,"quit\n") == 0) {
            printf("User quit.");
            break;
        }
		
		// initialization of args everytime
		memset(args, 0, sizeof(args));
		
		// transform the input string
		// to array of args
		// so that execvp can use
		int argc = 0;
		int len = strlen(input);
		char *prevArg = input;

		// I dont think I need this
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
		args[argc++] = prevArg;

		// dump the info for debugging purpose
		printf("Input : %s\n", input);
		if (strcmp(input, "quit") == 0) {
			break;
		}

		printf("- argc : %d\n", argc);
		printf("- args : \n");
		for (int i = 0; i <= argc; i++) {
			printf("  + args[%d]=%s\n", i, args[i]);
		}

		// fork() + exec() combo
		int pid = fork();
		if (pid == 0) {
			printf(111111);
			execvp(args[0], args);
		}
		else {
			waitpid(pid, NULL, 0);
		}
	}
	printf("Terminating.\n");
	return 0;
}