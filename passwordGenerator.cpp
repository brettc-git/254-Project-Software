// Used for implementing somewhere else later

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

std::string passwordGenerator(int length) {
	const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_-+={[}]|:;\"'<,>.?/\\";
	std::random_device random;
	std::mt19937 generator(random());
	std::uniform_int_distribution<> distribution(0, chars.size() - 1);

	std::string pass;

	for (int i = 0; i < length; ++i) {
	
		pass += chars[distribution(generator)];
	}

	return pass;
}

int main() {
	srand(time(0));
	std::cout << "Entering a length for password: " << std::endl;
	std::string first_p = passwordGenerator(14);
	std::cout << first_p;

	return 0;
}
