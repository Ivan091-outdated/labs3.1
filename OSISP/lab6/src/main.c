#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include <stdlib.h>

void sig_handler_parent(int signum) {
    printf("Parent : Received a response signal from child \n");
}

void sig_handler_child(int signum) {
    printf("Child : Received a signal from parent \n");
}

int main() {
    int fd[2];

    if(pipe(fd) < 0){
        printf("Can\'t create pipe\n");
        return -1;
    }

    pid_t pid;
    if ((pid = fork()) < 0) {
        printf("Fork Failed\n");
        exit(1);
    }
        /* Child Process */
    else if (pid == 0) {
        signal(SIGUSR1, sig_handler_child);
        pause();
        double sides[3];
        read(fd[0], sides, 3*sizeof(double));
        close(fd[0]);
        sides[0] += sides[1] + sides[2];
        write(fd[1], sides, sizeof(double));
        close(fd[1]);
        printf("Child: sending signal to Parent\n");
        kill(getppid(), SIGUSR1);
    }
        /* Parent Process */
    else {
        signal(SIGUSR1, sig_handler_parent);
        double sides[3] = {100, 200, 150};
        write(fd[1], sides, 3*sizeof(double));
        close(fd[1]);
        printf("Parent: sending signal to Child\n");
        kill(pid, SIGUSR1);
        printf("Parent: waiting for response\n");
        pause();
        double side[1];
        read(fd[0], side, sizeof(double));
        close(fd[0]);
        printf("Parent: perimeter is: %f", side[0]);
    }
    return 0;
}