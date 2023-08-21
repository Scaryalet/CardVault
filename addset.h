#ifndef ADDSET_H
#define ADDSET_H

#include "qcombobox.h"
#include <QMainWindow>
#include <QSqlDatabase>

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

public slots:
    void addSet();
private:
    Ui::AddSet *ui;
    QComboBox *franchiseCombo;


private slots:
    void on_returnButton_clicked();
    void franchiseBox();
    void showSetList();
};

#endif // ADDSET_H
