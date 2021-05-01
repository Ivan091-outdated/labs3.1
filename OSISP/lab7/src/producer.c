#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <uv.h>
#include "consts.h"


int main() {
    printf("Producer started\n");
    sem_unlink(SEM_NAME);
    sem_t *sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0666, 0);
    if (!sem) {
        printf("Cannot open semaphore\n");
        perror("error: ");
        return 1;
    }
    u_int iteration = 0;
    char buf[1];
    while (1){
        printf("Producer waits input\n");
        read(0, buf, 10);
        printf("Iteration %d\n", iteration++);
        int fd = open("../main.txt", O_WRONLY | O_CREAT, 0666);
        if (fd < 0){
            printf("Cannot open the file");
            return -1;
        }
        write(fd, buf, 1);
        close(fd);
        printf("Producer posts\n");
        sem_post(sem);
    }
}
