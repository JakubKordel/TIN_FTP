#pragma once

#include <string>


class ClientState{
public:
    const std::string root_path = "ftp_root/"; 

    std::string root_path_user;
    std::string curr_path;
    std::string username;
    bool logged = false;
    int curr_operation = 0;// it is unused

    const std::string GetRootPath(){ return root_path; }
    const std::string GetCurrPath(){ return curr_path; }
    const std::string GetUsername(){ return username; }
    const std::string GetRootPathUser() { return root_path_user; }
    const bool IsLogged(){ return logged; }
    const int GetCurrOperation(){ return curr_operation; }

    // void SetRootPath(std::string n_path){ root_path = n_path; }
    void SetRootPathUser(std::string n_path) {root_path_user = n_path; }
    void SetCurrPath(std::string n_curr){ curr_path = n_curr; }
    void SetUsername(std::string n_user){ username = n_user; }
    void SetLogged(){ logged = true; }
    void ResetLogged(){ logged = false; }
    void SetCurrOperation( int n_currop ){ curr_operation = n_currop; }

    

};