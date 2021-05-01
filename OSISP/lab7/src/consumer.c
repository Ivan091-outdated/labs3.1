#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <uv.h>
#include "consts.h"


int main() {
    printf("Consumer started\n");
    sem_t *sem = sem_open(SEM_NAME, 0);
    if (!sem){
        printf("Semaphore not exist\n");
        perror("error: ");
        return -1;
    }
    char buf[1];
    u_int iteration = 0;
    while (1) {
        printf("Consumer waits\n");
        sem_wait(sem);
        printf("Iteration %d\n", iteration++);
        int fd = open("../main.txt", O_RDONLY, 0666);
        if (fd < 0){
            printf("Cannot open the file.");
            return -1;
        }
        read(fd, buf, 1);
        remove("../main.txt");
        write(1, buf, 1);
        write(1, buf, 1);
        write(1, buf, 1);
        write(1, "\n\n", 2);
    }
}
