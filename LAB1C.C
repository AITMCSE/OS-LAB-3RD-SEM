#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // for fork(), execvp()
#include <sys/wait.h>    // for waitpid()

int main (int argc, char **argv)
{
    int i = 0;
    long sum;
    int pid;
    int status, ret;

    printf("Parent: Hello, World!\n");

    pid = fork();

    if (pid == 0) {
        // I am the child
        char *args[] = {"./child", NULL};
        execvp("./child", args);
        perror("execvp failed");   // runs only if exec fails
        exit(1);
    }

    // I am the parent
    printf("Parent: Waiting for Child to complete.\n");

    if ((ret = waitpid(pid, &status, 0)) == -1)
        printf("parent:error\n");

    if (ret == pid)
        printf("Parent: Child process waited for.\n");

    return 0;
}
