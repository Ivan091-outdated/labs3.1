#include <iostream>

int main() {
	double a = 1000;
	double b = 0.0001;
	double res = (( a + b ) * ( a + b ) - ( a * a + 2 * a * b )) / ( b * b );
	std::cout << res << std::endl;
	return 0;
}

