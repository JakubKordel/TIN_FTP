#pragma once

#include <iostream>

#include <string>
#include <sstream>
#include <iomanip>

#include "HashFunctions/passwordHashing.h"
#include "Database.h"

class Authentication{

public:

    bool login(std::string username, std::string password);

    const std::string PASS_FILE_PATH = "FTP_Server/Authentication/";
    const std::string PASS_FILE_NAME = "login_db.csv";

};
