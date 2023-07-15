#ifndef LOGINREGISTER_H
#define LOGINREGISTER_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginRegister; }
QT_END_NAMESPACE

class LoginRegister : public QMainWindow
{
    Q_OBJECT

public:
    LoginRegister(QWidget *parent = nullptr);
    ~LoginRegister();
    QSqlDatabase db;

private slots:
    void on_loginButton_clicked();

    void on_registerButton_clicked();

private:
    Ui::LoginRegister *ui;
};
#endif // LOGINREGISTER_H
