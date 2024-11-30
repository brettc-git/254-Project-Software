// Used for implementing somewhere else later

#include <iostream>
#include <cstdlib>
#include <ctime>

std::string passwordGenerator(int length) {
	std::string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string numeric = "0123456789";
	std::string special = "~`!@#$%^&*()_-+={[}]|:;\"'<,>.?/\\";
	std::string pass;

}

int main() {
	srand(time(0));
	std::cout << "Entering a length for password: " << std::endl;
	std::string first_p = passwordGenerator(14);

	return 0;
}
