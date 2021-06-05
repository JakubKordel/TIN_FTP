#include "readCsv.h"

#include <fstream>
#include <utility>
#include <stdexcept>
#include <sstream>

std::vector<std::pair<std::string, std::vector<std::string>>> readCsv(std::string filename) {
    std::vector<std::pair<std::string, std::vector<std::string>>> result;

    std::ifstream myFile(filename);

    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line, colname;
    std::string val;

    if (myFile.good())
    {
        std::getline(myFile, line);
        std::stringstream ss(line);

        while (std::getline(ss, colname, ','))
            result.push_back({ colname, std::vector<std::string> {} });
    }

    while (std::getline(myFile, line))
    {
        std::stringstream ss(line);

        int colIdx = 0;

        while (std::getline(ss, val, ','))
        {
            result.at(colIdx).second.push_back(val);
            ++colIdx;
        }
    }

    myFile.close();

    return result;
}
