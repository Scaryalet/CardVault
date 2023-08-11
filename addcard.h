#ifndef ADDCARD_H
#define ADDCARD_H

#include <QMainWindow>
#include <QWindow>
#include "loginregister.h"

namespace Ui {
class AddCard;
}

class AddCard : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddCard(QWidget *parent = nullptr);
    ~AddCard();
    QString imageURL;
    Card userSelectedCard;

public slots:
    void showSets();
    void showNumbers();
    void showImage();
private slots:
    void handleReturn();
    void showFranchises();
    void addCardSingle();
private:
    Ui::AddCard *ui;
signals:
    void singleCardToAdd(Card);
};

#endif // ADDCARD_H
