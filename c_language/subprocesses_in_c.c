// Simulates the BASH command:
//     /path/to/some/bin some_arg

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
}

int main(){
    func();
}