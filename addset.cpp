#include "addset.h"
#include "qsqlquery.h"
#include "ui_addset.h"
#include "userhome.h"
#include <QPushButton>
#include <QPushButton>

AddSet::AddSet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddSet)
{
    ui->setupUi(this);
    franchiseCombo=ui->franchiseCombo;

    setWindowTitle("Add New Set");

    QSqlQuery q1;
    // select all sets from DB
    q1.exec("SELECT * FROM Sets");

//    while (q1.next()) {
//        QString setName = q1.value(1).toString();

//        // check if the set is not already owned by the user
//        bool setOwned = false;
//        for (const Set& ownedSet : LoggedInUser->AllSets) {
//            if (ownedSet.setName == setName) {
//                setOwned = true;
//                break;
//            }
//        }
//        // if the set is not owned, add it to the listWidget
//        if (!setOwned) {
//            ui->listWidget->addItem(setName);
//        }
//    }

    franchiseBox();
    connect(ui->addSetButton, &QPushButton::clicked, this, &AddSet::addSet);
    connect(ui->franchiseCombo, &QComboBox::currentTextChanged,this, &AddSet::showSetList);
}

AddSet::~AddSet()
{
    delete ui;
}

void AddSet::addSet(){
    QString setName = ui->setsList->currentItem()->text(); // temp string to hold selected set name

    db.open();
    QSqlQuery q1;

    // select all from sets table
    q1.exec("SELECT * FROM SETS");
    while(q1.next()){
        // if set name matches chosen set from list
        if(setName == q1.value(1).toString()){
            Set s1;
            // set 'Set' object (declared in header file) to set info from DB
            s1.franchiseName=q1.value(0).toString();
            s1.setName = q1.value(1).toString();
            s1.setId = q1.value(2).toInt();
            s1.numberOfCards = q1.value(3).toInt();

            // push back to users allsets vector
            LoggedInUser->AllSets.push_back(s1);

            // insert into UserSets DB
            q1.prepare("INSERT INTO UserSets (Username,  SetName, SetID, Franchise)"
                       "VALUES (:username, :setName, :setID, :franchise)");
            q1.bindValue(":username", LoggedInUser->name);
            q1.bindValue(":franchise", s1.franchiseName);
            q1.bindValue(":setName", s1.setName);
            q1.bindValue(":setID", s1.setId);

            q1.exec();
        }
    }

    // Returns User to Home
    UserHome *userHomeWindow = new class UserHome;
    setCentralWidget(userHomeWindow);


}

void AddSet::on_returnButton_clicked()
{
    UserHome *userHomeWindow = new class UserHome;
    setCentralWidget(userHomeWindow);
}

void AddSet::franchiseBox(){

    QVector <QString> AllSets;
    QSqlQuery q1;
    q1.exec("SELECT * FROM Sets");
    while(q1.next()){
        AllSets.push_back(q1.value(0).toString());

    }
    // A set to store unique franchise names, we use QSet because QSet will not store duplicate entries
    QSet<QString> uniqueFranchises;

    // Loop through the LoggedInUser->AllSets vector to find unique franchise names
    for (const QString& franchise : AllSets) {
        uniqueFranchises.insert(franchise);
    }

    // Clear the combo box before adding new items.
    ui->franchiseCombo->clear();

    // Add unique franchise names to the combo box
    for (const QString& franchiseName : uniqueFranchises) {
        ui->franchiseCombo->addItem(franchiseName);
    }
}

void AddSet::showSetList(){
    db.open();
    QString selectedFranchise = ui->franchiseCombo->currentText();
    QSqlQuery q1;
    q1.prepare("SELECT * FROM Sets WHERE Franchise = :franchise");
    q1.bindValue(":franchise", selectedFranchise);
    q1.exec();
    while (q1.next()) {
        QString setName = q1.value(1).toString();

        // check if the set is not already owned by the user
        bool setOwned = false;
        for (const Set& ownedSet : LoggedInUser->AllSets) {
            if (ownedSet.setName == setName) {
                setOwned = true;
                break;
            }
        }
        // if the set is not owned, add it to the listWidget
        if (!setOwned) {
            ui->setsList->addItem(setName);
        }
    }
}
