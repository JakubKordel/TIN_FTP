#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <exception>

namespace fs = std::filesystem;

class FileSystem{

public:
    static int SaveFile(std::string full_path, std::string file_content);
    static std::string List(std::string curr_path);
    static std::string ChangeDirectory(std::string root_path, std::string curr_path, std::string dir);
    static std::string GetFile(std::string path);
    static bool MakeDir(std::string path, std::string dir_name);

private:
    static bool VerifyPath(std::string path);
    static bool IsAboveRoot(std::string root_path, std::string curr_path);
    static const char PATH_SEPARATOR = '/';
};