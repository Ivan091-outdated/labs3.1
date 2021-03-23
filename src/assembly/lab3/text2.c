#include "stdio.h"

int main(){
    char text[] = "1Some text2";
    for (char i = 0; text[i] != '\0'; i++){
        if (text[i] == ' ')
            text[i] = '_';
    }
    printf("%s", "asd");
}