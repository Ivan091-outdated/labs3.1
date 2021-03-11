#include <stdio.h>

extern void replace(char*, char, char);

int main (){
	char a[] = " qwe qwe qwe ";
	replace(a, ' ', '_');
	printf("%s", a);
	return 0;
	}
}

