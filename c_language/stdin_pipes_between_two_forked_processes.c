// Simulates the BASH command:
//     /usr/bin/cat file.txt | /path/to/bin

#include <sys/wait.h>
#include <unistd.h>

int fxn(char *prod_app, char * cons_app, char** prod_args, char** cons_args) {
    int i = 0, j = 0;

    if ( 0 == (i = fork()) ) {                            // Child1 process
        int pipe_fds[2];
        pipe(pipe_fds);
        if ( 0 == (j = fork()) ) {                        // Child1 > Child2 forked process
            //sleep(1);                                   // Simulate wait
            dup2(pipe_fds[STDOUT_FILENO], STDOUT_FILENO); // Use the WRITE pipe for the "Child1 > Child2" forked process
            close(pipe_fds[STDIN_FILENO]);                // Close the READ pipe for the "Child1 > Child2" forked process, since it's not used
            execve(prod_app, prod_args, NULL);
        } else {                                          // Child1 > Parent2 forked process
            dup2(pipe_fds[STDIN_FILENO], STDIN_FILENO);   // Use the READ pipe for the "Child1 > Parent2" forked process
            close(pipe_fds[STDOUT_FILENO]);               // Close the WRITE pipe for the "Child1 > Parent2" forked process, since it's not used
            execve(cons_app, cons_args, NULL);
        }
    } else {                                              // Parent1 process
        waitpid(i, NULL, 0);
    }
}

int main(int argc, char** argv) {
    char *prod_app    = "/usr/bin/cat";
    char *prod_args[] = { prod_app, "file.txt", (char *) NULL };

    char *cons_app    = "/path/to/bin";
    char *cons_args[] = { cons_app, (char *) NULL };
    fxn(prod_app, cons_app, prod_args, cons_args);
    return 0;
}
