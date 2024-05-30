#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "qvariant.h"
#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <algorithm>

class SparseMatrix : public QObject {
    Q_OBJECT

public:
    // value1 - значения выше диагонали
    // value2 - значения ниже диагонали
    // x1 - для value1 - столбец, для value2 - строка
    // x2 - для value1 - строка, для value2 - столбец
    struct Position {
        QVariant value1;
        QVariant value2;
        int x1;
        int x2;
    };

    SparseMatrix(QObject *parent = nullptr);
    SparseMatrix(const QVector<Position>& positions, const QVector<QVariant>& diagonal, int size, const QVariant& predominant, bool symmetric, QObject *parent = nullptr);

    void clear();

    void generate(int size, float sparsity, int randStart, int randEnd, const QVariant& predominant = "0");
    void readMatrixFromFile(const QString& inputFilePath, bool symmetric = true);
    void makeFileOfMatrix(const QString& outputFilePath) const;
    void printMatrix(int head = -1, int tail = -1) const;

    void printMatrixToTextEdit(QTextEdit *textEdit, int head = -1, int tail = -1) const;
    void printData() const;
    void changeValues(int b);
private:
    QVector<Position> positions;
    QVector<QVariant> diagonal;
    int size;
    QVariant predominant;
    bool symmetric;
};

#endif // SPARSEMATRIX_H
