// Used for implementing somewhere else later

#include <iostream>
#include <cstdlib>
#include <ctime>

std::string passwordGenerator(int length) {
	std::string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string numeric = "0123456789";
	std::string special = "~`!@#$%^&*()_-+={[}]|:;\"'<,>.?/\\";
}

int main() {
	srand(time(0));
	passwordGenerator(15);
	std::cout 
	return 0;
}
