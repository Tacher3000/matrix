// mainwindow.cpp

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), matrixDisplay(new QTextEdit(this)),
    rowsInput(new QLineEdit(this)), colsInput(new QLineEdit(this)),
    nonZeroInput(new QLineEdit(this)), printMatrix(new QCheckBox(this)), generateButton(new QPushButton("Сгенерировать матрицу", this)),
    loadButton(new QPushButton("Загрузить матрицу", this)), saveButton(new QPushButton("Сохранить матрицу", this))
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(new QLabel("Строк", this));
    inputLayout->addWidget(rowsInput);
    inputLayout->addWidget(new QLabel("Столбцов", this));
    inputLayout->addWidget(colsInput);
    inputLayout->addWidget(new QLabel("Не нулевых элементов", this));
    inputLayout->addWidget(nonZeroInput);
    inputLayout->addWidget(printMatrix);
    inputLayout->addWidget(generateButton);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(matrixDisplay);
    mainLayout->addWidget(loadButton);
    mainLayout->addWidget(saveButton);

    setCentralWidget(centralWidget);

    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generateMatrix);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadMatrix);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveMatrix);
}

MainWindow::~MainWindow() {}

void MainWindow::generateMatrix() {
    int rows = rowsInput->text().toInt();
    int cols = colsInput->text().toInt();
    int nonZeroElements = nonZeroInput->text().toInt();
    matrix.clear();

    matrix.generateSparseMatrix(rows, cols, nonZeroElements);
    if(printMatrix->checkState())
        matrix.print();
        // displayMatrix();
}

void MainWindow::loadMatrix() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Matrix File");
    if (!fileName.isEmpty()) {
        matrix.loadFromFile(fileName);
        displayMatrix();
    }
}

void MainWindow::saveMatrix() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Matrix File");
    if (!fileName.isEmpty()) {
        matrix.saveToFile(fileName);
    }
}

void MainWindow::displayMatrix() {
    matrixDisplay->clear();

    QVector<QVector<int>> fullMatrix(matrix.numRows, QVector<int>(matrix.numCols, 0));
    for (int i = 0; i < matrix.values.size(); ++i) {
        fullMatrix[matrix.rows[i]][matrix.cols[i]] = matrix.values[i];
    }

    QString matrixString;
    const int fieldWidth = 8; // Ширина поля для каждого элемента
    const int precision = 0;  // Количество знаков после запятой

    // Находим максимальное количество символов в строке
    int maxChars = 0;
    for (const auto& row : fullMatrix) {
        int rowChars = 0;
        for (int value : row) {
            QString formattedValue = QString::number(value, 'f', precision);
            rowChars += formattedValue.length() + 1; // +1 для пробела между элементами
        }
        maxChars = std::max(maxChars, rowChars);
    }

    // Форматируем и добавляем строки матрицы в строку вывода
    for (const auto& row : fullMatrix) {
        QString rowString;
        for (int value : row) {
            QString formattedValue = QString::number(value, 'f', precision);
            rowString.append(formattedValue.rightJustified(fieldWidth, ' ')); // Выравнивание по правому краю
            rowString.append(" "); // Пробел между элементами
        }
        // Добавляем дополнительные пробелы к строкам, которые короче максимальной
        rowString.append(QString(maxChars - rowString.length(), ' '));
        matrixString.append(rowString + "\n");
    }
    matrixDisplay->setPlainText(matrixString);
}



