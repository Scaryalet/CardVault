#include "loginregister.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginRegister w;
    w.show();
    return a.exec();
}
