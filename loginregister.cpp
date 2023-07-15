#include "loginregister.h"
#include "./ui_loginregister.h"
#include "userhome.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

LoginRegister::LoginRegister(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginRegister)
{
    ui->setupUi(this);

    // database connection
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
    db.open();
}

LoginRegister::~LoginRegister()
{
    delete ui;
}


void LoginRegister::on_loginButton_clicked()
{
    bool usernameCorrect = false;
    bool passwordCorrect = false;
    QSqlQuery q1;
    q1.exec("SELECT * FROM users");

    while(q1.next()){
        if(ui->loginUsername->text() == q1.value(1).toString()){
            usernameCorrect = true;
        }
        if(ui->loginPassword->text() == q1.value(2).toString()){
            passwordCorrect = true;
        }

    }
    if(usernameCorrect == true && passwordCorrect == true){
        QMessageBox::information(this, "Welcome","Welcome Back " + ui->loginUsername->text() + "!");
        UserHome* userHome = new class UserHome;
        userHome->show();
        close();
    } else if(usernameCorrect == true && passwordCorrect == false){
        QMessageBox::information(this, "incorrect password","incorrect password");
    }else if(usernameCorrect == false && passwordCorrect == true){
        QMessageBox::information(this, "incorrect username","incorrect username");
    } else if(usernameCorrect == false && passwordCorrect == false) {
        QMessageBox::information(this, "no user found","no user found");

    }

}


void LoginRegister::on_registerButton_clicked()
{
    // new query
    QSqlQuery q1;

    // bool variable to check if user account already exists
    bool userAlreadyFound = false;

    // search through login table in database
    q1.exec("SELECT * FROM users");

    // read each row of table and check if user exits already
    while(q1.next()){
        if(ui->registerEmail->text() == q1.value(0).toString()){
            userAlreadyFound = true;
            break;
        }else if(userAlreadyFound = false);
    }

    // if found - display dialog, if not found - create new user account from users input
    if(userAlreadyFound == true){
        QMessageBox::information(this, "user found", "user with this email already exists");
    }else if(userAlreadyFound == false){
        q1.prepare("INSERT INTO users (email, username, password)"
                   "VALUES (:email, :username, :password)");

        q1.bindValue(":email", ui->registerEmail->text());
        q1.bindValue(":username", ui->registerUsername->text());
        q1.bindValue(":password", ui->registerPassword->text());

        if(ui->registerPassword->text() == ui->registerPasswordConfirm->text()){
            q1.exec();
            QMessageBox::information(this, "account created", "sign up succesful. you may now log in");
            ui->tabWidget->setCurrentIndex(0); // sets tab back to login
        } else {
            QMessageBox::information(this, "passwords do not match", "passwords do not match");
        }
    }
    // NEED TO ADD A CHECK FOR EMPTY FIELDS
}

