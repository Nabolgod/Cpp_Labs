#include <iostream>
#include <string>
#include <any>

using namespace std;

class MathObject {
public:
	string name_math_obj;

	virtual ~MathObject() = default;

	// Обязательный для реализации метод сложения объектов одного типа 
	virtual MathObject operator+(const Derived& other) const = 0;

	// Обязательный для реализации метод вычитания объектов одного типа 
	virtual MathObject operator-(const Derived& other) const = 0;

	// Обязательный для реализации метод умножения объектов одного типа 
	virtual MathObject operator*(const Derived& other) const = 0;

	// Обязательный для реализации метод умножения объекта с числом
	virtual MathObject operator*(int scalar) const = 0;

	// Обязательный для реализации метод строкового представления объекта 
	virtual void str_view const = 0;

	// Обязательный для реализации метод возврата нового объекта
	virtual MathObject new_obj_return const = 0;
};

class Matrix : public MathObject<Matrix> {
private:
	int rows, cols;
	int content[]; // Переменная для хранения значений 

	void set_rows() {
		cout << "Введите кол-во строк: ";
		cin >> rows;
	}

	void set_cols() {
		cout << "Введите кол-во столбцов: ";
		cin >> cols;
	}

	void fill_matrix() {
		int element;

		cout << "Заполните матрицу: ";
		for (int i; i <= rows; i++) {
			for (int j; j <= cols; j++) {
				cout << "Введите значения для элемента [" << i << ", " << j << "] :";
				cin >> element;

				content[i][j] = element;
			}
		}
	}

public:
	Matrix(){
		set_rows();
		set_cols();
		fill_matrix();
	}

	Matrix(int r, int c, int cnt) {
		rows = r;
		cols = c;
		content = cnt;
	}

	string name_math_obj = "Матрица";
	
	// Определение перегрузки оператора сложения для сложения матриц
	Matrix* operator+(const Matrix& other) const override {
		int r, c;
		int new_content[];


		return new Matrix(r, c, new_content);
	}

	// Определение перегрузки оператора сложения для вычитания матриц
	Matrix* operator-(const Matrix& other) const override {
		int r, c;
		int new_content[];


		return new Matrix(r, c, new_content);
	}

	// Определение перегрузки оператора для умножения матриц
	Matrix* operator*(const Matrix& other) const override {
		int r, c;
		int new_content[];


		return new Matrix(r, c, new_content);
	}

	// Определение перегрузки оператора для умножения матрицы с числом
	Matrix* operator*(int scalar) const override {
		int r, c;
		int new_content[];


		return new Matrix(r, c, new_content);
	}

	// Возврат нового объекта
	Matrix new_obj_return() override {
		return Matrix();
	}

	// Вывод вида объекта в консоль
	void str_view() override {
		for (int i; i <= rows; i++) {
			cout << "[";
			for (int j; j <= cols; j++) {
				cout << content[i][j] << " ";
			}
			cout << "]" << endl;
		}
	}
};

MathObject initialization_object_first() {
	int choice;

	do {
		cout << "1. Матрица" << endl;
		cout << "2. Полином" << endl;
		cout << "3. Вектор" << endl;
		cout << "4. Дробь" << endl;
		cout << "5. Комплексное число" << endl;

		cout << "Выберите первый объект операции: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			return Matrix();
			break;
		case 2:
			return Polynomial();
			break;
		case 3:
			return Vector();
			break;
		case 4:
			return Fraction();
			break;
		case 5:
			return СomplexNumber();
			break;
		default:
			break;
		}
	} while (true);
}

MathObject initialization_object_second(MathObject first_obj) {
	int choice;
	int integer_work;

	do {
		cout << "1. " << first_obj.name_math_obj << endl;
		cout << "2. Число" << endl;

		cout << "Выберите второй объект операции: ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
			return first_obj.new_obj_return();
			break;
		case 2:
			cin >> integer_work;
			return integer_work;
			break;
		default:
			break;
		}
	} while{true};
}

MathObject operation_result(MathObject first_obj, MathObject second_obj) {
	int choice;

	do {
		cout << "1. Сложение" << endl;
		cout << "2. Вычитание" << endl;
		cout << "3. Умножение" << endl;

		cout << "Выберите операцию: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			return first_obj + second_obj;
			break;
		case 2:
			return first_obj - second_obj;
			break;
		case 3:
			return first_obj * second_obj;
			break;
		default:
			break;
		}
	} while (true);
}

MathObject operation_result(MathObject first_obj, int second_obj) {
	int choice;

	do {
		cout << "1. Умножение" << endl;

		cout << "Выберите операцию: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			return first_obj * second_obj;
			break;
		default:
			break;
		}
	} while (true);
}

void menu() {
	cout << "Добро пожаловать в консольное меню для выполнения математических операция с различными объектами!\n\n";

	MathObject first_obj = initialization_object_first();
	MathObject double_obj = initialization_object_second(first_obj);

	MathObject result_obj = operation_result(first_obj, double_obj);

	result_obj.str_view();

}

int main() {
	setlocale(LC_ALL, "RU");
	menu();
	return 0;
}
