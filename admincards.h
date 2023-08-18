#ifndef ADMINCARDS_H
#define ADMINCARDS_H

#include <QWidget>

namespace Ui {
class admincards;
}

class admincards : public QWidget
{
    Q_OBJECT

public:
    explicit admincards(QWidget *parent = nullptr);
    ~admincards();

private:
    Ui::admincards *ui;
};

#endif // ADMINCARDS_H
