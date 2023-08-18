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
    QVector <Card> CardsToAdd;

public slots:
    void showSets();
    void showNumbers();
    void showImage();
private slots:
    void handleReturn();
    void showFranchises();
    void addCardSingle();
    void addCardMultiple();
    void showSetsMultiple();
    void showNumbersMultiple();
    void showImageMultiple();
    void addCardToListMultiple();
    void showCardFromListMultiple();
private:
    Ui::AddCard *ui;

signals:
    void singleCardToAdd(Card);
    void multipleCardsToAdd(QVector<Card>);
};

#endif // ADDCARD_H
