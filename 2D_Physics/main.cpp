#include <QtGui/QApplication>
#include "mainwindow.h"
#include "World.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
