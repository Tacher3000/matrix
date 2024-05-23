#include "sparsematrix.h"

SparseMatrix::SparseMatrix() {}

void SparseMatrix::addElement(int row, int col, double value)
{
    if (value != 0) {
        rows.append(row);
        cols.append(col);
        values.append(value);
    }
}

void SparseMatrix::clear()
{
    rows.clear();
    cols.clear();
    values.clear();
}

void SparseMatrix::print() const {
    // Создаем QDebug с флагом QDebug::nospace, чтобы не добавлять пробелы между элементами
    QDebug debug = qDebug().nospace();

    // Пройдемся по каждой строке
    for (int i = 0; i < numRows; ++i) {
        // Пройдемся по каждому столбцу
        for (int j = 0; j < numCols; ++j) {
            // Ищем индекс элемента в векторах rows и cols
            int index = -1;
            for (int k = 0; k < rows.size(); ++k) {
                if (rows[k] == i && cols[k] == j) {
                    index = k;
                    break;
                }
            }
            // Если элемент найден, выводим его значение
            if (index != -1) {
                debug << values[index] << "\t";
            } else {
                // В противном случае выводим 0
                debug << 0 << "\t";
            }
        }
        debug << "\n"; // Переход на новую строку после каждой строки матрицы
    }
}



void SparseMatrix::saveToFile(const QString &fileName) const
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << fileName;
        return;
    }

    QTextStream out(&file);
    out << numRows << " " << numCols << "\n";
    for (int i = 0; i < values.size(); ++i) {
        out << rows[i] << " " << cols[i] << " " << values[i] << "\n";
    }
    file.close();
}

void SparseMatrix::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << fileName;
        return;
    }

    clear();
    QTextStream in(&file);
    in >> numRows >> numCols;
    while (!in.atEnd()) {
        int row, col;
        int value;
        in >> row >> col >> value;
        addElement(row, col, value);
    }
    file.close();
}

void SparseMatrix::generateSparseMatrix(int numRows, int numCols, int numNonZeroPercent)
{
    this->numRows = numRows;
    this->numCols = numCols;

    int totalElements = numRows * numCols;
    int numNonZeroElements = totalElements * numNonZeroPercent / 100;

    QRandomGenerator *generator = QRandomGenerator::global();

    // Генерация элементов только для одной половины матрицы
    for (int i = 0; i < numNonZeroElements / 2; ++i) {
        int row = generator->bounded(numRows);
        int col = generator->bounded(numCols);
        int value = generator->bounded(1, 100);
        int value2 = generator->bounded(1, 100);        // случайные значения от 1 до 100

        addElement(row, col, value);
        addElement(col, row, value2);
    }
}



void SparseMatrix::redistributeSparseMatrix(double b)
{
    QList<QPair<int, int>> positions;
    QVector<double> greaterThanB;
    QVector<double> lessOrEqualToB;

    // Разделение элементов на две группы
    for (int i = 0; i < values.size(); ++i) {
        positions.append(qMakePair(rows[i], cols[i]));
        if (values[i] > b) {
            greaterThanB.append(values[i]);
        } else {
            lessOrEqualToB.append(values[i]);
        }
    }

    // Очистка матрицы
    clear();

    // Восстановление позиций с новыми значениями
    int index = 0;
    for (double value : greaterThanB) {
        addElement(positions[index].first, positions[index].second, value);
        ++index;
    }
    for (double value : lessOrEqualToB) {
        addElement(positions[index].first, positions[index].second, value);
        ++index;
    }
}
