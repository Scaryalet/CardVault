#include "userhome.h"
#include "ui_userhome.h"
#include "addset.h"
#include "addcard.h"
#include <QComboBox>
#include "flowlayout.h"
#include <QPushButton>
#include <QListWidget>

UserHome::UserHome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserHome)
{
    ui->setupUi(this);
    flowLayout = new FlowLayout;
    flowLayout->setGeometry(QRect(0,0,750,300));




    connect(ui->setsCombo, &QComboBox::currentTextChanged, this, &UserHome::showUsersSets);
    connect(ui->setsList, &QListWidget::currentItemChanged, this, &UserHome::showSetCards);


}

UserHome::~UserHome()
{
    delete ui;
}

void UserHome::on_pushButton_clicked()
{
    AddSet* addSet = new class AddSet;
    addSet->show();

}


void UserHome::on_pushButton_2_clicked()
{
    AddCard* addCard = new class AddCard;
    setCentralWidget(addCard);
}

void UserHome::showUsersSets(){
    if(ui->setsCombo->currentText() == "Pokemon"){
        ui->setsList->clear();
        ui->setsList->addItem("Base Set");
        ui->setsList->addItem("2022 McDonalds");


    }
    if(ui->setsCombo->currentText() == "Yu-Gi-Oh!"){
        ui->setsList->clear();
        ui->setsList->addItem("Legend of Blue Eyes White Dragon");
        ui->setsList->addItem("Metal Raiders");


    }

}


void UserHome::showSetCards(){
    clearLayout(flowLayout);
    if(ui->setsList->currentItem()->text() == "2022 McDonalds"){
        for(int i = 1; i < 20; i++){
            QPushButton* card1 = new QPushButton;
            card1->setStyleSheet("border: 1px solid black;"
                                 "width: 150px;"
                                 "height: 250px;"
                                 "border-image: url(:/img/2022/001.png);");
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

