#include <iostream>

int main() {
	float a = 1000;
	float b = 0.0001;
	float res = (( a + b ) * ( a + b ) - ( a * a + 2 * a * b )) / ( b * b );
	std::cout << res << std::endl;
	return 0;
}

