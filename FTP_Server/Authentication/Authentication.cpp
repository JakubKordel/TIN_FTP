#include "Authentication.h"

bool Authentication::login(std::string username, std::string password){
    Database base("login_db.csv");
    return base.exists(username, password);
}