#include "userhome.h"
#include "ui_userhome.h"
#include "addset.h"
#include "addcard.h"

UserHome::UserHome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserHome)
{
    ui->setupUi(this);
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
    addCard->show();
}

