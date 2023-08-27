 #include "loginregister.h"
#include "./ui_loginregister.h"
#include "userhome.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "forgotpassword.h"

LoginRegister::LoginRegister(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginRegister)
{
    setWindowTitle("Card Vault");
    setWindowIcon(QIcon(":/img/SmallCardVaultLogo.png"));
    ui->setupUi(this);
    LoggedInUser = new CurrentUser;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    connect(ui->forgotButton, &QPushButton::clicked, this, &LoginRegister::forgotPassword);

}

LoginRegister::~LoginRegister()
{
    delete ui;
}

// Function that manages the login.
void LoginRegister::on_loginButton_clicked()
{
    db.open();
    //Variables for login function
    bool usernameCorrect = false;
    bool passwordCorrect = false;
    bool isAdmin = false;
    bool admin = false;
    QSqlQuery q1;

    // Checks user input against database
    q1.exec("SELECT * FROM users");
    while(q1.next()){

        if(ui->loginUsername->text() == q1.value(1).toString()){
            usernameCorrect = true;                                 //Sets usernameCorrect to true if input matches database.

            LoggedInUser->name = q1.value(1).toString();

            if(ui->loginPassword->text() == q1.value(2).toString()){
                passwordCorrect = true;                             // Sets passwordCorrect to true if password is correct.

                for(int i =0; i < q1.size(); i++){
                }
                if(q1.value(3) == "Yes"){                           // If database column 3 is "Yes" then user is an admin.
                    isAdmin = true;
                }
            }
        }
    }


    // Loops through user sets table and adds to LoggedInUser if set is owned
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
    // Loops through user cards table and adds to LoggedInUser if card is owned
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
    // Handles login
    if(usernameCorrect == true && passwordCorrect == true && isAdmin == false){ // if non-admin user is found
        QMessageBox::information(this, "Welcome","Welcome Back " + ui->loginUsername->text() + "!");

        UserHome* userHome = new class UserHome;
        setCentralWidget(userHome);
    }
    // Admin Signs In
    else if(usernameCorrect == true && passwordCorrect == true && isAdmin == true){ // if admin user is found
        QMessageBox::information(this, "Admin","Admin Signed In");
    }
    // Handles incorrect password
    else if(usernameCorrect == true && passwordCorrect == false){ // if username is correct but password is wrong
        QMessageBox::information(this, "incorrect password","Incorrect password");
    }
    // Handles incorrect username
    else if(usernameCorrect == false && passwordCorrect == false) { // if no matching user is found
        QMessageBox::information(this, "no user found","No user found");
    }
    db.close();
}


void LoginRegister::on_registerButton_clicked()
{

    db.open();
    // Handles potentional errors if a new user doesn't enter all information required to create an account.
    if(ui->registerEmail->text() == "" || ui->registerPassword->text() == "" || ui->registerUsername->text() == "" || ui->registerPasswordConfirm->text() == "" ){
        if(ui->registerEmail->text() == ""){
            QMessageBox::information(this, "enter an email", "Enter an email");
        }
        if(ui->registerUsername->text() == ""){
            QMessageBox::information(this, "enter a username", "Enter a username");
        }
        if(ui->registerPassword->text() == ""){
            QMessageBox::information(this, "enter a password", "Enter a password");
        }
        if(ui->registerPasswordConfirm->text() == ""){
            QMessageBox::information(this, "please confirm password", "Please confirm password");
        }

    }else {
        QSqlQuery q2;

        // bool variable to check if user account already exists
        bool userAlreadyFound = false;

        // search through login table in database
        q2.exec("SELECT * FROM users");

        // read each row of table and check if user exits already
        while(q2.next()){
            if(ui->registerEmail->text() == q2.value(0).toString()){
                userAlreadyFound = true;
                break;
            }else {
                userAlreadyFound = false;
            }
        }

        // If username already exists, displays pop up with User found.
        if(userAlreadyFound == true){
            QMessageBox::information(this, "user found", "A User with this email already exists");
        }
        // If username isn't found, then new account created.
        else if(userAlreadyFound == false){
            q2.prepare("INSERT INTO users (email, username, password, isAdmin)"
                       "VALUES (:email, :username, :password, :isAdmin)");
            q2.bindValue(":email", ui->registerEmail->text());
            q2.bindValue(":username", ui->registerUsername->text());
            q2.bindValue(":password", ui->registerPassword->text());
            q2.bindValue(":isAdmin", "No");


            // If passwords match when registering, account creation is succesful. If incorrect, pop up with passwords do not match
            if(ui->registerPassword->text() == ui->registerPasswordConfirm->text()){
                q2.exec();
                QMessageBox::information(this, "account created", "Sign up succesful. You may now log in");
                db.close();
                ui->tabWidget->setCurrentIndex(0); // sets tab back to login
            } else {
                QMessageBox::information(this, "passwords do not match", "Passwords do not match");
            }
        }

    }
    db.close();
}

void LoginRegister::forgotPassword(){
    ForgotPassword *forgotPassword = new class ForgotPassword;
    setCentralWidget(forgotPassword);
}
