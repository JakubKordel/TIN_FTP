#include "FileSystem.h"
#include <iostream>

// #include <filesystem>
// #include <fstream>
// #include <vector>

namespace fs = std::filesystem;

int main(){
    
    std::string root_path = "/home/student/Student/semestr_6/TIN/Projekt/Program/TIN_FTP/";

    std::string curr_path = "/home/student/Student/semestr_6/TIN/Projekt/Program/TIN_FTP/FTP_Server/Filesystem";

    std::string dir = "../../libs";

    // std::string content = "Zwykly krotki tekscik, ktory pewnie \nmoglby zmiescic sie w jednej linii\n ale wole rozbic go na 3 wersy ;p";

    // if(!FileSystem::SaveFile(str_path, content)){
    //     std::cout << "Success\n";
    // } else std::cout << "Error\n";

    // std::string read_content = FileSystem::GetFile(str_path);

    // std::cout << read_content;

    // fs::directory_iterator(str_path);

    // test List function
    // std::string files = FileSystem::List(str_path);

    // test ChangeDirectory function
    // std::string ndir = FileSystem::ChangeDirectory(root_path, curr_path, dir);

    // test MakeDir function
    if(FileSystem::MakeDir(curr_path, "Test_dir/")){
        std::cout << "Success\n";
    }else{
        std::cout << "Error\n";
    }

    // std::cout << ndir;

    return 0;
}