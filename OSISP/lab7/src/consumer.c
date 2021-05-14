#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <uv.h>
#include "consts.h"


int main() {
    printf("Consumer started\n");
    sem_t *producerSem = sem_open(PRODUCER_SEM_NAME, 0);
    sem_t *consumerSem = sem_open(CONSUMER_SEM_NAME, 0);
    sem_t *transferSem = sem_open(TRANSFER_SEM_NAME, 0);

    u_int iteration = 0;
    char buf[2] = ".\n";
    int intBuf[1];
    while (1) {
        printf("Consumer waits\n");
        sem_wait(consumerSem);
        printf("Iteration %d\n", iteration++);
        sem_getvalue(transferSem, intBuf);
        buf[0] = (char)intBuf[0];
        write(0, buf, 2);
        sem_post(producerSem);
    }
}
