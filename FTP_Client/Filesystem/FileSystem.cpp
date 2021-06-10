#include "FileSystem.h"

#include <iostream>



int FileSystem::SaveFile(std::string full_path, std::string file_content){
    std::string filename;
    std::string dir_path;
    if( full_path[0] == '/' ) full_path = full_path.substr(1, full_path.length()-1);
    size_t start_filename = full_path.find_last_of(PATH_SEPARATOR);
    if( start_filename == full_path.length() - 1 ){
        // error - wrong path or filename
        return 1;
    }
    if( start_filename == std::string::npos ) {
        start_filename = 0;
        dir_path.clear();
    }else{
        dir_path = full_path.substr(0, start_filename);
    }
    filename = full_path.substr(start_filename+1);
    if( !dir_path.empty() && !VerifyPath(dir_path)){
        // error directory path doesnt exist
        return 2;
    }

    std::fstream fd;
    try{
        fd.open(full_path, std::ios_base::out);
    }catch(std::exception &e){
        // std::cout << e.what;
        return 3;
    }
    try{
        fd.write(&file_content[0], file_content.length());
    }catch(std::exception &e){
        //
        return 4;
    }
    fd.close();

    return 0;
}

int FileSystem::List(std::string &result, std::string curr_path){
    result.clear();
    if( curr_path.at(curr_path.length()-1) !='/' ){
        curr_path.push_back('/');
    }

    std::cout << curr_path << "\n";

    if(curr_path.at(curr_path.length()-1) != '/') curr_path.push_back('/');

    if(!pathRelExists(curr_path)){
        // error - wrong path
        return 1;
    }

    try{
        for(auto& entry: fs::directory_iterator(curr_path)){
            std::string fs_obj = entry.path();
            result.append(fs_obj.replace(fs_obj.find_first_of(curr_path), curr_path.length(), "")).push_back('\n');
        }
    }catch(std::exception &e){
        return 2; // list error
    }
    
    return 0;
}

/* return
 * 0 - success
 * 1 - directory unavailable
 * 2 - directory not found
*/
int FileSystem::ChangeDirectory(std::string &result, std::string root_path, std::string curr_path, std::string dir){

    std::cout << "root_path\t" << root_path <<"\n";
    std::cout << "curr_path\t" << curr_path <<"\n";
    std::cout << "dir\t" << dir <<"\n";

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
            if( !single_dir.compare("../")){
                size_t last_bs = ncurr_path.find_last_of('/', ncurr_path.length()-2) +1;
                ncurr_path.erase(last_bs, ncurr_path.length() - last_bs );
            }
            idx_s = idx_e + 1;
        }

    }while(idx_e != std::string::npos && idx_s < dir.length() && !single_dir.compare("../"));

    
    std::cout << ncurr_path << "\n";


    if( IsAboveRoot(root_path, ncurr_path) ){
        // if new current path is above the root_path (in files tree), it is an error
        return 1;
    }

    std::string bw_dir = "../";
    size_t first_not_bw_dir = dir.rfind(bw_dir);
    if(first_not_bw_dir != std::string::npos ){
        first_not_bw_dir += bw_dir.length();
    }
    
    if( first_not_bw_dir!=std::string::npos && first_not_bw_dir >= dir.length()){
        // result.append(ncurr_path);
        // if there were only backward dirs then we have finished 
    }else if(first_not_bw_dir == std::string::npos ){
        if(ncurr_path.at(ncurr_path.size()-1)!='/' && dir.at(0)!='/') ncurr_path.push_back('/');
        ncurr_path.append(dir);
        // result.append(ncurr_path);
    }else{
        std::string ndir = dir.substr(first_not_bw_dir, dir.length() - first_not_bw_dir);
        if(ncurr_path.at(ncurr_path.size()-1)!='/' && ndir.at(0)!='/') ncurr_path.push_back('/');
        ncurr_path.append(ndir);
    }

    if( !pathRelExists(ncurr_path) ){
        // error directory not found
        std::cout << ncurr_path << "\n";
        return 2;
    }

    result.append(ncurr_path);
    return 0;
}

int FileSystem::GetFile(std::string &result, std::string path){
    if( path[0] == '/' ) path = path.substr(1, path.length()-1 );
    result.clear();
    char *buffer = nullptr;

    if(!VerifyPath(path)){
        // error directory path doesnt exist
        return 1;
    }
    std::ifstream is;
    try{
        is.open(path, std::ifstream::in);
    }catch(std::exception &e){
        // std::cout << e.what;
        return 2;
    }
    try{
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);
        buffer = new char[length + 1] {0}; //zainicjalizowane zerami

        // reading
        is.read(buffer, length);

        if(is){
            // all characters read succesfully
        }else{
            // error 
            std::cout << "error: only " << is.gcount() << " could be read\n";
            return 3;
        }

        result.append(buffer);
        free(buffer);

    }catch(std::exception &e){
        //
        return 4;
    }
    is.close();
    
    return 0;
}

/* return:
 * 0 - success
 * 1 - wrong path
 * 2 - directory already exists
 * 3 - server error
*/
int FileSystem::MakeDir(std::string curr_path, std::string dir_name){
    if(curr_path.at(curr_path.length()-1) != '/'){
        curr_path.push_back('/');
    }

    if(!VerifyPath(curr_path)){ return 1; }
    std::string full_path = curr_path.append(dir_name);
    if(VerifyPath(full_path)){ return 2; }
    if(!fs::create_directory(full_path)){
        return 3; // directory is not created
    }
    return 0;
}

bool FileSystem::pathRelExists(std::string path){
    std::string full_path = fs::current_path();
    if(full_path.at(full_path.size()-1)!='/') full_path.push_back('/');
    full_path.append(path);
    std::cout << full_path << "\t full_path\n";
    return fs::exists(full_path);
}

bool FileSystem::VerifyPath(std::string path){
    // std::string full_path = fs::current_path();
    return fs::exists(path);// || full_path.find(path) == full_path.length()-path.length();
}

bool FileSystem::IsAboveRoot(std::string root_path, std::string curr_path){
    if(curr_path.empty() && !root_path.empty()) return true;
    if(curr_path.at(0)!='/') curr_path.insert(curr_path.begin(), '/');
    if(curr_path.find(root_path)==std::string::npos) return true;
    return false;
}
