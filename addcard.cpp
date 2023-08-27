#include "addcard.h"
#include "ui_addcard.h"
#include "userhome.h"
#include <QVector>
#include <QComboBox>
#include <QSqlQuery>
#include <QMessageBox>

AddCard::AddCard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddCard)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    db.open();

    showFranchises();

    //Signals to show set names
    connect(ui->franchiseCombo, &QComboBox::currentTextChanged, this, &AddCard::showSetsSingle);
    connect(ui->franchiseComboMultiple, &QComboBox::currentTextChanged, this, &AddCard::showSetsMultiple);
    //Signals to show numbers
    connect(ui->setCombo, &QComboBox::currentTextChanged, this, &AddCard::showNames);
    connect(ui->setComboMultiple, &QComboBox::currentTextChanged, this, &AddCard::showNamesMultiple);
    //Signals to show Images
    connect(ui->numberCombo, &QComboBox::currentTextChanged, this, &AddCard::showImage);
    connect(ui->numberComboMultiple, &QComboBox::currentTextChanged, this, &AddCard::showImageMultiple);
    //Return to UserHome signals
    connect(ui->returnButtonMultiple, &QPushButton::clicked, this, &AddCard::handleReturn);
    connect(ui->returnButtonSingle, &QPushButton::clicked, this, &AddCard::handleReturn);
    //Multiple card additional signals
    connect(ui->addIndividuaButton, &QPushButton::clicked, this, &AddCard::addCardToListMultiple);
    connect(ui->displayCardsMultiple, &QListWidget::currentItemChanged, this, &AddCard::showCardFromListMultiple);
    //Add card signals
    connect(ui->addCardButton, &QPushButton::clicked, this, &AddCard::addCardSingle);
    connect(ui->addCardButtonMultiple, &QPushButton::clicked, this, &AddCard::addCardMultiple);

}

AddCard::~AddCard()
{
    delete ui;
}

//Function to show the franchise names
void AddCard::showFranchises(){

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
    ui->franchiseComboMultiple->clear();

    // Add unique franchise names to the combo box
    for (const QString& franchiseName : uniqueFranchises) {
        ui->franchiseCombo->addItem(franchiseName);
        ui->franchiseComboMultiple->addItem(franchiseName);
    }
}

//Functions to call showSets
void AddCard::showSetsSingle(){
    showSets(ui->setCombo, ui->numberCombo, ui->franchiseCombo);
}

void AddCard::showSetsMultiple(){
    showSets(ui->setComboMultiple, ui->numberComboMultiple,ui->franchiseComboMultiple);
}

//Function to reduce code
void AddCard::showSets(QComboBox *combo1, QComboBox *combo2, QComboBox *combo3){
    QString selectedFranchise = combo3->currentText();
    combo1->clear();
    combo2->clear();

    for(int i = 0; i < LoggedInUser->AllSets.size(); i++){
        if(LoggedInUser->AllSets[i].franchiseName == selectedFranchise){
            combo1->addItem(LoggedInUser->AllSets[i].setName);
        }
    }
}

//Functions to show the number in combo boxes
void AddCard::showNames(){
    QString selectedSet = ui->setCombo->currentText();
    ui->numberCombo->clear();
    QSqlQuery q1;
    q1.exec("SELECT * FROM Cards");
    while(q1.next()){
        if(q1.value(1) == selectedSet){
            ui->numberCombo->addItem(q1.value(0).toString());
        }
    }
}

void AddCard::showNamesMultiple(){
    QString selectedSet = ui->setComboMultiple->currentText();
    ui->numberComboMultiple->clear();
    QSqlQuery q1;
    q1.exec("SELECT * FROM Cards");
    while(q1.next()){
        if(q1.value(1) == selectedSet){
            ui->numberComboMultiple->addItem(q1.value(0).toString());
        }
    }
}

//Function to show images
void AddCard::showImage(){
    QString selectedSet = ui->setCombo->currentText();
    QString selectedCard = ui->numberCombo->currentText();

    QSqlQuery q2;
    q2.exec("SELECT * FROM Cards");
    while(q2.next()){
        if(q2.value(0).toString() == selectedCard && selectedSet == q2.value(1).toString()){
            userSelectedCard.cardName = q2.value(0).toString();
            userSelectedCard.cardNumber = q2.value(3).toInt();
            userSelectedCard.setName = q2.value(1).toString();
            userSelectedCard.rarity = q2.value(4) .toString();
            userSelectedCard.imgURL = q2.value(5).toString();
        }
    }
    ui->cardImage->setStyleSheet("border-image: url(" + userSelectedCard.imgURL + ");");
}

void AddCard::showImageMultiple(){
    QString selectedSet = ui->setComboMultiple->currentText();
    QString selectedCard = ui->numberComboMultiple->currentText();

    QSqlQuery q2;
    q2.exec("SELECT * FROM Cards");
    while(q2.next()){
        if(q2.value(0).toString() == selectedCard && selectedSet == q2.value(1).toString()){
            userSelectedCard.cardName = q2.value(0).toString();
            userSelectedCard.cardNumber = q2.value(3).toInt();
            userSelectedCard.setName = q2.value(1).toString();
            userSelectedCard.rarity = q2.value(4) .toString();
            userSelectedCard.imgURL = q2.value(5).toString();
        }
    }
    ui->cardImageMultiple->setStyleSheet("border-image: url(" + userSelectedCard.imgURL + ");");
}

//Function to return to userHome
void AddCard::handleReturn(){
    UserHome *userHome = new class UserHome;
    setCentralWidget(userHome);
}

//Functions to add cards
void AddCard::addCardSingle(){
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

    QMessageBox::information(this, "Card Added!", userSelectedCard.cardName + " added to your portfolio!");

    UserHome *userHome = new class UserHome;
    setCentralWidget(userHome);
}

void AddCard::addCardMultiple(){

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
    UserHome *userHome = new class UserHome;
    setCentralWidget(userHome);
}

//Additional functions for mulitple cards
void AddCard::addCardToListMultiple() {

    CardsToAdd.push_back(userSelectedCard);
    ui->displayCardsMultiple->addItem(userSelectedCard.cardName);

}

void AddCard::showCardFromListMultiple() {
    QString selectedCardFromList = ui->displayCardsMultiple->currentItem()->text();
    for(int i = 0; i < CardsToAdd.size(); i++){
        if(selectedCardFromList == CardsToAdd[i].cardName){
            ui->cardImageMultiple->setStyleSheet("border-image: url(" + CardsToAdd[i].imgURL + ");");
        }
    }
}
