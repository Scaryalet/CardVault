#include "addset.h"
#include "qsqlquery.h"
#include "ui_addset.h"
#include <QPushButton>
#include <QPushButton>

AddSet::AddSet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddSet)
{
    ui->setupUi(this);
    setWindowTitle("Add New Set");



    QSqlQuery q1;
    // select all sets from DB
    q1.exec("SELECT * FROM Sets");
    while(q1.next()){
        ui->listWidget->addItem(q1.value(1).toString()); // add set names to list widget
    }

    connect(ui->addSetButton, &QPushButton::clicked, this, &AddSet::addSet);

}

AddSet::~AddSet()
{
    delete ui;


}
void AddSet::addSet(){
    QString setName = ui->listWidget->currentItem()->text(); // temp string to hold selected set name
    QSqlQuery q1;
    // select all from sets table
    q1.exec("SELECT * FROM SETS");
    while(q1.next()){
        // if set name matches chosen set from list
        if(setName == q1.value(1).toString()){
            // set 'Set' object (declared in header file) to set info from DB
            s1.franchiseName=q1.value(0).toString();
            s1.setName = q1.value(1).toString();
            s1.setId = q1.value(2).toInt();
            s1.numberOfCards = q1.value(3).toInt();
            // push back to users allsets vector
            LoggedInUser->AllSets.push_back(s1);
            // insert into USerSets DB
            q1.prepare("INSERT INTO UserSets (Username,  SetName, SetID, Franchise)"
                       "VALUES (:username, :setName, :setID, :franchise)");
            q1.bindValue(":username", LoggedInUser->name);
            q1.bindValue(":franchise", s1.franchiseName);

            q1.bindValue(":setName", s1.setName);

            q1.bindValue(":setID", s1.setId);

            q1.exec();


        }
    }
    // close DB
    // close window
    this->close();

}
