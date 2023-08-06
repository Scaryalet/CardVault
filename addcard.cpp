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
    connect(ui->franchiseCombo, &QComboBox::currentTextChanged, this, &AddCard::showSets);
    connect(ui->setCombo, &QComboBox::currentTextChanged, this, &AddCard::showNumbers);
    connect(ui->numberCombo, &QComboBox::currentTextChanged, this, &AddCard::showImage);



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
