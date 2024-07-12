#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
public:
    Product(const std::string& name);

    void setName(const std::string& name);

    const std::string& getName() const;


private:
    std::string m_name;
};

#endif // PRODUCT_H
