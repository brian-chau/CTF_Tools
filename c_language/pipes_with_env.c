// Simulates the BASH command:
//     /usr/bin/cat arg1 | envVariable=value /path/to/bin arg2

#include <sys/wait.h>
#include <unistd.h>

int pwncollege(char *prod_app, char * cons_app, char** prod_args, char** cons_args, char **prod_env, char **cons_env) {
    int i = 0, j = 0;

    if ( 0 == (i = fork()) ) {                            // Child1 process
        int pipe_fds[2];
        pipe(pipe_fds);
        if ( 0 == (j = fork()) ) {                        // Child1 > Child2 forked process
            dup2(pipe_fds[STDOUT_FILENO], STDOUT_FILENO); // Use the WRITE pipe for the "Child1 > Child2" forked process
            close(pipe_fds[STDIN_FILENO]);                // Close the READ pipe for the "Child1 > Child2" forked process, since it's not used
            execve(prod_app, prod_args, prod_env);
        } else {                                          // Child1 > Parent2 forked process
            dup2(pipe_fds[STDIN_FILENO], STDIN_FILENO);   // Use the READ pipe for the "Child1 > Parent2" forked process
            close(pipe_fds[STDOUT_FILENO]);               // Close the WRITE pipe for the "Child1 > Parent2" forked process, since it's not used
            execve(cons_app, cons_args, cons_env);
        }
    } else {                                              // Parent1 process
        waitpid(i, NULL, 0);
    }
    return 0;
}

int main(int argc, char** argv) {
    char *prod_app    = "/usr/bin/cat";
    char *prod_args[] = { prod_app, "arg1", (char *) NULL };
    char *prod_env[] = { (char*) NULL };

    char *cons_app    = "/challenge/embryoio_level32";
    char *cons_args[] = { cons_app, "arg2", (char *) NULL };
    char *cons_env[] = { "envVariable=value", (char*) NULL };

    pwncollege(prod_app, cons_app, prod_args, cons_args, prod_env, cons_env);
    return 0;
}