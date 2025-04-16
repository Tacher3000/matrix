#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>
#include <QCheckBox>
#include "sparsematrix.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void print();
private slots:
    void generateMatrix();
    void stosunkowoB();
    void loadMatrix();
    void saveMatrix();

private:
    SparseMatrix _matrix;
    QTextEdit *_matrixDisplay;
    QLineEdit *_sizeInput;
    QLineEdit *_predominantInput;
    QLineEdit *_dischargeInput;
    QLineEdit *_bInput;
    QCheckBox *_printWindow;
    QCheckBox *_printKonsol;
    QCheckBox *_reducePrint;
    QPushButton *_generateButton;
    QPushButton *_algorithmButton;
    QPushButton *_loadButton;
    QPushButton *_saveButton;
};

#endif // MAINWINDOW_H
