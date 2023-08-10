#ifndef USERHOME_H
#define USERHOME_H

#include <QMainWindow>
#include "addset.h"
#include "flowlayout.h"
#include "qcombobox.h"
#include "qlistwidget.h"

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
    AddSet* addSetWindow;
    Set s1;

public slots:
    void showFranchiseNames();
    void showUsersSets();
    void showSetCards();
    void clearLayout(QLayout *layout);
    void addSet(const QString& setName);

private slots:
    void userAddCard();
    void userAddSet();

    void handleExit();
private:
    Ui::UserHome *ui;
    QComboBox *setsCombo;
    QListWidget *setsList;
};

#endif // USERHOME_H
