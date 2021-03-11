#include <iostream>

int main() {
	int m = 3;
	int n = 4;

	std::cout << m+++n << std::endl;
	
	std::cout << (n-- > m) << std::endl;

	std::cout << (m-- > n) << std::endl;

	return 0;
}

