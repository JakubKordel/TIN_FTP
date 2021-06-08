#include <string>
#include <fstream>
#include <exception>

// jesli <filesystem> nieobslugiwany

// #include <experimental/filesystem>
// namespace fs = std::experimental::filesystem;

// * * * * * * * * * * * *

// jesli <filesystem> obslugiwany
#include <filesystem>
namespace fs = std::filesystem;




class FileSystem{

public:
    static int SaveFile( std::string full_path, std::string file_content);// curr_path.nazwa pliku
    static int List( std::string &result, std::string curr_path);
    static int ChangeDirectory( std::string &result, std::string root_path, std::string curr_path, std::string dir);
    static int GetFile( std::string &result, std::string path);
    static int MakeDir(std::string path, std::string dir_name);
    static bool pathRelExists(std::string path);// checks relative path
private:
    static bool VerifyPath(std::string path);
    static bool IsAboveRoot(std::string root_path, std::string curr_path);
    static const char PATH_SEPARATOR = '/';
};
