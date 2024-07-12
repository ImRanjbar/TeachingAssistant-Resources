#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "product_window.h"
#include <QMessageBox>
#include "database.h"

std::vector<User> users;

// Member initializer list
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->error->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_sign_up_clicked()
{
    std::string name = ui->le_name->text().toStdString();
    std::string username = ui->le_username->text().toStdString();
    std::string password = ui->le_pass->text().toStdString();

    User user(name, username, password);

    if (Database::userExistence(user)){
        ui->error->setText("User already exists");
        ui->error->show();
        return;
    }

    Database::addUser(user);

    QMessageBox ms;
    ms.setText("You have successfully registered!");
    ms.setWindowTitle("Sign-up");

    ms.exec();
}


void MainWindow::on_pb_login_clicked()
{
    std::string username = ui->le_username_login->text().toStdString();
    std::string password = ui->le_pass_login->text().toStdString();

    User user(username, password);
    int loginResult = Database::readUserData(user);

    if (loginResult == 1){
        // login
        product_window* productWindow = new product_window(user);
        productWindow->show();
        this->close();
    }
    else if (loginResult == 0){
        ui->error->setText("Wrong Username");
        ui->error->show();
    }
    else if (loginResult == -1){
        ui->error->setText("Wrong Password");
        ui->error->show();
    }


    // for (std::vector<User>::iterator it = users.begin(); it != users.end(); it++){
    //     if ((it->getUsername() == username) && (it->getPassword() == password)){
    //         // it -> user
    //         product_window* productWindow = new product_window(*it);
    //         productWindow->show();
    //         this->close();
    //     }
    //     else {
    //         continue;
    //     }
    // }
}

