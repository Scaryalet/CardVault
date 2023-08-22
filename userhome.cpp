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
    setWindowTitle("Home");
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
    connect(ui->setsList, &QListWidget::currentItemChanged, this, &UserHome::displayTheCards);
    connect(ui->setsList, &QListWidget::currentItemChanged, this, &UserHome::resetFilter);
    connect(ui->userNewSet, &QPushButton::clicked, this, &UserHome::userAddSet);
    connect(ui->userNewCard, &QPushButton::clicked, this, &UserHome::userAddCard);
    connect(ui->exitButton, &QPushButton::clicked, this, &UserHome::handleExit);
    connect(ui->filterCombo, &QComboBox::currentTextChanged, this, &UserHome::displayTheCards);

    //Functions that run when page loads
    populateSet2022McDonalds();
    showFranchiseNames();
}

UserHome::~UserHome()
{
    delete ui;
}

//This function can be removed when code is added for database file to copy when app is built
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

//Functions for going to addSet and addCard page
void UserHome::userAddSet()
{
    AddSet *addSetWindow = new class AddSet;
    setCentralWidget(addSetWindow);


}

void UserHome::userAddCard()
{
    AddCard *addCardWindow = new class AddCard;
    setCentralWidget(addCardWindow);

}

// Function to show unique Franchise names in QComboBox
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

// Function to add sets to the QListWidget
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


// Functions to display cards
void UserHome::displayTheCards() {
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

        if (shouldShowCard(q1, selectedOption)) {
            CustomButton* cardButton = new CustomButton("", cardURL, opacity, buttonStyleSheet, this);
            cardButton->setFixedSize(180, 240);
            flowLayout->addWidget(cardButton);
        }
    }
    ui->scrollAreaWidgetContents->setLayout(flowLayout);
}
//Function to reset filter options
void UserHome::resetFilter() {
    ui->filterCombo->setCurrentIndex(-1);
}
//Function to check if card is in Users Card
bool UserHome::cardExistsInAllCards(const QString& cardName) {
    for (const auto& card : LoggedInUser->AllCards) {
        if (card.cardName == cardName) {
            return true;
        }
    }
    return false;
}
//Function for the filter options
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


//Function to clear the QLayout.
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

// Function to exit and go back to login page
void UserHome::handleExit(){

    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase("database.db");

    LoginRegister *newLoginScreen = new class LoginRegister;
    setCentralWidget(newLoginScreen);
    LoggedInUser = new CurrentUser;
}
