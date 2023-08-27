#ifndef FORGOTPASSWORDCONT_H
#define FORGOTPASSWORDCONT_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class ForgotPasswordCont;
}

class ForgotPasswordCont : public QMainWindow
{
    Q_OBJECT

public:
    explicit ForgotPasswordCont(QWidget *parent = nullptr);

    ~ForgotPasswordCont();
    QSqlDatabase db;
public slots:

private slots:
    void returnButton();
    void checkNewPassword();
private:
    Ui::ForgotPasswordCont *ui;

};

#endif // FORGOTPASSWORDCONT_H
