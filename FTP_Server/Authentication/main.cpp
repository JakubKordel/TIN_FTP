#include <iostream>

#include <string>
#include <sstream>
#include <iomanip>

#include "HashFunctions/passwordHashing.h"
#include "Userbase.h"

int main()
{
    Userbase base("login_db.csv");
    std::cout << "zbigniew: " << base.exists("zbigniew.zuch", getHashedPassword("zuch")) << std::endl;
    std::cout <<  "wm: " << base.exists("wm", getHashedPassword("wm")) << std::endl;
    std::cout <<  "ckonopcz: " << base.exists("ckonopcz", getHashedPassword("ck")) << std::endl;
    std::cout <<  "kacper: " << base.exists("kacpernowak", getHashedPassword("nowak")) << std::endl;
    std::cout <<  "jan: " << base.exists("j.kowalski", getHashedPassword("haslo")) << std::endl;
    std::cout << "jan with wrong pass: " << base.exists("j.kowalski", getHashedPassword("wrong_password")) << std::endl;
    std::cout << "kacper with wrong login: " << base.exists("kacper", getHashedPassword("nowak")) << std::endl;

    std::cout << std::endl;
    return 0;
}
