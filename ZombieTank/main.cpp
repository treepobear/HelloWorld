#include "mainview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainView mv;
    mv.show();

    return a.exec();
}
