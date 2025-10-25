#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

template <typename T>
void my_input(T& value, string text) {
    cout << text;
    cin >> value;
}

class MathObject {
public:
    virtual ~MathObject() = default;

    virtual MathObject& operator+(const MathObject& other) const = 0;
    virtual MathObject& operator-(const MathObject& other) const = 0;
    virtual MathObject& operator*(const MathObject& other) const = 0;
    virtual MathObject& operator*(double scalar) const = 0;

    virtual std::string toString() const = 0;
};

class Matrix : public MathObject {
private:
    double** data;
    int rows, cols;

    void allocateMemory() {
        data = new double* [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = 0.0;
            }
        }
    }

    void freeMemory() {
        if (data) {
            for (int i = 0; i < rows; ++i) {
                delete[] data[i];
            }
            delete[] data;
        }
    }

public:
    ~Matrix() {
        freeMemory();
    }

    Matrix(int r, int c){
        rows = r;
        cols = c;
        allocateMemory();
    }

    Matrix(double** matrixData, int r, int c){
        rows = r;
        cols = c;

        allocateMemory();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = matrixData[i][j];
            }
        }
    }

    void setValue(int row, int col, double value) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            data[row][col] = value;
        }
    }

    double getValue(int row, int col) const {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return data[row][col];
        }
        return 0.0;
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // Оператор сложения
    Matrix& operator+(const MathObject& other) const override {
        const Matrix* otherMatrix = dynamic_cast<const Matrix*>(&other);
        if (!otherMatrix || rows != otherMatrix->rows || cols != otherMatrix->cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }

        Matrix* result = new Matrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result->setValue(i, j, data[i][j] + otherMatrix->getValue(i, j));
            }
        }
        return *result;
    }

    // Оператор вычитания
    Matrix& operator-(const MathObject& other) const override {
        const Matrix* otherMatrix = dynamic_cast<const Matrix*>(&other);
        if (!otherMatrix || rows != otherMatrix->rows || cols != otherMatrix->cols) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction");
        }

        Matrix* result = new Matrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result->setValue(i, j, data[i][j] - otherMatrix->getValue(i, j));
            }
        }
        return *result;
    }

    // Оператор умножения матриц
    Matrix& operator*(const MathObject& other) const override {
        const Matrix* otherMatrix = dynamic_cast<const Matrix*>(&other);
        if (!otherMatrix || cols != otherMatrix->rows) {
            throw std::invalid_argument("Matrix dimensions are incompatible for multiplication");
        }

        Matrix* result = new Matrix(rows, otherMatrix->cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < otherMatrix->cols; ++j) {
                double sum = 0.0;
                for (int k = 0; k < cols; ++k) {
                    sum += data[i][k] * otherMatrix->getValue(k, j);
                }
                result->setValue(i, j, sum);
            }
        }
        return *result;
    }

    // Умножение на скаляр
    Matrix& operator*(double scalar) const override {
        Matrix* result = new Matrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result->setValue(i, j, data[i][j] * scalar);
            }
        }
        return *result;
    }

    // Строковое представление
    std::string toString() const override {
        std::string result = "Matrix " + std::to_string(rows) + "x" + std::to_string(cols) + ":\n";
        for (int i = 0; i < rows; ++i) {
            result += "[ ";
            for (int j = 0; j < cols; ++j) {
                result += std::to_string(data[i][j]) + " ";
            }
            result += "]\n";
        }
        return result;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    std::cout << "1. Матрицы:\n";
    double** m1Data = new double* [2];
    m1Data[0] = new double[2] {1, 2};
    m1Data[1] = new double[2] {3, 4};

    double** m2Data = new double* [2];
    m2Data[0] = new double[2] {5, 6};
    m2Data[1] = new double[2] {7, 8};

    Matrix m1(m1Data, 2, 2);
    Matrix m2(m2Data, 2, 2);

    Matrix& sumM = dynamic_cast<Matrix&>(m1 + m2);
    Matrix& productM = dynamic_cast<Matrix&>(m1 * m2);
    Matrix& scaledM = dynamic_cast<Matrix&>(m1 * 2.5);

    std::cout << "m1:\n" << m1.toString();
    std::cout << "m2:\n" << m2.toString();
    std::cout << "m1 + m2:\n" << sumM.toString();
    std::cout << "m1 * m2:\n" << productM.toString();
    std::cout << "m1 * 2.5:\n" << scaledM.toString();

    // Освобождение памяти
    delete& sumM;
    delete& productM;
    delete& scaledM;
    for (int i = 0; i < 2; ++i) {
        delete[] m1Data[i];
        delete[] m2Data[i];
    }
    delete[] m1Data;
    delete[] m2Data;

    return 0;
}
