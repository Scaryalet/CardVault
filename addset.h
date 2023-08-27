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

private:
    Ui::AddSet *ui;
    QComboBox *franchiseCombo;

private slots:
    void franchiseBox();
    void showSetList();
    void addSet();
    void on_returnButton_clicked();

};

#endif // ADDSET_H
