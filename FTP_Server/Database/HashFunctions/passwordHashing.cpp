#include "passwordHashing.h"
#include <sstream>

void sha1(BYTE* buf, BYTE* data, size_t len)
{
    SHA1_CTX ctx;
    sha1_init(&ctx);
    sha1_update(&ctx, data, len);
    sha1_final(&ctx, buf);
}

void hashString(BYTE* buf, std::string str)
{
    size_t length = str.length();
    BYTE* data = new BYTE[length + 1];
    for (size_t i = 0; i < length; ++i)
    {
        data[i] = str[i];
    }
    data[length] = '\0';
    sha1(buf, data, length + 1);
    delete[] data;
}

std::string getHashedPassword(std::string password)
{
    BYTE buf[SHA1_BLOCK_SIZE];
    hashString(buf, password);
    std::stringstream stream;
    for (auto c : buf)
    {
        stream << std::hex << (int)c;
    }
    return stream.str();
}
