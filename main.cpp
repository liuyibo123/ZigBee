#include "mainwindow.h"
#include <QApplication>
#include "qpaintboard.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWidget widget;
//    widget.show();
    MainWindow w;
    w.show();
    return a.exec();
}
