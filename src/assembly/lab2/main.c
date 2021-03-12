#include <stdio.h>

extern void replace(char*, char, char);

void replace2(char* str, char replaced, char replacing){
	for (int i = 0; str[i] != '\0'; i++) {
	if (str[i] == replaced)
		str[i] = replacing;
	}
}

void replace(char* str, char replaced, char replacing){
	for (char* i = str; *i != '\0'; i++){
	if (*i == replaced)
		*i = replacing;
	}
}

int main (){
	char a[] = "                                   ";
	for (int i = 0; i < 100000000; ++i){
	replace2(a, ' ', '_');
	}
}

