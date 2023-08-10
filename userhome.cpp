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
    connect(ui->setsList, &QListWidget::currentItemChanged, this, &UserHome::populateTheCards);
    connect(ui->userNewSet, &QPushButton::clicked, this, &UserHome::userAddSet);
    connect(ui->userNewCard, &QPushButton::clicked, this, &UserHome::userAddCard);
    connect(ui->exitButton, &QPushButton::clicked, this, &UserHome::handleExit);

    populateSet2022McDonalds();
    showFranchiseNames();

}

UserHome::~UserHome()
{
    delete ui;
}


void UserHome::populateSet2022McDonalds()
{

    QString setName = "2022 McDonalds";
    QString franchiseName = "Pokemon";
    int setID = 1;
    int numberOfCards = 15;

    // Insert the set into the Sets table
    QSqlQuery q1;
    q1.prepare("INSERT INTO Sets (Franchise, SetName, SetID, NumberOfCards) VALUES (:franchise, :setName, :setID, :NumberOfCards)");
    q1.bindValue(":franchise", franchiseName);
    q1.bindValue(":setName", setName);
    q1.bindValue(":setID", setID);
    q1.bindValue(":NumberOfCards", numberOfCards);
    q1.exec();

    // Add the set to the user's AllSets vector
    Set s;
    s.franchiseName = franchiseName;
    s.setName = setName;
    s.setId = 1;
    s.numberOfCards = 15; // Total number of cards in the set
    LoggedInUser->AllSets.push_back(s);

    // Insert the card details into the Cards table
    QSqlQuery q2;

    for (int cardNumber = 1; cardNumber <= 15; ++cardNumber) {
        QString cardRarity = "Common"; // Adjust the rarity as needed
        //Input image url. cardNumber is the value of the card, 3 is the width of the string (if less than 10, two zeros go in front, less that 100, one zero)
        //10 is the base of the number system and QLatin1Char('0') makes the character used for padding a 0.
        QString imageURL = QString(":/img/2022/%1.png").arg(cardNumber, 3, 10, QLatin1Char('0'));

        q2.prepare("INSERT INTO Cards (CardName, SetName, CardID, CardNumber, CardRarity, ImageURL) "
                   "VALUES (:cardName, :setName, :cardID, :cardNumber, :cardRarity, :imageURL)");

        q2.bindValue(":cardName", cardNumber);
        q2.bindValue(":cardID", cardNumber);
        q2.bindValue(":cardNumber", cardNumber);
        q2.bindValue(":cardRarity", cardRarity);
        q2.bindValue(":imageURL", imageURL);

        q2.bindValue(":setName", setName);

        q2.exec();


    }



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
//    disconnect(ui->setsList, &QListWidget::currentItemChanged, this, &UserHome::populateTheCards);

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




void UserHome::populateTheCards(){
    clearLayout(flowLayout);
    QString selectedSet = ui->setsList->currentItem()->text();
    //Searches database for cards from selected set.
    QSqlQuery q1;
    q1.prepare("SELECT * FROM Cards WHERE SetName = :selectedSet");
    q1.bindValue(":selectedSet", selectedSet);
    q1.exec();

    //Creates card button with image of cards.
    while (q1.next()) {
        QPushButton* cardButton = new QPushButton;
        cardButton->setStyleSheet("border: 1px solid black;"
                                  "width: 150px;"
                                  "height: 200px;"
                                  "border-image: url(" + q1.value(5).toString() + ");"
                                                             "margin: 20px;");
        flowLayout->addWidget(cardButton);
    }

    // Set the layout for the scroll area's contents
    ui->scrollAreaWidgetContents->setLayout(flowLayout);
};

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
