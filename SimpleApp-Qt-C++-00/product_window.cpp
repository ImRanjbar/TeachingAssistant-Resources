#include "product_window.h"
#include "ui_product_window.h"
#include "product.h"

product_window::product_window(const User& user,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::product_window)
    , m_user(user)
{
    ui->setupUi(this);
    Product p0("Sib");
    Product p1("Havij");

    m_user.addProduct(p0);
    m_user.addProduct(p1);

    std::vector<Product> products = m_user.getProduct();

    for (const Product& p : products){
        ui->listWidget->addItem(QString::fromStdString(p.getName()));
    }

}

product_window::~product_window()
{
    delete ui;
}
