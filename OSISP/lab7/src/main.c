#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>



int main()
{
    sem_t mutex;
    sem_init(&mutex, 0, 0);
    int times = 10;

    pid_t pid;
    if ((pid = fork()) < 0) {
        printf("Fork Failed\n");
        exit(1);

    }

        /* Child Process */
    else if (pid != 0) {
        for (int i = 0; i < times; ++i){
            printf("File before wait\n");
            sem_wait(&mutex);
            printf("File after wait\n");
            char buf[1];
            read(0, buf, 1);
            int fd = open("../main.txt", O_WRONLY | O_CREAT, 0666);
            write(fd, "1", 1);
            close(fd);
            printf("File before post\n");
            sem_post(&mutex);
            printf("File after post\n");
        }
    }
        /* Parent Process */
    else {

        for (int i = 0; i < times; ++i){
            printf("Console before wait\n");
            sem_wait(&mutex);
            printf("Console after wait\n");
            int fd = open("../main.txt", O_RDONLY, 0666);
            char buf[1];
            read(fd, buf, 1);
            close(fd);
            remove("../main.txt");
            write(1, buf, 1);
            printf("Console before post\n");
            sem_post(&mutex);
            printf("Console after post\n");
        }
    }
    return 0;
}
