#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include <signal.h>

#define REDIRECT1 1
#define REDIRECT2 2

int redirect_state(char*[]); // Checks if there redirect sign, and which one (> or >>)
void run(char*[]); // Runs the shell command
void _redirect1(char*[]); // Runs shell command with >
void _redirect2(char*[]); // Runs shell command with >>
void _pipe(char*[], int); // Runs shell command with |
void sigint_exit(int); // Exiting child process via Ctrl+C

int main() {
	char *argv[10], command[1024], *token;

	signal(SIGINT, sigint_exit);
	printf("Welcome!\n");

	while (1) {
	    printf("# ");
	    fgets(command, 1024, stdin);
	    command[strlen(command) - 1] = '\0'; // replace \n with \0

        int saved_stdout = dup(STDOUT_FILENO), i = 0, isPipe = 0;

	    token = strtok(command," ");
	    while (token != NULL) {
			argv[i] = token;
			token = strtok (NULL, " "); 
            if(strcmp(argv[i] , "|") == 0) isPipe = 1;
			i++;
	    }
	    argv[i] = NULL;

	    if (argv[0] == NULL) continue;
		else if(strcmp(argv[0], "exit") == 0) return 0;

        if (isPipe == 1) {
            _pipe(argv, saved_stdout);
        }
        else if (redirect_state(argv) == REDIRECT1) {
            _redirect1(argv);
            fflush(stdout);
            dup2(saved_stdout, STDOUT_FILENO); 
        }
        else if (redirect_state(argv) == REDIRECT2) {
            _redirect2(argv);
            fflush(stdout);
            dup2(saved_stdout, STDOUT_FILENO); 
        }
        else run(argv);
	}

	return 0;
}

void sigint_exit(int signal) {
    printf("\n");
} 

int redirect_state(char *argv[]) {
    int i = 0;
    while(argv[i] != NULL) {
        if (strcmp(argv[i], ">") == 0) {
            return REDIRECT1;
        }
        else if (strcmp(argv[i], ">>") == 0) {
            return REDIRECT2;
        }
        i++;
    }
    return 0;
}

void run(char *argv[]) {
    if (fork() == 0) { 
        signal(SIGINT, sigint_exit);
        execvp(argv[0], argv);
    } 
    else wait(NULL);
}

void _redirect1(char *argv[]) {
    int i = 0;
    char *src[10], *target;
    while(argv[i] != NULL) {
        if(strcmp(argv[i], ">") == 0) {
            src[i] = NULL;
            i++;
            target = argv[i];
        }
        else src[i] = argv[i];
        i++;
    }
    
    FILE *fp = fopen(target, "w");
    dup2(fileno(fp), STDOUT_FILENO);
    run(src);
    fclose(fp);
}

void _redirect2(char *argv[]) {
    int i = 0;
    char *src[10], *target;
    while(argv[i] != NULL) {
        if(strcmp(argv[i], ">>") == 0) {
            src[i] = NULL;
            i++;
            target = argv[i];
        }
        else src[i] = argv[i];
        i++;
    }
    
    FILE *fp = fopen(target, "a+");
    dup2(fileno(fp), STDOUT_FILENO);
    run(src);
    fclose(fp);
} 

void _pipe(char *argv[], int saved_stdout) {
    int i = 0, j = 0, k = 0, _pipe1 = 0, _pipe2 = 0, pipe1[2], pipe2[2], saved_stdin = dup(STDIN_FILENO);
    char *cmd1[10], *cmd2[10], *cmd3[10];

    while(argv[i] != NULL) {
        if(strcmp(argv[i], "|") == 0) {
            if(_pipe1 == 0) {
                _pipe1 = i;
                cmd1[i] = NULL;
            }
            else _pipe2 = i;
            i++;
        }
        if(_pipe1 == 0) {
            cmd1[i] = argv[i];
        }
        else if(_pipe1 != 0 && _pipe2 == 0) {
            cmd2[j] = argv[i];
            j++;
            cmd2[j] = NULL;
        }
        else if(_pipe1 != 0 && _pipe2 != 0) {
            cmd3[k] = argv[i];
            k++;
            cmd3[k] = NULL;
        }
        i++;
    }

    if(_pipe1 != 0 && _pipe2 == 0) {
        pipe(pipe1);
        dup2(pipe1[1], STDOUT_FILENO);
        dup2(pipe1[0], STDIN_FILENO); 
        
        // cmd1
        switch(redirect_state(cmd1)) {
            case REDIRECT1:
                _redirect1(cmd1);
                break;
            case REDIRECT2:
                _redirect2(cmd1);
                break;
            case 0:
                run(cmd1);
                break;
        }

        //cmd2
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);

        switch(redirect_state(cmd2)) {
            case REDIRECT1:
                _redirect1(cmd2);
                break;
            case REDIRECT2:
                _redirect2(cmd2);
                break;
            case 0:
                run(cmd2);
                break;
        }
        dup2(saved_stdin, STDIN_FILENO);
        
        if(dup(STDOUT_FILENO) != saved_stdout)  dup2(saved_stdout, STDOUT_FILENO);
    }
    
    else {
        pipe(pipe1);
        pipe(pipe2);
        dup2(pipe1[1], STDOUT_FILENO);
        dup2(pipe1[0], STDIN_FILENO);
        // cmd1
        switch(redirect_state(cmd1)) {
            case REDIRECT1:
                _redirect1(cmd1);
                break;
            case REDIRECT2:
                _redirect2(cmd1);
                break;
            case 0:
                run(cmd1);
                break;
        }

        //cmd2
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);

        switch(redirect_state(cmd2)) {
            case REDIRECT1:
                _redirect1(cmd2);
                break;
            case REDIRECT2:
                _redirect2(cmd2);
                break;
            case 0:
                run(cmd2);
                break;
        }

        //cmd3
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe2[1]);
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[0]);

        switch(redirect_state(cmd3)) {
            case REDIRECT1:
                _redirect1(cmd3);
                break;
            case REDIRECT2:
                _redirect2(cmd3);
                break;
            case 0:
                run(cmd3);
                break;
        }
        dup2(saved_stdin, STDIN_FILENO);
        if(dup(STDOUT_FILENO) != saved_stdout)  dup2(saved_stdout, STDOUT_FILENO);
    }
}
