#include "userhome.h"
#include "qsqlquery.h"
#include "ui_userhome.h"
#include "addset.h"
#include "addcard.h"
#include <QComboBox>
#include "flowlayout.h"
#include <QPushButton>
#include <QListWidget>
#include "addset.h"

UserHome::UserHome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserHome)
{
    ui->setupUi(this);
    setsCombo = ui->setsCombo;
    setsList = ui->setsList;


    flowLayout = new FlowLayout;
    flowLayout->setGeometry(QRect(0,0,750,300));

    connect(ui->setsCombo, &QComboBox::currentTextChanged, this, &UserHome::showUsersSets);
    connect(ui->setsList, &QListWidget::currentItemChanged, this, &UserHome::showSetCards);
    connect(ui->userNewSet, &QPushButton::clicked, this, &UserHome::userAddSet);
    connect(ui->userNewCard, &QPushButton::clicked, this, &UserHome::userAddCard);
    connect(ui->exitButton, &QPushButton::clicked, this, &UserHome::handleExit);


    showFranchiseNames();

}

UserHome::~UserHome()
{
    delete ui;
}

void UserHome::showFranchiseNames()
{
    // A set to store unique franchise names, we use QSet because QSet will not store duplicate entries
    QSet<QString> uniqueFranchises;

    // Loop through the LoggedInUser->AllSets vector to find unique franchise names
    for (const Set& set : LoggedInUser->AllSets) {
        uniqueFranchises.insert(set.franchiseName);
    }

//    // Clear the combo box before adding new items.
//    setsCombo->clear();

    // Add unique franchise names to the combo box
    for (const QString& franchiseName : uniqueFranchises) {
        setsCombo->addItem(franchiseName);
    }
}

void UserHome::userAddSet()
{
    addSetWindow = new class AddSet;
    addSetWindow->show();

    // runs when signal is caught from AddSet
    connect(addSetWindow, &AddSet::setAdded, this, &UserHome::addSet);

}


void UserHome::userAddCard()
{
    AddCard* addCard = new class AddCard;
    addCard->show();
}

void UserHome::showUsersSets(){

    // disconnect slot to avoid crashes
    disconnect(ui->setsList, &QListWidget::currentItemChanged, this, &UserHome::showSetCards);

    QString selectedFranchise = setsCombo->currentText();

    // Clear the list widget before adding new items.
    setsList->clear();


    for (const Set& set : LoggedInUser->AllSets) {
        if (set.franchiseName == selectedFranchise) {
            setsList->addItem(set.setName);
            qDebug() << set.setName;
        }
    }










}


void UserHome::showSetCards(){
    clearLayout(flowLayout);

    if(ui->setsList->currentItem()->text() == "2022 McDonalds"){
        for(int i = 1; i < 20; i++){
            QPushButton* card1 = new QPushButton;
            card1->setStyleSheet("border: 1px solid black;"
                                 "width: 150px;"
                                 "height: 200px;"
                                 "border-image: url(:/img/2022/001.png);"
                                 "margin: 20px;");
            flowLayout->addWidget(card1);
        }
        ui->scrollAreaWidgetContents->setLayout(flowLayout);
    }
    if(ui->setsList->currentItem()->text() == "Base Set"){
        for(int i = 1; i < 20; i++){
            QPushButton* card1 = new QPushButton;
            card1->setStyleSheet("border: 1px solid black;"
                                 "width: 150px;"
                                 "height: 250px;"
                                 "border-image: url(:/img/2022/002.png);");
            flowLayout->addWidget(card1);
        }
        ui->scrollAreaWidgetContents->setLayout(flowLayout);
    }
}
void UserHome::clearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void UserHome::addSet(const QString& setName){ //

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
    showFranchiseNames();
}
void UserHome::handleExit(){
    LoginRegister *newLoginScreen = new class LoginRegister;
    setCentralWidget(newLoginScreen);
    delete LoggedInUser;
    db.close();


}
