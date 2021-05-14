#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <uv.h>

int isLast(int len, int idx) {
    return idx == len;
}

int isEnd(const char *buf, int len, int idx) {
    return idx > len || buf[idx] == '\0';
}

void replaceAll(char *buf, int start, int end, char oldSymbol, char newSymbol) {
    for (int i = start; i < end; i++) {
        if (buf[i] == oldSymbol) buf[i] = newSymbol;
    }
}

int main(int argc, char *argv[]) {
    int bufSize = 1024;
    char buf[1024];
    bzero(buf, bufSize);
    int fd = 0;
    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
        if (fd < 0){
            printf("Cannot open file\n");
            return -1;
        }
    }
    read(fd, buf, bufSize);
    close(fd);
    size_t len = strlen(buf);
    int l = 0;
    int r = 1;

    while (!isEnd(buf, bufSize, r)) {
        while (buf[r] != '\n' && !isEnd(buf, len, r)) r++;
        if (!isLast(len, r)) if (isEnd(buf, len, r)) break;
        if (isdigit(buf[l])) {
            replaceAll(buf, l, r, 'X', 'Y');
            write(1, &buf[l], r - l + 1);
        }
        l = ++r;
    }
}
