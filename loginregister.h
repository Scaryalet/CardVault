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

    QSqlDatabase db;

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

    void forgotPassword();
private:
    Ui::LoginRegister *ui;
};

//Structure to hold information about cards
struct Card {
    QString cardName;
    int cardID;
    int cardNumber;
    QString rarity;
    QString setName;
    QString imgURL;
};

//Structure to hold information about sets
struct Set {
    QString franchiseName;
    int setId;
    QString setName;
    int numberOfCards;
};

//Structure to hold information about the current user
struct CurrentUser {
    QString name;
    QVector <Card> AllCards;
    QVector <Set> AllSets;
};

inline CurrentUser *LoggedInUser;




#endif // LOGINREGISTER_H

