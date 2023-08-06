#include "loginregister.h"
#include "userhome.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginRegister w;
//    UserHome w;
    w.show();
    return a.exec();
}
