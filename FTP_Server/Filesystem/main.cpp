#include <iostream>

//#include "FileSystem.h"

 #include <filesystem>
// #include <fstream>
// #include <vector>

namespace fs = std::filesystem;

int main(){
    
    // std::string root_path = "/home/student/Student/semestr_6/TIN/Projekt/Program/TIN_FTP/";
    // std::string curr_path = "/home/student/Student/semestr_6/TIN/Projekt/Program/TIN_FTP/FTP_Server/Filesystem/";
    // std::string dir = "../../";

    std::string root_path = "/test/";
    std::string curr_path = "test/test_subdir";
    std::string dir = "../";

    // std::string content = "Zwykly krotki tekscik, ktory pewnie \nmoglby zmiescic sie w jednej linii\n ale wole rozbic go na 3 wersy ;p";

    // SaveFile test
    // int res_save_file_function = FileSystem::SaveFile(curr_path.append("/file.txt"), content);
    // std::cout << "SaveFile function:\t:" << res_save_file_function << "\n";
    
    std::string relative_path = "wm";

    std::string files;
    
    //std::string sciezka = "/home/student/Student/semestr_6/TIN/Projekt/Program/TIN_FTP/root_path/wm/test";
    std::string sciezka = fs::current_path();
    
    std::cout << sciezka << "\n";
    
    std::cout << "exists\t" << fs::exists(sciezka) << "\n";

    // // List test
    // int res_list_function = FileSystem::List(files, relative_path);
    // std::cout << "List function\t:" << res_list_function << "\n";
    // std::cout << files;
    // std::cout << files.length() << "\n";

    

    // // ChangeDirectory test
    // std::string n_path;
    // int res_change_directory_function = FileSystem::ChangeDirectory(n_path, root_path, curr_path, dir);
    // std::cout << "ChangeDirectory function\t:" << res_change_directory_function << "\n";
    // std::cout << "New directory: " << n_path << "\n";


    // // GetFile test
    // std::string file_content;
    // int res_get_file_function = FileSystem::GetFile(file_content, curr_path.append("file.txt"));
    // std::cout << "GetFile function\n:" << res_get_file_function <<"\n";
    // std::cout << "File content: \n" << file_content << "\n";

    // // MakeDir test
    // int res_make_dir_function = FileSystem::MakeDir(curr_path, "NowyKatalog");
    // std::cout << "MakeDir\t:" << res_make_dir_function << "\n";

    //
    // std::cout << ndir;

    return 0;
}
