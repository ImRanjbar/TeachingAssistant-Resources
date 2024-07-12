#include "database.h"

#include <QSqlDatabase>
#include <QSqlQuery>

Database::Database() {}

void Database::initialize()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");

    if (!db.open()){
        qDebug() << "Failed to open database";
        return;
    }


    QSqlQuery query;
    query.prepare("SELECT * FROM sqlite_master WHERE type = 'table' AND name = 'Users'");

    if (!query.exec()){
        qDebug() << "Failed to exec addUser";
        return;
    }

    if (query.next()) {
        return;
    }
    else {
        query.prepare(
            "CREATE TABLE 'Users' ("
            "'id' INTEGER PRIMARY KEY AUTOINCREMENT,"
            "'username' TEXT UNIQUE,"
            "'name' TEXT,"
            "'password' TEXT"
            ");"
            );

        if (!query.exec()) {
            qDebug() << "Failed to create Users table";
            return;
        }

        query.prepare(
            "CREATE TABLE 'Products' ("
            "'productID' INTEGER PRIMARY KEY AUTOINCREMENT,"
            "'name' TEXT,"
            "'ownerID' INTEGER NOT NULL,"
            "FOREIGN KEY('ownerID') REFERENCES 'Users'('id')"
            ");"
            );

        if (!query.exec()) {
            qDebug() << "Failed to create Products table";
            return;
        }
    }

}

void Database::addUser(const User &user)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");

    if (!db.open()){
        qDebug() << "Failed to open database";
        return;
    }

    // Query -> request
    QSqlQuery query;
    query.prepare("INSERT INTO Users (username, name, password) "
                  "VALUES (:username, :name, :password)");

    query.bindValue(":username", QString::fromStdString(user.getUsername()));
    query.bindValue(":name", QString::fromStdString(user.getName()));
    query.bindValue(":password", QString::fromStdString(user.getPassword()));

    if (!query.exec()){
        qDebug() << "Failed to exec addUser";
        return;
    }


    qDebug() << "User Added to database";
    db.close();
}

bool Database::userExistence(const User& user)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");


    if (!db.open()){
        qDebug() << "Failed to open database";
        return true;
    }

    QSqlQuery query;
    query.prepare("SELECT EXISTS (SELECT 1 FROM Users WHERE username = :username)");
    query.bindValue(":username", QString::fromStdString(user.getUsername()));

    if (!query.exec()){
        qDebug() << "Failed to exec addUser";
        return true;
    }

    query.next();

    int exist = query.value(0).toInt();

    if (exist){
        db.close();
        return true;
    }
    else {
        return false;
    }

    db.close();
    return true;
}

// username 0
// password -1
// login    1
int Database::readUserData(User &user)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");


    if (!db.open()){
        qDebug() << "Failed to open database";
        return true;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE username = :username");

    query.bindValue(":username", QString::fromStdString(user.getUsername()));

    if (!query.exec()){
        qDebug() << "Failed to exec readUserData";
        return true;
    }

    if (query.next()){
        std::string pass = query.value(3).toString().toStdString();
        if (pass != user.getPassword()){
            return -1;
        }
        else {
            // Read Data -> Login
            user.setName(query.value(2).toString().toStdString());
            user.setId(query.value(0).toInt());

            // Read Products
            readUserProduct(user);

            return 1;
        }
    }
    else {
        return 0;
    }



}

void Database::addUserProduct(const Product &product, const User &user)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");


    if (!db.open()){
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Products (name, ownerID) "
                  "VALUES (:name, :ownerID)");

    query.bindValue(":name", QString::fromStdString(product.getName()));
    query.bindValue(":ownerID", user.getId());

    if (!query.exec()){
        qDebug() << "Failed to exec addUserProduct";
        return;
    }


    qDebug() << "Product have added";
    db.close();
}

void Database::readUserProduct(User &user)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM Products WHERE ownerID = :ownerID");

    query.bindValue(":ownerID", user.getId());

    if (!query.exec()){
        qDebug() << "Failed to exec readUserProduct";
        return;
    }


    while (query.next()){
        std::string name = query.value(1).toString().toStdString();
        Product p(name);
        user.addProduct(p);
    }

    qDebug() << "Products have read";

}
