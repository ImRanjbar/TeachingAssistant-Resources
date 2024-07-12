#include "product.h"

Product::Product(const std::string& name)
{
    m_name = name;
}

void Product::setName(const std::string& name)
{
    m_name = name;
}

const std::string &Product::getName() const
{
    return m_name;
}
