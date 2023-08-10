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
    QVector <QString>* PokeSets;
    QVector <QString>* YugiSets;

public slots:
    void showSets();
    void showNumbers();
    void showImage();
private slots:
    void handleReturn();
private:
    Ui::AddCard *ui;
};

#endif // ADDCARD_H
