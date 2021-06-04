#pragma once

#include "sha1.h"
#include <string>

void sha1(BYTE* buf, BYTE* data, size_t len);
void hashString(BYTE* buf, std::string str);
std::string getHashedPassword(std::string password);
