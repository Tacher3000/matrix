import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: "Sparse Matrix Generator"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        RowLayout {
            spacing: 10

            Label {
                text: "Rows:"
            }

            TextField {
                id: rowsInput
                width: 100
                placeholderText: "Enter number of rows"
            }
        }

        RowLayout {
            spacing: 10

            Label {
                text: "Columns:"
            }

            TextField {
                id: colsInput
                width: 100
                placeholderText: "Enter number of columns"
            }
        }

        RowLayout {
            spacing: 10

            Button {
                text: "Generate Matrix"
                onClicked: {
                    // Здесь вызывается метод для генерации матрицы
                    let numRows = parseInt(rowsInput.text)
                    let numCols = parseInt(colsInput.text)
                    if (!isNaN(numRows) && !isNaN(numCols)) {
                        // Вызов метода C++ для генерации матрицы
                        sparseMatrix.generateSparseMatrix(numRows, numCols, numNonZeroElements)
                    } else {
                        console.log("Invalid input for rows or columns")
                    }
                }
            }

            Button {
                text: "Load Matrix"
                onClicked: {
                    // Здесь вызывается метод для загрузки матрицы из файла
                    sparseMatrix.loadFromFile("path_to_your_matrix_file.txt")
                }
            }
        }
    }
}
