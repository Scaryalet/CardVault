#include "forgotpasswordcont.h"
#include "loginregister.h"
#include "qsqlquery.h"
#include "ui_forgotpasswordcont.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include "forgotpassword.h"

ForgotPasswordCont::ForgotPasswordCont(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ForgotPasswordCont)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    connect(ui->nextButton, &QPushButton::clicked, this, &ForgotPasswordCont::checkNewPassword);
    connect(ui->returnButton, &QPushButton::clicked, this, &ForgotPasswordCont::returnButton);
}

ForgotPasswordCont::~ForgotPasswordCont()
{
    delete ui;
}

void ForgotPasswordCont:: checkNewPassword(){
    if(ui->newPassword->text() == ui->confirmPassword->text()) {
        db.open();
        QSqlQuery q1;
        q1.prepare("UPDATE users SET password = :newpassword WHERE username = :username");
        q1.bindValue(":username", username);
        q1.bindValue(":newpassword", ui->newPassword->text());
        q1.exec();
        db.close();
        QMessageBox::information(this,"Password Updated", "Password has been updated.");
        LoginRegister *login = new class LoginRegister;
        setCentralWidget(login);
    }
    else {
        QMessageBox::information(this,"Does Not Match", "Details do not match, make sure passwords are the same.");
    }
}

void ForgotPasswordCont:: returnButton(){
    LoginRegister *login = new class LoginRegister;
    setCentralWidget(login);
}
