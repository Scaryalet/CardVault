#ifndef USERHOME_H
#define USERHOME_H

#include <QMainWindow>
#include "flowlayout.h"

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
    FlowLayout *emptyFlowLayout;

public slots:
    void showUsersSets();
    void showSetCards();
    void emptyLayout();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::UserHome *ui;
};

#endif // USERHOME_H
