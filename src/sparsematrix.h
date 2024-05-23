#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "qcontainerfwd.h"

#include <QVector>
#include <QDebug>
#include <QList>
#include <QRandomGenerator>
#include <QFile>
#include <QTextStream>

class SparseMatrix : public QObject {
    Q_OBJECT
public:
    SparseMatrix();
    // Метод для добавления ненулевого элемента
    void addElement(int row, int col, double value);

    // Метод для очистки матрицы
    void clear();

    // Метод для печати всей матрицы
    void print() const;

    // Метод для записи матрицы в файл
    void saveToFile(const QString &fileName) const;

    // Метод для чтения матрицы из файла
    void loadFromFile(const QString &fileName);

    void generateSparseMatrix(int numRows, int numCols, int numNonZeroPercent);
    void redistributeSparseMatrix(double b);

// private:
    QVector<int> rows;
    QVector<int> cols;
    QVector<int> values;
    int numRows;
    int numCols;
};


#endif // SPARSEMATRIX_H
