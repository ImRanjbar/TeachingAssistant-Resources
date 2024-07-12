#ifndef PRODUCT_WINDOW_H
#define PRODUCT_WINDOW_H

#include <QDialog>
#include "user.h"

namespace Ui {
class product_window;
}

class product_window : public QDialog
{
    Q_OBJECT

public:
    explicit product_window(const User& user,QWidget *parent = nullptr);
    ~product_window();

private:
    void populateList();

private slots:
    void on_PB_add_clicked();

private:
    Ui::product_window *ui;
    User m_user;
};

#endif // PRODUCT_WINDOW_H
