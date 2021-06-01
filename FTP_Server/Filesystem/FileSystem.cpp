#include "FileSystem.h"

#include <iostream>

int FileSystem::SaveFile(std::string full_path, std::string file_content){
    int start_filename = full_path.find_last_of(PATH_SEPARATOR);
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
    }catch(std::exception e){
        // std::cout << e.what;
        return -1;
    }
    try{
        fd.write(&file_content[0], file_content.length());
    }catch(std::exception e){
        //
        return -1;
    }
    fd.close();

    return 0;
}

std::string FileSystem::List(std::string curr_path){
    std::string result = "";

    if(!VerifyPath(curr_path)){
        // error
        return result;
    }

    for(auto& entry: fs::directory_iterator(curr_path)){
        std::string fs_obj = entry.path();
        result.append(fs_obj.replace(fs_obj.find_first_of(curr_path), curr_path.length(), "")).push_back('\n');
    }


    return result;
}

std::string FileSystem::ChangeDirectory(std::string root_path, std::string curr_path, std::string dir){
    if(dir.at(dir.length()-1) == '/') dir.pop_back();

    std::string ncurr_path = curr_path;


    std::string single_dir = "";
    size_t idx_s = 0, idx_e = 0;
    do{
        size_t idx_e = dir.find_first_of('/', idx_s);
        single_dir.clear();
        if( idx_e != std::string::npos ){
            single_dir.append(dir.substr(idx_s, idx_e-idx_s+1));

            std::cout << single_dir <<"\n";

            if( !single_dir.compare("../")){
                size_t last_bs = ncurr_path.find_last_of('/', ncurr_path.length()-2);
                ncurr_path.erase(last_bs, ncurr_path.length() - last_bs - 1 );
            }
            idx_s = idx_e + 1;
        }

    }while(idx_e != std::string::npos && idx_s < dir.length() && !single_dir.compare("../"));


    std::string bw_dir = "../";

    size_t first_not_bw_dir = dir.find_last_of(bw_dir) + 1;

    if(first_not_bw_dir != std::string::npos){
        std::cout << first_not_bw_dir <<"\n";
    }

    if(first_not_bw_dir >= dir.length()){
        return ncurr_path;
    }

    ncurr_path.append(dir.substr(first_not_bw_dir, dir.length() - first_not_bw_dir));

    if( IsAboveRoot(root_path, ncurr_path) ){
        return std::string("-1");
    }

    if( !VerifyPath(ncurr_path) ){
        // error directory not found
        return std::string("-1");
    }

    return ncurr_path;
}

std::string FileSystem::GetFile(std::string path){
    std::string result = "";
    char *buffer = nullptr;

    if(!VerifyPath(path)){
        // error directory path doesnt exist
        return result;
    }
    std::ifstream is;
    try{
        is.open(path, std::ifstream::in);
    }catch(std::exception e){
        // std::cout << e.what;
        return result;
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
            return result;
        }

        result.append(buffer);
        std::cout << "read " <<result.length() << "bytes\n";
        free(buffer);

    }catch(std::exception e){
        //
        return result;
    }
    is.close();

    return result;
}

bool FileSystem::MakeDir(std::string curr_path, std::string dir_name){
    int result = false;
    if(curr_path.at(curr_path.length()-1) != '/'){
        curr_path.push_back('/');
    }
    std::string full_path = curr_path.append(dir_name);
    try{
        result = fs::create_directory(full_path);
    }catch( std::exception e ){
        std::cout << e.what() << " FileSystem::MakeDir\n";
        return false;
    }


    return result;
}


bool FileSystem::VerifyPath(std::string path){
    return fs::exists(path);
}

bool FileSystem::IsAboveRoot(std::string root_path, std::string curr_path){
    if(curr_path.compare(root_path) < 0 || curr_path.length() < root_path.length()) return true;
    return false;
}