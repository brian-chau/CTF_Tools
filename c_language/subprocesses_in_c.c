#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int func() {
    char *bin      = "/path/to/some/bin";
    char *arg1     = "some_arg";
    char *myargs[] = { bin, arg1, NULL };
    char *myenv[]  = { NULL };

    pid_t mypid;
    if (0 == (mypid = fork())) {
        execve(bin, myargs, myenv);
        perror("execve");
    }

    int timeout = 10000;
    int status;
    while (0 == waitpid(mypid, &status, WNOHANG)) {
        if ( --timeout < 0 ) {
            perror("timeout");
            return -1;
        }
        sleep(1);
    }
    exit(EXIT_FAILURE);
}

int main(){
    func();
}