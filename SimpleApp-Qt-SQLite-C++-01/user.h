#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include "product.h"

class User
{
public:
    User(const std::string &name, const std::string& username, const std::string &password);
    User(const std::string& username, const std::string &password);

    int getId() const;
    const std::string& getName() const;
    const std::string& getPassword() const;
    const std::string& getUsername() const;

    void setId(int id);
    void setName(const std::string& name);
    void setPassword(const std::string& password);
    void setUsername(const std::string& username);

    void addProduct(const Product& newProduct);
    const std::vector<Product>& getProduct() const;


private:
    int m_id;
    std::string m_name;
    std::string m_username;
    std::string m_password;
    std::vector<Product> m_products;
};

#endif // USER_H
