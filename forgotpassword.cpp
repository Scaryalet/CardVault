#include "forgotpassword.h"
#include "loginregister.h"
#include "ui_forgotpassword.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "forgotpasswordcont.h"
#include <QMessageBox>

ForgotPassword::ForgotPassword(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    connect(ui->nextButton, &QPushButton::clicked, this, &ForgotPassword::checkUserDetails);
    connect(ui->returnButton, &QPushButton::clicked, this, &ForgotPassword::returnButton);
}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword:: checkUserDetails(){

    db.open();
    bool emailCorrect = false;
    bool usernameCorrect = false;

    //Checks user information against the database
    QSqlQuery q1;

    q1.exec("SELECT * FROM users");
    while(q1.next()){

        if(ui->emailEdit->text() == q1.value(0).toString()){
            emailCorrect = true;                                 //Sets bool value to true if email address is true

            if(ui->usernameEdit->text() == q1.value(1).toString()){
                usernameCorrect = true;                          // Sets bool value to true if username is true
            }
        }

    }

    if(emailCorrect == true && usernameCorrect == true){ // If details are correct
        username = ui->usernameEdit->text();
        ForgotPasswordCont *forgotPasswordCont = new ForgotPasswordCont;
        setCentralWidget(forgotPasswordCont);
    }

    //If email address is incorrect but username is correct:
    else if(emailCorrect == false && usernameCorrect == true){
        QMessageBox::information(this, "Email Incorrect", "Email Address is Incorrect");

    }
    //If email address is correct but username is incorrect:
    else if (emailCorrect == true && usernameCorrect == false) {
        QMessageBox::information(this, "Username Incorrect", "Username is Incorrect");
    }

    //If details are incorrect:
    else if (emailCorrect == false && usernameCorrect == false) {
        QMessageBox::information(this, "no user found","No user found");
    }
};

void ForgotPassword:: returnButton(){
    LoginRegister *login = new class LoginRegister;
    setCentralWidget(login);
}
