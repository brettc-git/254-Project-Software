#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>

bool containsSpecial(const std::string our_string);
bool containsUpper(const std::string our_string);
bool containsNumber(const std::string our_string);
std::string passwordGenerator(int length, bool upper, bool num, bool special);

#endif
