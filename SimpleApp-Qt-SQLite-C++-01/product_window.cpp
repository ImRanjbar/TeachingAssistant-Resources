#include "product_window.h"
#include "ui_product_window.h"
#include "product.h"
#include "database.h"

product_window::product_window(const User& user,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::product_window)
    , m_user(user)
{
    ui->setupUi(this);

    populateList();
}

product_window::~product_window()
{
    delete ui;
}

void product_window::populateList()
{
    ui->listWidget->clear();

    std::vector<Product> products = m_user.getProduct();

    for (const Product& p : products){
        ui->listWidget->addItem(QString::fromStdString(p.getName()));
    }
}

void product_window::on_PB_add_clicked()
{

    std::string name = ui->LE_name->text().toStdString();

    Product p(name);
    m_user.addProduct(p);
    Database::addUserProduct(p, m_user);

    populateList();
}

