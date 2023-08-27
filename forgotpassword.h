#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H
#include <QSqlDatabase>

#include <QMainWindow>

namespace Ui {
class ForgotPassword;
}

class ForgotPassword : public QMainWindow
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = nullptr);

    ~ForgotPassword();
    QSqlDatabase db;

private slots:
    void returnButton();
private:
    Ui::ForgotPassword *ui;
    void checkUserDetails();
};
inline QString username;
#endif // FORGOTPASSWORD_H
