#pragma once

#include <string>


class ClientState{
public:
    std::string root_path = "~/Student/semestr_6/TIN/Projekt/Program/TIN_FTP";
    std::string curr_d;
    std::string username;
    bool logged = false;
    int curr_operation = 0;

    
};