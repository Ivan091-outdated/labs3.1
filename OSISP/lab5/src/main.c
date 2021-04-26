#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <uv.h>

ssize_t writeToEnd(int fd, char* buf, int bufSize){
    int l = 0;
    int r = 0;
    while (buf[r] != '\0' && r < bufSize){
        r++;
    }
    return write(fd, buf, r - l);
}

int main() {
    int bufSize = 255;
    int numSize = 10;
    char buf[bufSize];
    char num[numSize];
    bzero(num, numSize);
    bzero(buf, bufSize);
    int fd = 1;
    (void)umask(0);
    int fdOdd = open("odd", O_WRONLY | O_CREAT, 0666);
    int fdEven = open("even", O_WRONLY | O_CREAT, 0666);
    if (fdOdd < 0 || fdEven < 0){
        printf("Cannot open a file.");
        return -1;
    }

    for (int i = 0; read(0, buf, bufSize) != 0; bzero(buf, bufSize)){
        int l = 0;
        int r = 0;
        while (1){
            while (buf[r] != '\n' && buf[r] != '\0' && r < bufSize){
                r++;
            }

            if (buf[r] == '\0' || r == bufSize){
                break;
            }
            sprintf(num, "%d. ", i);

            if (i % 2 == 0){
                fd = fdEven;
            } else {
                fd = fdOdd;
            }

            writeToEnd(fd, num, numSize);
            write(fd, &buf[l], r - l + 1);
            i++;
            l = ++r;
        }
    }
    if (close(fdOdd) < 0 || close(fdEven) < 0){
        printf("Cannot close a file.");
        return -1;
    }
}
