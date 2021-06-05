#include "AuthenticationDB.h"

bool AuthenticationDB::login(std::string username, std::string password){
    if( opened ){
        return exists(username, getHashedPassword(password));
    }else{
        return false;
    }
}
