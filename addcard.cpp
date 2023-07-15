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
    ui->numberCombo->setCurrentIndex(-1);
    if(ui->franchiseCombo->currentText() == "Pokemon"){
       ui->setCombo->clear();
       ui->setCombo->addItem("Base Set");
       ui->setCombo->addItem("Jungle");
       ui->setCombo->addItem("2022 McDonalds");
    }
    if(ui->franchiseCombo->currentText() == "Yu-Gi-Oh!"){
       ui->setCombo->clear();
       ui->setCombo->addItem("Legend of Blue Eyes White Dragon");
       ui->setCombo->addItem("Metal Raiders");
    }

}
void AddCard::showNumbers(){
    if(ui->setCombo->currentText() == "Legend of Blue Eyes White Dragon"){
        ui->numberCombo->clear();
        ui->numberCombo->addItem("LOB-EN000 - Tri-Horned Dragon");
        ui->numberCombo->addItem("LOB-EN002 - Blue Eyes White Dragon");
        ui->numberCombo->addItem("LOB-EN003 - Hitotsu-Me Giant");
        ui->numberCombo->addItem("LOB-EN004 - Flame Swordsman");
    }
    if(ui->setCombo->currentText() == "2022 McDonalds"){
        ui->numberCombo->clear();
        ui->numberCombo->addItem("01/15 - Ledyba");
        ui->numberCombo->addItem("02/15 - Rowlet");
        ui->numberCombo->addItem("03/15 - Gossifluer");
        ui->numberCombo->addItem("04/15 - Growlithe");
    }


}
void AddCard::showImage(){
    if(ui->numberCombo->currentText() == "04/15 - Growlithe"){
        ui->cardImage->setStyleSheet("border-image: url(:/img/2022/004.png)");
    }

}
