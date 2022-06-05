// Simulates the BASH command:
//     /path/to/some/bin < file_to_redirect_to_stdin.txt

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int pwncollege(char *appName, char **appArgs, char **appEnv, char *targetFileToRead) {
    pid_t pid;
    int status, fd = open(targetFileToRead, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    if ((pid = fork()) < 0) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (!pid) { /* child */
        dup2(fd, STDIN_FILENO);
        close(fd);
        execve(appName, appArgs, appEnv);
        perror("exec");
        return EXIT_FAILURE;
    } else { /* parent */
        close(fd);
        wait(&status);
    }

    return EXIT_SUCCESS;
}

int main(void) {
    char *appName = "/path/to/some/bin";
    char *appArgs[] = {appName, NULL};
    char *appEnv[] = {NULL};

    char *targetFileToRead = "file_to_redirect_to_stdin.txt";

    pwncollege(appName, appArgs, appEnv, targetFileToRead);
}