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

private:
    Ui::AddCard *ui;
};

#endif // ADDCARD_H
