#include "addcard.h"
#include "ui_addcard.h"

AddCard::AddCard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddCard)
{
    ui->setupUi(this);
}

AddCard::~AddCard()
{
    delete ui;
}
