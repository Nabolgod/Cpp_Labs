#include <iostream>
#include <string>

using namespace std;

class MathObject {
public:
    virtual ~MathObject() = default;
    
    // Чисто виртуальные методы - должны быть реализованы в дочерних классах
    virtual MathObject* __add__(const MathObject& other) const = 0;
    virtual MathObject* __sub__(const MathObject& other) const = 0;
    virtual MathObject* __mul__(const MathObject& other) const = 0;
    virtual MathObject* __mul__(int scalar) const = 0;
    virtual std::string __str__() const = 0;
};

class Matrix : public MathObject {
private:
    // данные матрицы
    int rows, cols;
    
public:
    Matrix(int r = 0, int c = 0) : rows(r), cols(c) {}
    
    // Реализация абстрактных методов
    MathObject* __add__(const MathObject& other) const override {
        // Здесь ты просто реализуешь сложение матриц
        // Пока заглушка - возвращаем новую матрицу
        return new Matrix(rows, cols);
    }
    
    MathObject* __sub__(const MathObject& other) const override {
        return new Matrix(rows, cols);
    }
    
    MathObject* __mul__(const MathObject& other) const override {
        return new Matrix(rows, cols);
    }
    
    MathObject* __mul__(int scalar) const override {
        return new Matrix(rows, cols);
    }
    
    std::string __str__() const override {
        return "Matrix[" + std::to_string(rows) + "x" + std::to_string(cols) + "]";
    }
    
    // Специфичные методы матрицы
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

class Polynomial : public MathObject {
public:
	Polynomial __add__(Matrix other) {
		return Polynomial();
	}

	Polynomial __sub__(Matrix other) {
		return Polynomial();
	}

	Polynomial __mul__(Matrix other) {
		return Polynomial();
	}

	Polynomial __mul__(int other) {
		return Polynomial();
	}

	void __str__(int other) {
		cout << "" << endl;
	}
};

class Vector : public MathObject {
public:
	Vector __add__(Vector other) {
		return Vector();
	}

	Vector __sub__(Vector other) {
		return Vector();
	}

	Vector __mul__(Vector other) {
		return Vector();
	}

	Vector __mul__(int other) {
		return Vector();
	}

	void __str__(int other) {
		cout << "" << endl;
	}
};

class Fraction : public MathObject {
public:
	Fraction __add__(Fraction other) {
		return Fraction();
	}

	Fraction __sub__(Fraction other) {
		return Fraction();
	}

	Fraction __mul__(Fraction other) {
		return Fraction();
	}

	Fraction __mul__(int other) {
		return Fraction();
	}

	void __str__(int other) {
		cout << "" << endl;
	}
};

class СomplexNumber : public MathObject {
public:
	СomplexNumber __add__(СomplexNumber other) {
		return СomplexNumber();
	}

	СomplexNumber __sub__(СomplexNumber other) {
		return СomplexNumber();
	}

	СomplexNumber __mul__(СomplexNumber other) {
		return СomplexNumber();
	}

	СomplexNumber __mul__(int other) {
		return СomplexNumber();
	}

	void __str__(int other) {
		cout << "" << endl;
	}
};

int main() {

	
	return 0;
}
