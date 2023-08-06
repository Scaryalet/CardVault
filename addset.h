#ifndef ADDSET_H
#define ADDSET_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "loginregister.h"
namespace Ui {
class AddSet;
}

class AddSet : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddSet(QWidget *parent = nullptr);
    ~AddSet();
    QSqlDatabase db;
    int tempId, tempNum;
    QString tempName;
    Set s1;


public slots:
    void addSet();
private:
    Ui::AddSet *ui;

};

#endif // ADDSET_H
