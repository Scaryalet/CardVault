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
    setWindowTitle("Add New Set");


    QSqlQuery q1;
    // select all sets from DB
    q1.exec("SELECT * FROM Sets");

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
            ui->listWidget->addItem(setName);
        }
    }
    connect(ui->addSetButton, &QPushButton::clicked, this, &AddSet::addSet);
}

AddSet::~AddSet()
{
    delete ui;
}

void AddSet::addSet(){
    QString setName = ui->listWidget->currentItem()->text(); // temp string to hold selected set name
    // emit a signal with setName that will be caught on UserHome
    emit setAdded(setName);

    UserHome *userHomeWindow = new class UserHome;

    setCentralWidget(userHomeWindow);


}

void AddSet::on_returnButton_clicked()
{
    UserHome *userHomeWindow = new class UserHome;
    setCentralWidget(userHomeWindow);
}

