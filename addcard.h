 #ifndef ADDCARD_H
#define ADDCARD_H

#include <QMainWindow>
#include <QWindow>
#include "loginregister.h"
#include <QComboBox>

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
    QSqlDatabase db;


public slots:

private slots:
    void showSetsSingle();
    void showSetsMultiple();
    void showNames();
    void showNamesMultiple();
    void showImage();
    void showImageMultiple();
    void addCardToListMultiple();
    void showCardFromListMultiple();
    void addCardSingle();
    void addCardMultiple();
    void handleReturn();
private:
    Ui::AddCard *ui;

    void showFranchises();
    void showSets(QComboBox *combo1, QComboBox *combo2, QComboBox *combo3);
};

#endif // ADDCARD_H
