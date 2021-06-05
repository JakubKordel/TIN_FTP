#include "FileSystem.h"

#include <iostream>



int FileSystem::SaveFile(std::string full_path, std::string file_content){
    unsigned int start_filename = full_path.find_last_of(PATH_SEPARATOR);
    if(start_filename < 0 || start_filename >= full_path.length() - 1 ){
        // error - wrong path or filename
        return -1;
    }
    std::string filename = full_path.substr(start_filename+1);
    std::string dir_path = full_path.substr(0, start_filename);
    if(!VerifyPath(dir_path)){
        // error directory path doesnt exist
        return -1;
    }

    std::fstream fd;
    try{
        fd.open(full_path, std::ios_base::out);
    }catch(std::exception &e){
        // std::cout << e.what;
        return -1;
    }
    try{
        fd.write(&file_content[0], file_content.length());
    }catch(std::exception &e){
        //
        return -1;
    }
    fd.close();

    return 0;
}

int FileSystem::List(std::string &result, std::string curr_path){
    result.clear();

    if(curr_path.at(curr_path.length()-1) != '/') curr_path.push_back('/');

    if(!VerifyPath(curr_path)){
        // error - wrong path
        return -1;
    }

    try{
        for(auto& entry: fs::directory_iterator(curr_path)){
            std::string fs_obj = entry.path();
            result.append(fs_obj.replace(fs_obj.find_first_of(curr_path), curr_path.length(), "")).push_back('\n');
        }
    }catch(std::exception &e){
        return -1; // list error
    }
    


    return 0;
}

// you can 
int FileSystem::ChangeDirectory(std::string &result, std::string root_path, std::string curr_path, std::string dir){
    result.clear();
    if(dir.at(dir.length()-1) != '/') dir.push_back('/');

    std::string ncurr_path = curr_path;


    std::string single_dir = "";
    size_t idx_s = 0, idx_e = 0;
    do{
        size_t idx_e = dir.find_first_of('/', idx_s);
        single_dir.clear();
        if( idx_e != std::string::npos ){
            single_dir.append(dir.substr(idx_s, idx_e-idx_s+1));

            // std::cout << single_dir <<"\n";

            if( !single_dir.compare("../")){
                size_t last_bs = ncurr_path.find_last_of('/', ncurr_path.length()-2) +1;
                // std::cout << "last_bs: " << last_bs << "\tlength: " << ncurr_path.length() << "\n";
                ncurr_path.erase(last_bs, ncurr_path.length() - last_bs );
            }
            idx_s = idx_e + 1;
        }

    }while(idx_e != std::string::npos && idx_s < dir.length() && !single_dir.compare("../"));


    std::string bw_dir = "../";


    size_t first_not_bw_dir = dir.rfind(bw_dir)+bw_dir.length();


    // if(first_not_bw_dir != std::string::npos){
    //     std::cout << first_not_bw_dir <<"\n";
    // }

    if(first_not_bw_dir >= dir.length()){
        result.append(ncurr_path);
        // if there were only backward dirs then we have finished 
        return 0;
    }

    ncurr_path.append(dir.substr(first_not_bw_dir, dir.length() - first_not_bw_dir));

    std::string dirname = dir.substr(first_not_bw_dir, dir.length()-first_not_bw_dir);
    std::cout << dirname << "\n";

    // ncurr_path.append(dirname)

    // std::cout << ncurr_path << "\n";

    if( IsAboveRoot(root_path, ncurr_path) ){
        // if new current path is above the root_path (in files tree), it is an error
        return -1;
    }

    if( !VerifyPath(ncurr_path) ){
        std::cout << ncurr_path << "\n";
        // error directory not found
        return -2;
    }

    result.append(ncurr_path);
    return 0;
}

int FileSystem::GetFile(std::string &result, std::string path){
    result.clear();
    char *buffer = nullptr;

    if(!VerifyPath(path)){
        // error directory path doesnt exist
        return -1;
    }
    std::ifstream is;
    try{
        is.open(path, std::ifstream::in);
    }catch(std::exception &e){
        // std::cout << e.what;
        return -2;
    }
    try{
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);
        buffer = new char[length];

        // reading
        is.read(buffer, length);

        if(is){
            // all characters read succesfully
        }else{
            // error 
            std::cout << "error: only " << is.gcount() << " could be read\n";
            return -3;
        }

        result.append(buffer);
        std::cout << "read " <<result.length() << "bytes\n";
        free(buffer);

    }catch(std::exception &e){
        //
        return -4;
    }
    is.close();
    
    return 0;
}

int FileSystem::MakeDir(std::string curr_path, std::string dir_name){
    if(curr_path.at(curr_path.length()-1) != '/'){
        curr_path.push_back('/');
    }

    std::string full_path = curr_path.append(dir_name);
    if(VerifyPath(full_path)){ return 1; }
    if(!fs::create_directory(full_path)){
        return 2; // directory is not created
    }
    return 0;
}


bool FileSystem::VerifyPath(std::string path){
    return fs::exists(path);
}

bool FileSystem::IsAboveRoot(std::string root_path, std::string curr_path){
    if(curr_path.find(root_path)==std::string::npos) return true;
    return false;
}