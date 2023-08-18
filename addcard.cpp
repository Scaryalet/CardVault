#include "addcard.h"
#include "ui_addcard.h"
#include <QVector>
#include <QComboBox>
#include <QSqlQuery>
#include <QMessageBox>

AddCard::AddCard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddCard)
{
    ui->setupUi(this);


    showFranchises();

    //signals
    connect(ui->franchiseCombo, &QComboBox::currentTextChanged, this, &AddCard::showSets);
    connect(ui->franchiseComboMultiple, &QComboBox::currentTextChanged, this, &AddCard::showSetsMultiple);
    connect(ui->setCombo, &QComboBox::currentTextChanged, this, &AddCard::showNumbers);
    connect(ui->setComboMultiple, &QComboBox::currentTextChanged, this, &AddCard::showNumbersMultiple);
    connect(ui->numberCombo, &QComboBox::currentTextChanged, this, &AddCard::showImage);
    connect(ui->numberComboMultiple, &QComboBox::currentTextChanged, this, &AddCard::showImageMultiple);
    connect(ui->returnButtonMultiple, &QPushButton::clicked, this, &AddCard::handleReturn);
    connect(ui->returnButtonSingle, &QPushButton::clicked, this, &AddCard::handleReturn);
    connect(ui->addCardButton, &QPushButton::clicked, this, &AddCard::addCardSingle);
    connect(ui->addIndividuaButton, &QPushButton::clicked, this, &AddCard::addCardToListMultiple);
    connect(ui->displayCardsMultiple, &QListWidget::currentItemChanged, this, &AddCard::showCardFromListMultiple);
    connect(ui->addCardButtonMultiple, &QPushButton::clicked, this, &AddCard::addCardMultiple);


}

AddCard::~AddCard()
{
    delete ui;
}
void AddCard::showSets(){
    QString selectedFranchise = ui->franchiseCombo->currentText();
    ui->setCombo->clear();
    ui->numberCombo->clear();
    QSqlQuery q1;
    q1.exec("SELECT * FROM Sets");
    while(q1.next()){
        if(q1.value(0) == selectedFranchise){
            ui->setCombo->addItem(q1.value(1).toString());

        }
    }
}
void AddCard::showSetsMultiple(){
    QString selectedFranchise = ui->franchiseComboMultiple->currentText();
    ui->setComboMultiple->clear();
    ui->numberComboMultiple->clear();
    QSqlQuery q1;
    q1.exec("SELECT * FROM Sets");
    while(q1.next()){
        if(q1.value(0) == selectedFranchise){
            ui->setComboMultiple->addItem(q1.value(1).toString());

        }
    }
}

void AddCard::showNumbers(){
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
void AddCard::showNumbersMultiple(){
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

void AddCard::showImage(){
    QString selectedSet = ui->setCombo->currentText();
    QString selectedCard = ui->numberCombo->currentText();
    qDebug() << "Selected Card: " + selectedCard;
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
    qDebug() << "Selected Card: " + selectedCard;
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

void AddCard::handleReturn(){
    close();
}

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

void AddCard::addCardSingle(){

    QMessageBox::information(this, "Card Added!", userSelectedCard.cardName + " added to your portfolio!");
    emit singleCardToAdd(userSelectedCard);

    this->close();

    // WE NEED TO CHECK IF THE USER OWNS THE SET ALREADY, AND IF NOT WE NEED TO ADD TO USERS SETS.

}
void AddCard::addCardMultiple(){

    emit multipleCardsToAdd(CardsToAdd);
    this->close();




}

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
