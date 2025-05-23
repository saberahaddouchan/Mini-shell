#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD 1024
#define MAX_ARGS 64

int main() {
    char cmd[MAX_CMD];
    char *args[MAX_ARGS];

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (!fgets(cmd, MAX_CMD, stdin)) break;
        cmd[strcspn(cmd, "\n")] = 0;  // retirer le \n

        if (strcmp(cmd, "exit") == 0) break;

        // Découper la commande en mots (arguments)
        int i = 0;
        char *token = strtok(cmd, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // dernier argument = NULL

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }

    return 0;
}
