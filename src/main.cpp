#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // 🔥 ОТКЛЮЧАЕМ HiDPI

    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);\

    MainWindow w;
    w.show();

    return app.exec();
}




