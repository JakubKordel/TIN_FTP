#include "Database.h"

bool Database::exists(std::string s1, std::string s2, bool strict=false)
{
    size_t value_count = db.at(0).second.size();
    for (size_t i = 0; i < value_count; ++i)
    {
        if (strict) {
            if (db[0].second.at(i) == s1 || db[1].second.at(i) == s2)
                return true;
        }
        else if (db[0].second.at(i) == s1 && db[1].second.at(i) == s2)
            return true;
    }
    return false;
}
void Database::addToDatabse(std::string s1, std::string s2)
{
    std::ofstream out;

    // std::ios::app is the open mode "append" meaning
    // new data will be written to the end of the file.
    out.open(this->dbPath, std::ios::app);
    out << s1 << "," << s2 << '\n';
    this->db = readCsv(dbPath);
}
