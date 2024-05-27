#include "user.h"

User::User(const std::string& name, const std::string& username,const std::string& password)
{
    m_name = name;
    m_username = username;
    m_password = password;
}

const std::string &User::getName() const
{
    return m_name;
}

const std::string &User::getPassword() const
{
    return m_password;
}

const std::string& User::getUsername() const
{
    return m_username;
}

void User::setName(const std::string &name)
{
    m_name = name;
}

void User::setPassword(const std::string &password)
{
    m_password = password;
}

void User::setUsername(const std::string& username)
{
    m_username = username;
}

void User::addProduct(const Product &newProduct)
{
    m_products.push_back(newProduct);
}

const std::vector<Product> &User::getProduct() const
{
    return m_products;
}
