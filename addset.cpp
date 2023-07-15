#include "addset.h"
#include "ui_addset.h"
#include "flowlayout.h"
#include <QPushButton>
#include <QPushButton>

AddSet::AddSet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddSet)
{
    ui->setupUi(this);
    FlowLayout *flowLayout = new FlowLayout;
    flowLayout->setGeometry(QRect(0,0,750,300));
    QPushButton* card1 = new QPushButton;
    card1->setStyleSheet("border: 1px solid black;"
                         "width: 200px;"
                         "height: 300px;"
                         "border-image: url(:/img/2022/001.png)"
                         );
    flowLayout->addWidget(card1);
    QPushButton* card2 = new QPushButton;
    card2->setStyleSheet("border: 1px solid black;"
                         "width: 200px;"
                         "height: 300px;"
                         "border-image: url(:/img/2022/002.png)"
                         );
    flowLayout->addWidget(card2);
    QPushButton* card3 = new QPushButton;
    card3->setStyleSheet("border: 1px solid black;"
                         "width: 200px;"
                         "height: 300px;"
                         "border-image: url(:/img/2022/003.png)"
                         );
    flowLayout->addWidget(card3);
    QPushButton* card4 = new QPushButton;
    card4->setStyleSheet("border: 1px solid black;"
                         "width: 200px;"
                         "height: 300px;"
                         "border-image: url(:/img/2022/004.png)"
                         );
    flowLayout->addWidget(card4);
    QPushButton* card5 = new QPushButton;
    card5->setStyleSheet("border: 1px solid black;"
                         "width: 200px;"
                         "height: 300px;"
                         "border-image: url(:/img/2022/005.png)"
                         );
    flowLayout->addWidget(card5);
    ui->scrollAreaWidgetContents->setLayout(flowLayout);



    setWindowTitle("AddSet");
}

AddSet::~AddSet()
{
    delete ui;


}
