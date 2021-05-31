#pragma once

#include <iostream>

#include <string>
#include <sstream>
#include <iomanip>

#include "HashFunctions/passwordHashing.h"
#include "Userbase.h"

class Authentication{

public:

    bool login(std::string username, std::string password);

};