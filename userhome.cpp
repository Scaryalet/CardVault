#include "userhome.h"
#include "qsqlquery.h"
#include "ui_userhome.h"
#include "addset.h"
#include "addcard.h"
#include <QComboBox>
#include "flowlayout.h"
#include <QPushButton>
#include <QListWidget>
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
    showFranchiseNames();
}

UserHome::~UserHome()
{
    delete ui;
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
    //If layout is equal to NULL, then it exits the function
    if (layout == NULL)
        return;
    QLayoutItem *item;
    //Deletes items from the layout
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
