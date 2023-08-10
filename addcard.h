#ifndef ADDCARD_H
#define ADDCARD_H

#include <QMainWindow>
#include <QWindow>

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
    struct SelectedCard {
        QString name;
        QString set;
        int number;
        QString rarity;
        QString imgURL;
    };
    SelectedCard *userSelectedCard;

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
};

#endif // ADDCARD_H
