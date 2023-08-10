#include "addcard.h"
#include "ui_addcard.h"
#include <QVector>
#include <QComboBox>

AddCard::AddCard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddCard)
{
    ui->setupUi(this);

    //signals
    connect(ui->sFranchiseCombo, &QComboBox::currentTextChanged, this, &AddCard::showSets);
    connect(ui->sSetCombo, &QComboBox::currentTextChanged, this, &AddCard::showNumbers);
    connect(ui->sNumberCombo, &QComboBox::currentTextChanged, this, &AddCard::showImage);
    connect(ui->mReturnButton, &QPushButton::clicked, this, &AddCard::handleReturn);
    connect(ui->sReturnButton, &QPushButton::clicked, this, &AddCard::handleReturn);




}

AddCard::~AddCard()
{
    delete ui;
}
void AddCard::showSets(){


}
void AddCard::showNumbers(){



}
void AddCard::showImage(){

}

void AddCard::handleReturn(){
    close();

}
