#ifndef LOGINREGISTER_H
#define LOGINREGISTER_H
#include <QVector>
#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginRegister; }
QT_END_NAMESPACE

class LoginRegister : public QMainWindow
{
    Q_OBJECT

public:
    LoginRegister(QWidget *parent = nullptr);
    ~LoginRegister();






private slots:
    void on_loginButton_clicked();

    void on_registerButton_clicked();


private:
    Ui::LoginRegister *ui;
};
struct Card {
    QString cardName;
    int cardID;
    int cardNumber;
    QString rarity;
    bool collected;
};

struct Set {
    QString franchiseName;
    int setId;
    QString setName;
    int numberOfCards;

};
struct CurrentUser {
    QString name;
    QVector <Card> AllCards;
    QVector <Set> AllSets;


};
inline CurrentUser *LoggedInUser = new CurrentUser;
inline QSqlDatabase db;

#endif // LOGINREGISTER_H

