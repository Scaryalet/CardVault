#ifndef ADMINUSERS_H
#define ADMINUSERS_H

#include <QWidget>

namespace Ui {
class adminusers;
}

class adminusers : public QWidget
{
    Q_OBJECT

public:
    explicit adminusers(QWidget *parent = nullptr);
    ~adminusers();

private:
    Ui::adminusers *ui;
};

#endif // ADMINUSERS_H
