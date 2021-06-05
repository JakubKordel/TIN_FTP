#pragma once

#include <iostream>

#include <string>
#include <sstream>
#include <iomanip>

#include "HashFunctions/passwordHashing.h"
#include "Database.h"

class AuthenticationDB: Database{
    bool opened = false;
    const std::string DB_PATH = "ftp_root/login_db.csv";
    
public:
    AuthenticationDB(): Database(){
        if(openDB(DB_PATH)){
            opened = true;
        }
    }
    bool login(std::string username, std::string password);

private:
    // const std::string PASS_FILE_NAME = "login_db.csv";

};
