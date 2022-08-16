#include "mainwindow.h"
//#include "ui_aircraf_macket.h"



#include <QList>

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    w.show();

    return a.exec();
}
