// main.cpp

#include "mainwindow.h"
#include <QApplication>
#include "sparsematrix.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // QWidget window;
    // window.setWindowTitle("GridLayout с разделителями");

    // // Создаем QGridLayout
    // QGridLayout *layout = new QGridLayout(&window);

    // // Создаем виджеты
    // QLabel *label1 = new QLabel("Ячейка 1");
    // QLabel *label2 = new QLabel("Ячейка 2");
    // QLabel *label3 = new QLabel("Ячейка 3");

    // // Создаем разделитель с использованием QFrame
    // QFrame *hline = new QFrame;
    // hline->setFrameShape(QFrame::HLine);
    // hline->setFrameShadow(QFrame::Sunken);

    // // Добавляем виджеты и разделитель в сетку
    // layout->addWidget(label1, 0, 0);
    // layout->addWidget(label2, 0, 1);
    // layout->addWidget(hline, 1, 0, 1, 2); // добавляем разделитель между строками 1 и 2
    // layout->addWidget(label3, 2, 0, 1, 2);

    // window.show();
    MainWindow window;
    window.showMaximized();
    // SparseMatrix matrix;
    // matrix.generate(10, 0.5, 1, 100, QVariant(0));

    // matrix.printMatrix(2, 2);
    return app.exec();
}

