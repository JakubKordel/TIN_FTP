#include "Userbase.h"

bool Userbase::exists(std::string login, std::string password)
{
    size_t value_count = db.at(0).second.size();
    for (size_t i = 0; i < value_count; ++i)
    {
        if (db[0].second.at(i) == login)
            if (db[1].second.at(i) == password)
                return true;
    }
    return false;
}
