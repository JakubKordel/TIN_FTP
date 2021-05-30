#pragma once

#include <string>
#include <exception>
#include <vector>


class ServiceProvider{

    bool logged = false;
    std::string username;
    std::string curr_dir;

    int curr_operation = 0;
    int err = 0;
    std::vector<std::string> arguments; 

public:
    struct Response ProvideService(std::string request);

private:

    int ParseCommand( std::string request);
    int ParseOperation(std::string request);
    int VerifyCommand();
    int CheckNrOfArgs(int nr_args);
    int ClearLastOperation();

    //  int DoWork(std::string &resp_str);

    const int MAX_OF_ARGS = 2;
};

enum Operation{
    help = 0,
    put = 1,
    get = 2,
    login = 3,
    logout = 4,
    mkd = 5,
    cd = 6,
    ls = 7
};

struct Response{
    int err_code;               // 0 if correct; error code otherwise
    int operation;        // code (enum) of operation client asks for
    std::string msg_response;   // response to send to client
};

