// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QCheckBox>
#include "sparsematrix.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void generateMatrix();
    void loadMatrix();
    void saveMatrix();
    void displayMatrix();

private:
    SparseMatrix matrix;
    QTextEdit *matrixDisplay;
    QLineEdit *rowsInput;
    QLineEdit *colsInput;
    QLineEdit *nonZeroInput;
    QCheckBox *printMatrix;
    QPushButton *generateButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
};

#endif // MAINWINDOW_H
