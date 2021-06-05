#pragma once

#include "Database.h"
#include "HashFunctions/crc.h"
#include "readCsv.h"

class ChecksumDB: public Database {
    bool opened = false;
public:
    ChecksumDB(): Database(){
        if(openDB(DB_PATH)){
            opened = true;
        }
    }

    bool fileExists(std::string filename, std::string content);
    void addToDB(std::string filename, std::string content);
    bool addToDBNewRecord(std::string filename, std::string content);

private:
    std::string DB_PATH = "ftp_root/file_db.csv";
};