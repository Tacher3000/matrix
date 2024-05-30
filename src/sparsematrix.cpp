#include "sparsematrix.h"
#include <QtAlgorithms>
#include <QRandomGenerator>

SparseMatrix::SparseMatrix(QObject *parent) : QObject(parent), size(0), predominant("0"), symmetric(true) {}

SparseMatrix::SparseMatrix(const QVector<Position>& positions, const QVector<QVariant>& diagonal, int size, const QVariant& predominant, bool symmetric, QObject *parent)
    : QObject(parent), positions(positions), diagonal(diagonal), size(size), predominant(predominant), symmetric(symmetric) {}

// SparseMatrix* SparseMatrix::copy() const {
//     return new SparseMatrix(positions, diagonal, size, predominant, symmetric);
// }

void SparseMatrix::clear() {
    size = 0;
    diagonal.clear();
    positions.clear();
    predominant = "0";
    symmetric = true;
}

// bool SparseMatrix::matrixFilled() const {
//     return !diagonal.isEmpty();
// }

void SparseMatrix::printData() const{
    for (const Position& pos : positions) {
        qDebug() << "Value1:" << pos.value1.toString() << "Value2:" << pos.value2.toString() << "\tx1:" << pos.x1 << "\tx2:" << pos.x2;
    }
}

void SparseMatrix::generate(int size, float sparsity, int randStart, int randEnd, const QVariant& predominant) {
    clear(); // Clear the matrix before generating new data

    // Calculate the number of non-zero elements based on the given sparsity
    int numbersAmount = qRound((1 - sparsity) * size * size);

    // Calculate the number of elements that should be on the diagonal
    int diagonalNumbersAmount = QRandomGenerator::global()->bounded(qMin(numbersAmount, size) + 1);

    // Calculate the number of elements that are not on the diagonal
    int nonDiagonalNumbersAmount = numbersAmount - diagonalNumbersAmount;

    // Ensure that the number of non-diagonal elements is even
    if (nonDiagonalNumbersAmount % 2 != 0) {
        nonDiagonalNumbersAmount++;
        diagonalNumbersAmount--;
    }
    nonDiagonalNumbersAmount /= 2;

    // Create a vector to store the positions of diagonal elements
    QVector<int> diagonalPositions(size);
    std::iota(diagonalPositions.begin(), diagonalPositions.end(), 0);

    // Shuffle the positions of diagonal elements and resize to the required size
    if (diagonalNumbersAmount > 0) {
        std::shuffle(diagonalPositions.begin(), diagonalPositions.end(), *QRandomGenerator::global());
        diagonalPositions.resize(diagonalNumbersAmount);
    } else {
        diagonalPositions.clear();
    }

    // Fill the diagonal elements of the matrix with a certain value
    diagonal.fill(predominant, size);
    for (int pos : diagonalPositions) {
        diagonal[pos] = QRandomGenerator::global()->bounded(randStart, randEnd + 1);
    }

    // Create a vector to store the positions of non-diagonal elements
    QVector<QPair<int, int>> nonDiagonalPositions;
    for (int i = 1; i < size; ++i) {
        for (int j = 0; j < i; ++j) {
            nonDiagonalPositions.append(qMakePair(i, j));
        }
    }
    // Shuffle the positions of non-diagonal elements and resize to the required size
    std::shuffle(nonDiagonalPositions.begin(), nonDiagonalPositions.end(), *QRandomGenerator::global());
    nonDiagonalPositions.resize(nonDiagonalNumbersAmount);

    // Fill the non-diagonal elements of the matrix with random values
    for (const auto& pos : nonDiagonalPositions) {
        QVariant value1 = QRandomGenerator::global()->bounded(randStart, randEnd + 1);
        QVariant value2 = QRandomGenerator::global()->bounded(randStart, randEnd + 1);
        positions.append({value1, value2, pos.first, pos.second});
    }

    // Set the size of the matrix and the predominant value for filling
    this->size = size;
    this->predominant = predominant;
}



void SparseMatrix::readMatrixFromFile(const QString& inputFilePath, bool symmetric) {
    clear();

    QFile file(inputFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);

    predominant = in.readLine().trimmed();
    QStringList diagonalElements = in.readLine().trimmed().split(" ");
    for (const QString& el : diagonalElements) {
        diagonal.append(el == predominant || !el.toInt() ? QVariant(el) : QVariant(el.toInt()));
    }

    QStringList value1List = in.readLine().trimmed().split(" ");
    QStringList value2List = in.readLine().trimmed().split(" ");
    QStringList x1List = in.readLine().trimmed().split(" ");
    QStringList x2List = in.readLine().trimmed().split(" ");

    for (int i = 0; i < value1List.size(); ++i) {
        QVariant val1 = value1List[i] == predominant || !value1List[i].toInt() ? QVariant(value1List[i]) : QVariant(value1List[i].toInt());
        QVariant val2 = value2List[i] == predominant || !value2List[i].toInt() ? QVariant(value2List[i]) : QVariant(value2List[i].toInt());
        positions.append({val1, val2, x1List[i].toInt(), x2List[i].toInt()});
    }

    this->symmetric = symmetric;
    size = diagonal.size();
}

void SparseMatrix::makeFileOfMatrix(const QString& outputFilePath) const {
    QFile file(outputFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);

    out << predominant.toString() << "\n";
    for (const QVariant& el : diagonal) {
        out << el.toString() << " ";
    }
    out << "\n";

    for (const Position& pos : positions) {
        out << pos.value1.toString() << " ";
    }
    out << "\n";

    for (const Position& pos : positions) {
        out << pos.value2.toString() << " ";
    }
    out << "\n";

    for (const Position& pos : positions) {
        out << pos.x1 << " ";
    }
    out << "\n";

    for (const Position& pos : positions) {
        out << pos.x2 << " ";
    }
    out << "\n";
}



void SparseMatrix::printMatrix(int head, int tail) const {
    QVector<int> htRange;
    QDebug debug = qDebug().nospace();
    debug.noquote();
    if (head != -1 && tail != -1) {
        for (int i = 0; i < head; ++i) htRange.append(i);
        for (int i = size - tail; i < size; ++i) htRange.append(i);
    } else {
        for (int i = 0; i < size; ++i) htRange.append(i);
    }

    for (int i : htRange) {
        for (int j : htRange) {
            if (i == j) {
                debug << diagonal[i].toString() << "\t";
            } else {
                bool flag = false;
                for (const Position& pos : positions) {
                    if ((i == pos.x1 && j == pos.x2) || (i == pos.x2 && j == pos.x1)) {
                        if (i < j) {
                            debug << pos.value1.toString() << "\t";
                        } else {
                            debug << pos.value2.toString() << "\t";
                        }
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    debug << predominant.toString() << "\t";
                }
            }
            if (head != -1 && tail != -1 && j == head - 1) {
                debug << "...\t";
            }
        }
        if (head != -1 && tail != -1 && i == head - 1) {
            debug << "\n" << QString(".\t").repeated(head + tail + 1);
            debug << "\n" << QString(".\t").repeated(head + tail + 1);
            debug << "\n" << QString(".\t").repeated(head + tail + 1);
        }
        debug << "\n";
    }
}

void SparseMatrix::printMatrixToTextEdit(QTextEdit* textEdit, int head, int tail) const {
    QVector<int> htRange;
    QString matrixOutput;
    QTextStream stream(&matrixOutput);

    if (head != -1 && tail != -1) {
        for (int i = 0; i < head; ++i) htRange.append(i);
        for (int i = size - tail; i < size; ++i) htRange.append(i);
    } else {
        for (int i = 0; i < size; ++i) htRange.append(i);
    }

    for (int i : htRange) {
        for (int j : htRange) {
            if (i == j) {
                stream << diagonal[i].toString() << "\t";
            } else {
                bool flag = false;
                for (const Position& pos : positions) {
                    if ((i == pos.x1 && j == pos.x2) || (i == pos.x2 && j == pos.x1)) {
                        if (i < j) {
                            stream << pos.value1.toString() << "\t";
                        } else {
                            stream << pos.value2.toString() << "\t";
                        }
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    stream << predominant.toString() << "\t";
                }
            }
            if (head != -1 && tail != -1 && j == head - 1) {
                stream << "...\t";
            }
        }
        if (head != -1 && tail != -1 && i == head - 1) {
            stream << "\n" << QString(".\t").repeated(head + tail + 1);
            stream << "\n" << QString(".\t").repeated(head + tail + 1);
            stream << "\n" << QString(".\t").repeated(head + tail + 1);
        }
        stream << "\n";
    }

    textEdit->setPlainText(matrixOutput);
}


void SparseMatrix::changeValues(int b) {
    QVector<Position> all_positions = positions;
    for (int i = 0; i < diagonal.size(); ++i) {
        if (diagonal[i] != predominant) {
            all_positions.append({diagonal[i], diagonal[i], i, i});
        }
    }

    QVector<QVariant> lesser_elements;
    QVector<QVariant> bigger_elements;
    for (const auto& pos : all_positions) {
        if (pos.x1 == pos.x2) {
            QVariant value = pos.value1;
            if (value.toInt() <= b) {
                lesser_elements.append(value);
            } else {
                bigger_elements.append(value);
            }
        } else {
            if (pos.value1.toInt() <= b) {
                lesser_elements.append(pos.value1);
            } else {
                bigger_elements.append(pos.value1);
            }
            if (pos.value2.toInt() <= b) {
                lesser_elements.append(pos.value2);
            } else {
                bigger_elements.append(pos.value2);
            }
        }
    }



    // Объединяем массивы больших и меньших элементов
    QVector<QVariant> elements = bigger_elements;
    elements.append(lesser_elements);

    QVector<QPair<int, int>> tempPairs;

    // Проходим по каждому элементу вектора positions
    for (const Position& pos : all_positions) {
        if(pos.x1 != pos.x2){
            tempPairs.append(QPair<int, int>(pos.x2, pos.x1));
            tempPairs.append(QPair<int, int>(pos.x1, pos.x2));
        }else
            tempPairs.append(QPair<int, int>(pos.x1, pos.x2));
    }

    std::sort(tempPairs.begin(), tempPairs.end());

    for (const auto& pair : tempPairs) {
        int x1 = pair.first;
        int x2 = pair.second;

        for (auto& pos : all_positions) {
            if (pos.x1 == x1 && pos.x2 == x2 && x1 == x2) {
                if (!elements.isEmpty()) {
                    diagonal[pos.x1] = elements.front();
                    elements.pop_front();
                }
                break;
            }
            if (pos.x1 == x1 && pos.x2 == x2) {
                if (!elements.isEmpty()) {
                    pos.value2 = elements.front();
                    elements.pop_front();
                }
                break;
            }
            if (pos.x1 == x2 && pos.x2 == x1) {
                if (!elements.isEmpty()) {
                    pos.value1 = elements.front();
                    elements.pop_front();
                }

                break;
            }
        }
    }

    // Обновляем позиции
    positions.clear();
    for (const auto& pos : all_positions) {
        if (pos.x1 != pos.x2) {
            positions.append(pos);
        }
    }
}

