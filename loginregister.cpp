#include "loginregister.h"
#include "./ui_loginregister.h"
#include "userhome.h"
#include "adminhome.h"
#include "./ui_adminhome.h"
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
    db.setDatabaseName("database.db");
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
    bool isAdmin = false;
    bool admin = false;
    QSqlQuery q1;

    // check user input against database
    q1.exec("SELECT * FROM users");
    while(q1.next()){
        if(ui->loginUsername->text() == q1.value(1).toString()){
            usernameCorrect = true;
            LoggedInUser->name = q1.value(1).toString();

            if(ui->loginPassword->text() == q1.value(2).toString()){
                passwordCorrect = true;

                for(int i =0; i < q1.size(); i++){

                }
                if(q1.value(3) == "Yes"){
                    isAdmin = true;
                }
            }
        }
    }

    // loop through user sets table and add to logged in user if set is owned
    q1.exec("SELECT * FROM UserSets");
    while(q1.next()){
        if(q1.value(0) == LoggedInUser->name){
            Set s1;
            s1.franchiseName = q1.value(1).toString();
            s1.setName = q1.value(2).toString();
            s1.setId = q1.value(3).toInt();
            LoggedInUser->AllSets.push_back(s1);
        }
    }
    // loop through user cards table and add to logged in user if card is owned
    q1.exec("SELECT * FROM UserCards");
    while(q1.next()){
        if(q1.value(0) == LoggedInUser->name){
            Card c1;
            c1.cardName = q1.value(1).toString();
            c1.cardID = q1.value(2).toInt();
            c1.rarity = q1.value(3).toString();
            LoggedInUser->AllCards.push_back(c1);
        }
    }

    // handle login
    if(usernameCorrect == true && passwordCorrect == true && isAdmin == false){ // if non-admin user is found
        QMessageBox::information(this, "Welcome","Welcome Back " + ui->loginUsername->text() + "!");
        UserHome* userHome = new class UserHome;

        //debug to check if working
        qDebug() << "UserName: " << LoggedInUser->name;
        qDebug() << "Sets Owned: ";

        for(int i = 0; i < LoggedInUser->AllSets.size(); i++){
            qDebug() << LoggedInUser->AllSets[i].setName;
        }
        qDebug() << "Cards Owned: ";
        for(int i = 0; i < LoggedInUser->AllCards.size(); i++){
            qDebug() << LoggedInUser->AllCards[i].cardName;
        }
        // end of debug

        setCentralWidget(userHome);
    } else if(usernameCorrect == true && passwordCorrect == true && isAdmin == true){ // if admin user is found
        QMessageBox::information(this, "Admin","Admin Signed In");
        adminhome* adminHome = new adminhome;
        this->setCentralWidget(adminHome);
    } else if(usernameCorrect == true && passwordCorrect == false){ // if username is correct but password is wrong
        QMessageBox::information(this, "incorrect password","incorrect password");
    } else if(usernameCorrect == false && passwordCorrect == false) { // if no matching user is found
        QMessageBox::information(this, "no user found","no user found");
    }

}


void LoginRegister::on_registerButton_clicked()
{
    // new query

    if(ui->registerEmail->text() == "" || ui->registerPassword->text() == "" || ui->registerUsername->text() == "" || ui->registerPasswordConfirm->text() == "" ){
        if(ui->registerEmail->text() == ""){
            QMessageBox::information(this, "enter an email", "enter an email");
        }
        if(ui->registerUsername->text() == ""){
            QMessageBox::information(this, "enter a username", "enter a username");
        }
        if(ui->registerPassword->text() == ""){
            QMessageBox::information(this, "enter a password", "enter a password");
        }
        if(ui->registerPasswordConfirm->text() == ""){
            QMessageBox::information(this, "please confirm password", "please confirm password");
        }

    }else {
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
            }else {
                userAlreadyFound = false;
            }
        }

        // if found - display dialog, if not found - create new user account from users input
        if(userAlreadyFound == true){
            QMessageBox::information(this, "user found", "user with this email already exists");
        }else if(userAlreadyFound == false){
            q1.prepare("INSERT INTO users (email, username, password, isAdmin)"
                       "VALUES (:email, :username, :password, :isAdmin)");
            q1.bindValue(":email", ui->registerEmail->text());
            q1.bindValue(":username", ui->registerUsername->text());
            q1.bindValue(":password", ui->registerPassword->text());
            q1.bindValue(":isAdmin", "No");

            if(ui->registerPassword->text() == ui->registerPasswordConfirm->text()){
                q1.exec();
                QMessageBox::information(this, "account created", "sign up succesful. you may now log in");
                ui->tabWidget->setCurrentIndex(0); // sets tab back to login
            } else {
                QMessageBox::information(this, "passwords do not match", "passwords do not match");
            }
        }

    }

}

