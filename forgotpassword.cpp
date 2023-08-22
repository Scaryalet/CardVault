#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

ForgotPassword::ForgotPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);

    setWindowTitle("Forgot Password");
    setGeometry(0,0,1280,720);

    QVBoxLayout * mainLayout = new QVBoxLayout;

    QLabel *newPasswordLabel = new QLabel(tr("Enter Password:"));
    QLineEdit *passwordEdit = new QLineEdit;
    QPushButton *button = new QPushButton(tr("Submit"));

    mainLayout->addWidget(newPasswordLabel);
    mainLayout->addWidget(passwordEdit);
    mainLayout->addWidget(button);

    setLayout(mainLayout);







}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}
