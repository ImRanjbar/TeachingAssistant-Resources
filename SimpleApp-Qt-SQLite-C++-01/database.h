#ifndef DATABASE_H
#define DATABASE_H

#include "user.h"

class Database
{
public:
    Database();

    static void initialize();
    static void addUser(const User& user);
    static bool userExistence(const User& user);

    // enum
    // username 0
    // password -1
    // login    1
    static int readUserData(User& user);
    static void addUserProduct(const Product& product, const User& user);

private:
    static void readUserProduct(User& user);
};

#endif // DATABASE_H
