// Implement Somewhere else Later

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <fstream>

// Checks if our password has a special character, returns true if a single one is found, false if there are none 
bool containsSpecial(const std::string our_string) {
	for (char c : our_string) {
		if (!std::isalnum(c))
			return true;
	}
	return false;
}

bool containsUpper(const std::string our_string) {
	for (char c : our_string) {
		if (!std::isupper(c))
			return true;
	}
	return false;
}

bool containsNumber(const std::string our_string) {

	for (char c : our_string) {
		if (!std::isdigit(c))
			return true;
	}
	return false;
}

bool containsLower(const std::string our_string) {
	for (char c : our_string) {
		if (!std::islower(c))
			return true;
	}
	return false;
}
std::string passwordGenerator(int length) {

	if (length < 8) {
		return "ERROR";
	}
	// All possible characters for a pssword 

	// Characters < and > are excluded since they can cause problems for web browsers
	const std::string CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_-+={[}]|:;\"',.?/\\";

	// Random generator 
	std::random_device random;
	std::mt19937 generator(random());
	std::uniform_int_distribution<> distribution(0, CHARS.size() - 1);

	// Our password variable

	std::string pass;
	do {
		// Initialize password with empty, will be empty again if password doesn't contain special character
		pass = "";
		for (int i = 0; i < length; ++i) {
			// Append characters from the distribution of chars to make the password	
			pass += CHARS[distribution(generator)];
		}

		// Our password in this generator should contain at least one special character
		/*if containsSpecial(pass) == false*/
	} while (containsSpecial(pass) == false || containsUpper(pass) == false || containsNumber(pass) == false || containsLower(pass) == false);

	// Return when at least once special character is found in password
	return pass;
}



int main() {
	srand(time(0));

	std::ofstream Myfile("ourpasswords.txt");

	if (!Myfile.is_open()) {
		std::cerr << "File not found. Error.";
		return 1;
	}

	std::string line; 
	int num_of_pwds = 14;
	int batch_length = 20;
	std::cout << "Specifying how many passwords: " << num_of_pwds << std::endl;
	std::cout << "of length: " << batch_length << std::endl;

	for (size_t i = 0; i < num_of_pwds; i++) {
		Myfile << passwordGenerator(batch_length) << std::endl;
	}

	std::cout << "All " << num_of_pwds << " passwords successfully generated.";
	Myfile.close();

	/*std::cout << "Entering a length for password: " << std::endl;
	std::string first_p = passwordGenerator(23);
	if (first_p != "ERROR")
		std::cout << first_p;
	else
		std::cout << "Password too short!";*/
	return 0;
}
