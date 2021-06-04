#pragma once

#include "readCsv.h"

#include <vector>
#include <string>
#include <fstream>
#include <streambuf>
#include <exception>
#include <iostream>

class Database
{
private:
	std::vector<std::pair<std::string, std::vector<std::string>>> db;
	std::string dbPath;
public:
	Database(){}
	Database(std::string dbFilename)
	{
		dbPath = dbFilename;
	}

	bool openDB(std::string path){
		dbPath = path;
		try{
			db = readCsv(dbPath);
		}catch(std::exception &e){
			perror("Blad otwarcia bazy");
			return false;
		}
		return true;
	}

	bool exists(std::string s1, std::string s2, bool strict=false);
	void addToDatabase(std::string s1, std::string s2);
};
