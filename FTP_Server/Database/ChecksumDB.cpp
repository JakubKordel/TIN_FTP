#include "ChecksumDB.h"

bool ChecksumDB::fileExists(std::string filename, std::string content){
    if(!opened) return false;
    std::string crc = crc32::getStringCrc(content);
    return exists(filename, crc, true);
}

void ChecksumDB::addToDB(std::string filename, std::string content){
    if(!opened) return;
    std::string crc = crc32::getStringCrc(content);
    addToDatabase(filename, crc);
}

bool ChecksumDB::addToDBNewRecord(std::string filename, std::string content){
    if(!opened) return false;
    if(fileExists(filename, content)) return false;
    addToDB(filename, content);
    return true;
}