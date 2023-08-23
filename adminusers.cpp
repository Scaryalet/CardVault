#include "adminusers.h"
#include "ui_adminusers.h"

adminusers::adminusers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminusers)
{
    ui->setupUi(this);
}

adminusers::~adminusers()
{
    delete ui;
}

void adminusers::on_adminEditSet_clicked()
{

}

