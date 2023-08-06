#ifndef USERHOME_H
#define USERHOME_H

#include <QMainWindow>
#include "flowlayout.h"
#include "qcombobox.h"

namespace Ui {
class UserHome;
}

class UserHome : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserHome(QWidget *parent = nullptr);
    ~UserHome();
    FlowLayout *flowLayout;

public slots:
    void showFranchiseNames();
    void showUsersSets();
    void showSetCards();
    void clearLayout(QLayout *layout);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::UserHome *ui;
    QComboBox *setsCombo;
};

#endif // USERHOME_H
