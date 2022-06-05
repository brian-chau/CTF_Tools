// Simulates the BASH command:
//     /path/to/some/bin > file_to_redirect_to_stdout.txt

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int pwncollege(char *app, char **args, char **env, char *file) {
    pid_t pid;
    int status, fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    if ((pid = fork()) < 0) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (!pid) { /* child */
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execve(app, args, env);
        perror("exec");
        return EXIT_FAILURE;
    } else { /* parent */
        close(fd);
        wait(&status);
    }

    return EXIT_SUCCESS;
}

int main(void) {
    char *app = "/path/to/some/bin";
    char *args[] = {app, NULL};
    char *env[] = {NULL};

    char *file = "file_to_redirect_to_stdout.txt";

    return pwncollege(app, args, env, file);
}