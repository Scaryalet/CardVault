#include "adminhome.h"
#include "ui_adminhome.h"
#include <QMessageBox>

adminhome::adminhome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminhome)
{
    ui->setupUi(this);

    // signals and slots here


}

adminhome::~adminhome()
{
    delete ui;
}

void adminhome::onEditFranchiseClicked()
{
    QMessageBox::information(this, "Edit Franchise", "You clicked the Edit Franchise button.");
    // logic to handle editing franchises here
}

void adminhome::onCreateFranchiseClicked()
{
    QMessageBox::information(this, "Create Franchise", "You clicked the Create Franchise button.");
    // logic to handle creating franchises here
}

void adminhome::onCreateCardClicked()
{
    QMessageBox::information(this, "Create Card", "You clicked the Create Card button.");
    // logic to handle creating cards here
}

