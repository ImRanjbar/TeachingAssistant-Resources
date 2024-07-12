#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
   /*
    * bool doesUserExist() -> user -> database -> true \ false
    * void readUserData() -> .
    *
    */
private slots:
    void on_pb_sign_up_clicked();

    void on_pb_login_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
