#include "admincards.h"
#include "ui_admincards.h"

admincards::admincards(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admincards)
{
    ui->setupUi(this);
}

admincards::~admincards()
{
    delete ui;
}
