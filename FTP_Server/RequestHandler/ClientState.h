#pragma once

#include <string>


class ClientState{
public:
    std::string root_path = "ftp_root/";
    std::string curr_path;
    std::string username;
    bool logged = false;
    int curr_operation = 0;// it is unused

    const std::string GetRootPath(){ return root_path; }
    const std::string GetCurrPath(){ return curr_path; }
    const std::string GetUsername(){ return username; }
    const bool IsLogged(){ return logged; }
    const int GetCurrOperation(){ return curr_operation; }

    void SetRootPath(std::string n_path){ root_path = n_path; }
    void SetCurrPath(std::string n_curr){ curr_path = n_curr; }
    void SetUsername(std::string n_user){ username = n_user; }
    void SetLogged(){ logged = true; }
    void ResetLogged(){ logged = false; }
    void SetCurrOperation( int n_currop ){ curr_operation = n_currop; }

};