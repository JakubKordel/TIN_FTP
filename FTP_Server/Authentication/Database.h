#pragma once

#include "readCsv.h"

#include <vector>
#include <string>
#include <fstream>
#include <streambuf>

class Database
{
private:
	std::vector<std::pair<std::string, std::vector<std::string>>> db;
	std::string dbPath;
public:
	Database(std::string dbFilename)
	{
		dbPath = dbFilename;
		db = readCsv(dbPath);
	}
	bool exists(std::string s1, std::string s2, bool strict=false);
	void addToDatabse(std::string s1, std::string s2);
};
