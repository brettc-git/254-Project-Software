// Used for implementing somewhere else later

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

std::string passwordGenerator(int length) {

	if (length < 5) {
		return "ERROR";
	}
	// All possible characters for a pssword 

	const std::string CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_-+={[}]|:;\"'<,>.?/\\";

	// Random generator 
	std::random_device random;
	std::mt19937 generator(random());
	std::uniform_int_distribution<> distribution(0, CHARS.size() - 1);


	std::string pass;

	for (int i = 0; i < length; ++i) {
		// Append characters from the distribution of chars to make the password	
		pass += CHARS[distribution(generator)];
	}
	return pass;
}

int main() {
	srand(time(0));
	std::cout << "Entering a length for password: " << std::endl;
	std::string first_p = passwordGenerator(2);
	if (first_p != "ERROR")
		std::cout << first_p;
	else
		std::cout << "Password too short!";
	return 0;
}
