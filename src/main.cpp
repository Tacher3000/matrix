// main.cpp

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // window.show();
    // for (int var = 0; var < 1000000; ++var) {
    //     out << "X" << " ";
    // }

    MainWindow window;
    window.showMaximized();
    return app.exec();
}

