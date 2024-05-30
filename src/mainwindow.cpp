// mainwindow.cpp

#include "mainwindow.h"
#include <_mingw_mac.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _matrixDisplay(new QTextEdit(this)),
    _sizeInput(new QLineEdit(this)), _bInput(new QLineEdit(this)), _predominantInput(new QLineEdit(this)),
    _dischargeInput(new QLineEdit(this)), _printWindow(new QCheckBox(this)), _printKonsol(new QCheckBox(this)), _reducePrint(new QCheckBox(this)), _generateButton(new QPushButton("Сгенерировать матрицу", this)),
    _algorithmButton(new QPushButton("относительно b", this)), _loadButton(new QPushButton("Загрузить матрицу", this)), _saveButton(new QPushButton("Сохранить матрицу", this))
{
    QWidget *centralWidget = new QWidget(this);

    _sizeInput->setMaximumSize(300, 40);
    _sizeInput->setMinimumSize(200, 40);
    _predominantInput->setMaximumSize(300, 40);
    _predominantInput->setMinimumSize(200, 40);
    _dischargeInput->setMaximumSize(300, 40);
    _dischargeInput->setMinimumSize(200, 40);
    _bInput->setMaximumSize(300, 40);
    _bInput->setMinimumSize(200, 40);

    _generateButton->setMaximumSize(300, 100);
    _generateButton->setMinimumSize(200, 40);
    _algorithmButton->setMaximumSize(300, 100);
    _algorithmButton->setMinimumSize(200, 40);

    _loadButton->setMaximumSize(300, 100);
    _loadButton->setMinimumSize(200, 40);
    _saveButton->setMaximumSize(300, 100);
    _saveButton->setMinimumSize(200, 40);

    QFrame *vline1 = new QFrame;
    vline1->setFrameShape(QFrame::VLine);
    // vline1->setFrameShadow(QFrame::Sunken);

    QFrame *vline2 = new QFrame;
    vline2->setFrameShape(QFrame::VLine);
    // vline2->setFrameShadow(QFrame::Sunken);

    QFrame *vline3 = new QFrame;
    vline3->setFrameShape(QFrame::VLine);

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(14);

    QFont fontBold;
    fontBold.setFamily("Arial");
    fontBold.setPointSize(14);
    fontBold.setBold(true);

    QLabel *label1 = new QLabel("Размерность", this);
    label1->setFont(font);
    QLabel *label2 = new QLabel("Преобладающий", this);
    label2->setFont(font);
    QLabel *label3 = new QLabel("Разряженность %)", this);
    label3->setFont(font);
    QLabel *label4 = new QLabel("b", this);
    label4->setFont(font);
    QLabel *label5 = new QLabel("Настройки вывода", this);
    label5->setFont(fontBold);
    QLabel *label6 = new QLabel("Экран", this);
    label6->setFont(font);
    QLabel *label7 = new QLabel("Консоль", this);
    label7->setFont(font);
    QLabel *label8 = new QLabel("Сократить матрицу", this);
    label8->setFont(font);

    _generateButton->setFont(font);
    _algorithmButton->setFont(font);
    _loadButton->setFont(font);
    _saveButton->setFont(font);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QGridLayout *inputLayout = new QGridLayout;
    inputLayout->addWidget(label1, 0, 0, 1, 1, Qt::AlignRight);
    inputLayout->addWidget(_sizeInput, 0, 1, 1, 1);
    inputLayout->addWidget(label2, 1, 0, 1, 1, Qt::AlignRight);
    inputLayout->addWidget(_predominantInput, 1, 1, 1, 1);
    inputLayout->addWidget(label3, 2, 0, 1, 1, Qt::AlignRight);
    inputLayout->addWidget(_dischargeInput, 2, 1, 1, 1);
    inputLayout->addWidget(label4, 3, 0, 1, 1, Qt::AlignRight);
    inputLayout->addWidget(_bInput, 3, 1, 1, 1);

    inputLayout->addWidget(vline1, 0, 2, 4, 1);

    inputLayout->addWidget(label5, 0, 3, 1, 2, Qt::AlignCenter);
    inputLayout->addWidget(label6, 1, 3, 1, 1, Qt::AlignRight);
    inputLayout->addWidget(_printWindow, 1, 4, 1, 1, Qt::AlignLeft);
    inputLayout->addWidget(label7, 2, 3, 1, 1, Qt::AlignRight);
    inputLayout->addWidget(_printKonsol, 2, 4, 1, 1, Qt::AlignLeft);
    inputLayout->addWidget(label8, 3, 3, 1, 1, Qt::AlignRight);
    inputLayout->addWidget(_reducePrint, 3, 4, 1, 1, Qt::AlignLeft);

    inputLayout->addWidget(vline2, 0, 5, 4, 1);

    inputLayout->addWidget(_generateButton, 0, 6, 2, 1);
    inputLayout->addWidget(_algorithmButton, 2, 6, 2, 1);

    inputLayout->addWidget(vline3, 0, 7, 4, 1);

    inputLayout->addWidget(_loadButton, 0, 8, 2, 1);
    inputLayout->addWidget(_saveButton, 2, 8, 2, 1);

    inputLayout->setColumnStretch(0, 1);
    inputLayout->setColumnStretch(1, 1);
    inputLayout->setColumnStretch(2, 1);
    inputLayout->setColumnStretch(3, 1);
    inputLayout->setColumnStretch(4, 1);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(_matrixDisplay);

    setCentralWidget(centralWidget);

    connect(_generateButton, &QPushButton::clicked, this, &MainWindow::generateMatrix);
    connect(_algorithmButton, &QPushButton::clicked, this, &MainWindow::stosunkowoB);
    connect(_loadButton, &QPushButton::clicked, this, &MainWindow::loadMatrix);
    connect(_saveButton, &QPushButton::clicked, this, &MainWindow::saveMatrix);
}

MainWindow::~MainWindow() {}

void MainWindow::generateMatrix() {
    int size = _sizeInput->text().toInt();
    float discharge = _dischargeInput->text().toFloat();
    QString predominant = _predominantInput->text();

    _matrix.clear();
    _matrix.generate(size, discharge / 100, 1, 100, QVariant(predominant));

    print();
}

void MainWindow::stosunkowoB()
{
    _matrix.changeValues(_bInput->text().toInt());
    print();
}

void MainWindow::loadMatrix() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Matrix File");
    if (!fileName.isEmpty()) {
        _matrix.clear();
        _matrixDisplay->clear();
        _matrix.readMatrixFromFile(fileName);

        print();
    }
}

void MainWindow::saveMatrix() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Matrix File");
    if (!fileName.isEmpty()) {
        _matrix.makeFileOfMatrix(fileName);
    }
}

void MainWindow::print(){
    int head = -1, tail = -1;

    if(_reducePrint->checkState())
        head = tail = 3;


    if(_printWindow->checkState())
        _matrix.printMatrixToTextEdit(_matrixDisplay, head, tail);
    if(_printKonsol->checkState())
        _matrix.printMatrix(head, tail);
    // _matrix.printData();
}



