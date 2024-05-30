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
#include <QElapsedTimer>

class SparseMatrix : public QObject {
    Q_OBJECT

public:
    // Структура для хранения значений матрицы
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

    // Конструкторы класса SparseMatrix
    SparseMatrix(QObject *parent = nullptr);
    SparseMatrix(const QVector<Position>& positions, const QVector<QVariant>& diagonal, int size, const QVariant& predominant, bool symmetric, QObject *parent = nullptr);

    ~SparseMatrix();

    // Очистка данных матрицы
    void clear();

    // Генерация разреженной матрицы
    void generate(int size, float sparsity, int randStart, int randEnd, const QVariant& predominant = "0");

    // Чтение матрицы из файла
    void readMatrixFromFile(const QString& inputFilePath, bool symmetric = true);

    // Сохранение матрицы в файл
    void makeFileOfMatrix(const QString& outputFilePath) const;

    // Печать матрицы
    void printMatrix(int head = -1, int tail = -1) const;

    // Печать матрицы в QTextEdit
    void printMatrixToTextEdit(QTextEdit *textEdit, int head = -1, int tail = -1) const;

    // Печать данных о матрице (позиции и диагональ)
    void printData() const;

    // Изменение значений матрицы
    void changeValues(int b);
private:
    QVector<Position> positions;
    QVector<QVariant> diagonal;
    int size;
    QVariant predominant;
    bool symmetric;
};

#endif // SPARSEMATRIX_H
