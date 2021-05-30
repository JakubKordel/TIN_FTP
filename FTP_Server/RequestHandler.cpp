#include "RequestHandler.h"
// #include "ErrorDetector.h"

/* return struct Response described in ServiceProvider.h 
*/
struct Response ServiceProvider::ProvideService(std::string request){
    Response response;
    response.err_code = 0;
    int result = ParseCommand(request);

    
    


    ClearLastOperation();

    return response;
}

int ServiceProvider::ParseOperation(std::commstring request){
    int len = request.find_first_of(' ', 0)+1;
    int operation;
    try{
        if( len>0 )
            operation = std::stoi(request.substr(0, len));
    }
    catch(std::exception &err){
        perror("ServiceProvider::ParseOperation");
        operation = -1;
    }
    return operation;
}

int ServiceProvider::ParseCommand( std::string request){

    curr_operation = ParseOperation(request);
    int arg_nr = 0;
    int start_arg = 0;
    while(start_arg>=0 && arg_nr < MAX_OF_ARGS ){
        start_arg = request.find_first_of(' ', start_arg);
        if( request.length()+1 > start_arg ){
            int end_arg = request.find_first_of(' ', start_arg+1);
            std::string arg = request.substr(start_arg+1, end_arg);
            arguments.push_back(arg);
            start_arg = start_arg + 1;
        }
        arg_nr+=1;
    }
    
    return 0;
}

int ServiceProvider::VerifyCommand(){
    // ErrorDetector.
    // switch(curr_operation){
    //     case Operation::help:

    //         break;
    //     case Operation::cd:

    //         break;
    //     case Operation::get:

    //         break;
    //     case Operation::login:

    //         break;
    //     case Operation::logout:

    //         break;
    //     case Operation::ls:

    //         break;
    //     case Operation::mkd:

    //         break;
    //     case Operation::put:

    //         break;
    //     default:
    //         // unknown operation
    //         // err = 
    //         break;
    // }
    return 0;
}

// int ServiceProvider::CheckNrOfArgs(int nr_args){
//     return arguments.size() == nr_args;
// }

int ServiceProvider::ClearLastOperation(){
    curr_operation = 0;
    arguments.clear();
    err = 0;
}

// int ServiceProvider::DoWork(std::string resp_str){

//     return 0;
// }