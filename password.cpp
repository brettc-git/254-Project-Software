#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <random>
#include <string>
#include <fstream>
#include "password.h"

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
std::string passwordGenerator(int length, bool upper, bool num, bool special) {
	// By default the password will have lowercase letters only

	// All possible characters for a pssword 

	// Characters < and > are excluded since they can cause problems for web browsers
	const std::string LOWER = "abcdefghijklmnopqrstuvwxyz";
	const std::string UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const std::string NUMBERS = "0123456789";
	const std::string SPECIAL = "!@#$%^&*()_-+={[}]|:;\"',.?/\\";

	std::string allPossibleChars = LOWER;

	// Incrementally add types of characters based on if booleans are true are false (exclude if false)
	if (upper) 
		allPossibleChars += UPPER;
	if (num)
		allPossibleChars += NUMBERS;
	if (special)
		allPossibleChars += SPECIAL;

	// Random generator for our password
	std::random_device random;
	std::mt19937 generator(random());
	std::uniform_int_distribution<> distribution(0, allPossibleChars.size() - 1);

	// Our password variable

	std::string pass;
	do {
		// Initialize password with empty, to be filled later with for loop
		pass = "";
		for (int i = 0; i < length; ++i) {
			// Append characters from the distribution of chars to make the password	
			pass += allPossibleChars[distribution(generator)];
		}

		bool valid = true;

		// Check if valid is consistently true (for example if all bools are true), in order to meet requirements 
		if (upper)
			valid = valid && containsUpper(pass);
		if (num)
			valid = valid && containsNumber(pass);
		if (special)
			valid = valid && containsSpecial(pass);

		if (valid)
			break;

		// Loop breaks until valid is true, if successful loop only happens once
	} while (true);

	// Return when at least once special character is found in password
	return pass;
}

