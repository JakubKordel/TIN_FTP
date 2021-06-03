#include "Authentication.h"

bool Authentication::login(std::string username, std::string password){
    std::string file_path = PASS_FILE_PATH;
    file_path.append(PASS_FILE_NAME);
    Userbase base(file_path);
    return base.exists(username, password);
}