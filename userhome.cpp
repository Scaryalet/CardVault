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
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>

UserHome::UserHome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserHome)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    db.open();

    ui->setupUi(this);

    setsCombo = ui->setsCombo;
    setsList = ui->setsList;
    filterCombo = ui->filterCombo;

    //Setting the flow layout
    flowLayout = new FlowLayout(-1, 45, 45);
    flowLayout->setGeometry(QRect(0,0,750,300));
    flowLayout->setSpacing(80);

    //Connect signals with slots
    connect(ui->setsCombo, &QComboBox::currentTextChanged, this, &UserHome::showUsersSets);
    connect(ui->setsList, &QListWidget::currentItemChanged, this, &UserHome::populateTheCards);
    connect(ui->userNewSet, &QPushButton::clicked, this, &UserHome::userAddSet);
    connect(ui->userNewCard, &QPushButton::clicked, this, &UserHome::userAddCard);
    connect(ui->exitButton, &QPushButton::clicked, this, &UserHome::handleExit);
    //
    connect(ui->filterCombo, &QComboBox::currentTextChanged, this, &UserHome::populateTheCards);
    //

    //Functions that run when page loads
    populateSet2022McDonalds();
    showFranchiseNames();
//    createFilterOptions(filterCombo);
}

UserHome::~UserHome()
{
    delete ui;
}

void UserHome::populateSet2022McDonalds()
{
    db.open();
    QString setName = "2022 McDonalds";
    QString franchiseName = "Pokemon";
    int setID = 1;
    int numberOfCards = 15;
    QSqlQuery q1;

    q1.exec("SELECT * FROM Sets");
    bool maccasFound = false;
    while(q1.next()){
        if(q1.value(0) == "Pokemon" && q1.value(1) == "2022 McDonalds"){
            maccasFound = true;
            break;
        }
    }
    if(!maccasFound){
        // Insert the set into the Sets table

        q1.prepare("INSERT INTO Sets (Franchise, SetName, SetID, NumberOfCards) VALUES (:franchise, :setName, :setID, :NumberOfCards)");
        q1.bindValue(":franchise", franchiseName);
        q1.bindValue(":setName", setName);
        q1.bindValue(":setID", setID);
        q1.bindValue(":NumberOfCards", numberOfCards);
        q1.exec();


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

}

void UserHome::showFranchiseNames()
{
    // A set to store unique franchise names, we use QSet because QSet will not store duplicate entries
    QSet<QString> uniqueFranchises;
    QVector <QString> vectorFranchises;
    // Loop through the LoggedInUser->AllSets vector to find unique franchise names
    for (const Set& set : LoggedInUser->AllSets) {
        uniqueFranchises.insert(set.franchiseName);
    }
    // Add unique franchise names to the combo box
    for (const QString& franchiseName : uniqueFranchises) {
        ui->setsCombo->addItem(franchiseName);
    }


}


void UserHome::userAddSet()
{
    addSetWindow = new class AddSet;
    setCentralWidget(addSetWindow);
    // runs when signal is caught from AddSet
    connect(addSetWindow, &AddSet::setAdded, this, &UserHome::addSet);

}

void UserHome::userAddCard()
{
    addCardWindow = new class AddCard;
    addCardWindow->show();
    connect(addCardWindow, &AddCard::singleCardToAdd, this, &UserHome::addCard);
    connect(addCardWindow, &AddCard::multipleCardsToAdd, this, &UserHome::addMultipleCards);
}

void UserHome::showUsersSets(){

    QString selectedFranchise = setsCombo->currentText();

    // Clear the list widget before adding new items.
    setsList->clear();

    for (const Set& set : LoggedInUser->AllSets) {
        if (set.franchiseName == selectedFranchise) {
            setsList->addItem(set.setName);
        }
    }

}

void UserHome::populateTheCards() {
    clearLayout(flowLayout);
    QString selectedSet;
    QString buttonStyleSheet = "width: 180px;"
                               "height: 240px;"
                               "border: none;"
                               "outline: none;";

    if (ui->setsList->currentItem() != nullptr) {
        selectedSet = ui->setsList->currentItem()->text();
    }

    QString selectedOption = filterCombo->currentText();
    QSqlQuery q1;
    q1.prepare("SELECT * FROM Cards WHERE SetName = :selectedSet");
    q1.bindValue(":selectedSet", selectedSet);
    q1.exec();

    while (q1.next()) {
        bool cardExists = cardExistsInAllCards(q1.value(0).toString());

        QString cardURL = q1.value(5).toString();
        double opacity = cardExists ? 1.0 : 0.3;
        if (selectedOption == "Not Collected") {
            opacity = 1.0; // Set opacity to 1.0 for all cards under "Not Collected" filter
        }
        if (shouldShowCard(q1, selectedOption)) {
            CustomButton* cardButton = new CustomButton("", cardURL, opacity, buttonStyleSheet, this);
            cardButton->setFixedSize(180, 240);
            flowLayout->addWidget(cardButton);
        }
    }
    ui->scrollAreaWidgetContents->setLayout(flowLayout);

}

bool UserHome::cardExistsInAllCards(const QString& cardName) {
    for (const auto& card : LoggedInUser->AllCards) {
        if (card.cardName == cardName) {
            return true;
        }
    }
    return false;
}

bool UserHome::shouldShowCard(const QSqlQuery& query, const QString& selectedOption) {
    QString rarity = query.value(4).toString();

    if (selectedOption == "" || selectedOption == "All") {
        return true;
    } else if (selectedOption == "Collected") {
        return cardExistsInAllCards(query.value(0).toString());
    } else if (selectedOption == "Not Collected") {
        return !cardExistsInAllCards(query.value(0).toString());
    } else if (selectedOption == "Common") {
        return rarity == "Common";
    } else if (selectedOption == "Uncommon") {
        return rarity == "Uncommon";
    } else if (selectedOption == "Rare") {
        return rarity == "Rare";
    } else if (selectedOption == "Holo+") {
        return rarity != "Common" && rarity != "Uncommon" && rarity != "Rare";
    }
    return false;
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
    db.open();
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


}

void UserHome::addCard(const Card& userSelectedCard) {
    db.open();
    QSqlQuery q3;
    q3.prepare("INSERT INTO UserCards (Username, CardName, SetName, ImageURL, CardRarity)"
               "VALUES (:username, :cardname, :setname, :imageurl, :cardrarity)");
    q3.bindValue(":username", LoggedInUser->name);
    q3.bindValue(":cardname", userSelectedCard.cardName);
    q3.bindValue(":setname", userSelectedCard.setName);
    q3.bindValue(":imageurl", userSelectedCard.imgURL);
    q3.bindValue(":cardrarity", "common");
    q3.exec();
    LoggedInUser->AllCards.push_back(userSelectedCard);


    populateTheCards();
}

void UserHome::addMultipleCards(const QVector<Card> &CardsToAdd) {
    db.open();
    QSqlQuery q3;
    for(int i = 0; i<CardsToAdd.size(); i++){
        q3.prepare("INSERT INTO UserCards (Username, CardName, SetName, ImageURL, CardRarity)"
                   "VALUES (:username, :cardname, :setname, :imageurl, :cardrarity)");
        q3.bindValue(":username", LoggedInUser->name);
        q3.bindValue(":cardname", CardsToAdd[i].cardName);
        q3.bindValue(":setname", CardsToAdd[i].setName);
        q3.bindValue(":imageurl", CardsToAdd[i].imgURL);
        q3.bindValue(":cardrarity", "common");
        q3.exec();
        LoggedInUser->AllCards.push_back(CardsToAdd[i]);


    }
    populateTheCards();

}

void UserHome::handleExit(){

    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase("database.db");

    LoginRegister *newLoginScreen = new class LoginRegister;
    setCentralWidget(newLoginScreen);
    LoggedInUser = new CurrentUser;
}
