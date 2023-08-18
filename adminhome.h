#ifndef ADMINHOME_H
#define ADMINHOME_H

#include <QWidget>

namespace Ui {
class adminhome;
}

class adminhome : public QWidget
{
    Q_OBJECT

public:
    explicit adminhome(QWidget *parent = nullptr);
    ~adminhome();

private slots:
    void onEditFranchiseClicked();
    void onCreateFranchiseClicked();
    void onCreateCardClicked();

private:
    Ui::adminhome *ui;  // Class name should be capitalized
};

#endif // ADMINHOME_H
