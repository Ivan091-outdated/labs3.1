#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <uv.h>
#include "consts.h"


int main() {
    printf("Producer started\n");
    sem_unlink(PRODUCER_SEM_NAME);
    sem_unlink(CONSUMER_SEM_NAME);
    sem_unlink(TRANSFER_SEM_NAME);
    sem_t *producerSem = sem_open(PRODUCER_SEM_NAME, O_CREAT | O_EXCL, 0666, 1);
    sem_t *consumerSem = sem_open(CONSUMER_SEM_NAME, O_CREAT | O_EXCL, 0666, 0);
    sem_t *transferSem = sem_open(TRANSFER_SEM_NAME, O_CREAT | O_EXCL, 0666, 0);

    u_int iteration = 0;
    char buf[1];
    while (1){
        sem_wait(producerSem);
        printf("Producer waits input\n");
        read(0, buf, 10);
        printf("Iteration %d\n", iteration++);
        sem_init(transferSem, 1, buf[0]);
        printf("Producer posts\n");
        sem_post(consumerSem);
    }
}
