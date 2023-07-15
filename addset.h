#ifndef ADDSET_H
#define ADDSET_H

#include <QMainWindow>

namespace Ui {
class AddSet;
}

class AddSet : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddSet(QWidget *parent = nullptr);
    ~AddSet();

private:
    Ui::AddSet *ui;

};

#endif // ADDSET_H
