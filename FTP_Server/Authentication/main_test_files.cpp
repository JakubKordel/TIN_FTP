#include <iostream>
#include <string>

#include "HashFunctions/crc.h"
#include "readCsv.h"
#include "Database.h"

int main()
{
    std::string database = "login_db.csv"; // sciezka do bazy danych plikow w systemie (baza danych trzyma pary nazwa pliku + crc32 pliku)
    std::string newFile = "zagadka.txt"; // sciezka do pliku, ktory chcemy dodac/sprawdzic

    Database db = Database(database);

    std::string crc = crc32::getFileCrc(newFile);

    std::cout << "crc: " << crc << std::endl;
    if (db.exists(newFile, crc)) {
        std::cout << "Already in database" << std::endl;
    }
    else {
        std::cout << "Adding to database" << std::endl;
        db.addToDatabse(newFile, crc);
    }

}