#pragma once

#include "readCsv.h"

#include <vector>
#include <string>

class Userbase
{
private:
	std::vector<std::pair<std::string, std::vector<std::string>>> db;
public:
	Userbase(std::string dbFilename)
	{
		db = readCsv(dbFilename);
	}
	bool exists(std::string login, std::string password);
};
