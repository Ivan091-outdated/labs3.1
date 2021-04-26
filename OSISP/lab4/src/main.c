#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void created(int procNum){
    printf("Created %d: parent = %d, this = %d\n", procNum, getppid(), getpid());
}

void exited(int procNum){
    printf("Exited %d: parent = %d, this = %d\n", procNum, getppid(), getpid());
}


int main() {

    created(0);

    pid_t pid;
    int procNum = 1;
    if ((pid = fork()) == 0){
        procNum = 1;
        created(procNum);

        if ((pid = fork()) == 0){
            procNum = 4;
            created(procNum);
            exited(procNum);
            exit(0);
        } else {
            sleep(1);
        }

        if ((pid = fork()) == 0){
            procNum = 5;
            created(procNum);
            exited(procNum);
            exit(0);
        } else {
            sleep(1);
        }

        exited(procNum);
        exit(0);
    } else {
        sleep(3);
    }

    if ((pid = fork()) == 0){
        procNum = 3;
        created(procNum);

        if ((pid = fork()) == 0){
            procNum = 6;
            created(procNum);

            if ((pid = fork()) == 0){
                procNum = 7;
                created(procNum);
                execl("/bin/pwd","pwd",NULL);
                exited(procNum);
                exit(0);
            } else {
                sleep(1);
            }

            exited(procNum);
            exit(0);
        } else {
            sleep(2);
        }

        exited(procNum);
        exit(0);
    } else {
        sleep(3);
    }

    exited(0);
    exit(0);
}