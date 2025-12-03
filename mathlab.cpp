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

#include <iostream>
#include <string>

using namespace std;

class MathObject {
public:
    string name_math_obj;

    virtual ~MathObject() = default;

    // Методы для операций
    virtual MathObject* operator+(const MathObject& other) const = 0;
    virtual MathObject* operator-(const MathObject& other) const = 0;
    virtual MathObject* operator*(const MathObject& other) const = 0;
    virtual MathObject* operator*(int scalar) const = 0;

    // Метод строкового представления
    virtual void str_view() const = 0;

    // Метод возврата нового объекта
    virtual MathObject* new_obj_return() const = 0;
};

class Matrix : public MathObject {
private:
    int rows, cols;
    int** content;

    // Заполнение матрицы (приватный метод)
    void fill_matrix() {
        cout << "Заполните матрицу " << rows << "x" << cols << ":" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "Введите значения для элемента [" << i + 1 << ", " << j + 1 << "] : ";
                cin >> content[i][j];
            }
        }
    }

public:
    string name_math_obj = "Матрица";

    // Конструктор с ручным вводом
    Matrix() {
        cout << "\nСоздание матрицы:" << endl;

        // Ввод размеров с проверкой
        while (true) {
            cout << "Введите кол-во строк: ";
            cin >> rows;
            cout << "Введите кол-во столбцов: ";
            cin >> cols;

            if (rows > 0 && cols > 0) {
                break;
            }
            cout << "Ошибка: размеры должны быть положительными числами. Попробуйте снова.\n";
        }

        // Выделение памяти
        content = new int* [rows];
        for (int i = 0; i < rows; i++) {
            content[i] = new int[cols];
        }

        fill_matrix();
    }

    // Конструктор с параметрами (для создания результата операций)
    Matrix(int r, int c) : rows(r), cols(c) {
        content = new int* [rows];
        for (int i = 0; i < rows; i++) {
            content[i] = new int[cols]();
        }
    }

    // Деструктор
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] content[i];
        }
        delete[] content;
    }

    // Сложение матриц
    Matrix* operator+(const MathObject& other) const override {
        const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
        if (!other_matrix) {
            cout << "Ошибка: нельзя складывать матрицу с объектом другого типа." << endl;
            return nullptr;
        }

        if (rows != other_matrix->rows || cols != other_matrix->cols) {
            cout << "Ошибка: матрицы должны быть одного размера для сложения." << endl;
            return nullptr;
        }

        Matrix* result = new Matrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result->content[i][j] = content[i][j] + other_matrix->content[i][j];
            }
        }
        return result;
    }

    // Вычитание матриц
    Matrix* operator-(const MathObject& other) const override {
        const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
        if (!other_matrix) {
            cout << "Ошибка: нельзя вычитать объект другого типа из матрицы." << endl;
            return nullptr;
        }

        if (rows != other_matrix->rows || cols != other_matrix->cols) {
            cout << "Ошибка: матрицы должны быть одного размера для вычитания." << endl;
            return nullptr;
        }

        Matrix* result = new Matrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result->content[i][j] = content[i][j] - other_matrix->content[i][j];
            }
        }
        return result;
    }

    // Умножение матриц
    Matrix* operator*(const MathObject& other) const override {
        const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
        if (!other_matrix) {
            cout << "Ошибка: нельзя умножать матрицу на объект другого типа." << endl;
            return nullptr;
        }

        if (cols != other_matrix->rows) {
            cout << "Ошибка: количество столбцов первой матрицы должно совпадать с количеством строк второй матрицы." << endl;
            return nullptr;
        }

        Matrix* result = new Matrix(rows, other_matrix->cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other_matrix->cols; j++) {
                result->content[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result->content[i][j] += content[i][k] * other_matrix->content[k][j];
                }
            }
        }
        return result;
    }

    // Умножение матрицы на скаляр
    Matrix* operator*(int scalar) const override {
        Matrix* result = new Matrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result->content[i][j] = content[i][j] * scalar;
            }
        }
        return result;
    }

    // Возврат нового объекта
    Matrix* new_obj_return() const override {
        return new Matrix();
    }

    // Вывод матрицы
    void str_view() const override {
        cout << "\nМатрица " << rows << "x" << cols << ":" << endl;
        for (int i = 0; i < rows; i++) {
            cout << "[ ";
            for (int j = 0; j < cols; j++) {
                cout << content[i][j] << " ";
            }
            cout << "]" << endl;
        }
    }
};

MathObject* initialization_object_first() {
    int choice;

    do {
        cout << "\nВыберите тип первого объекта:" << endl;
        cout << "1. Матрица" << endl;
        cout << "2. Полином" << endl;
        cout << "3. Вектор" << endl;
        cout << "4. Дробь" << endl;
        cout << "5. Комплексное число" << endl;

        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            return new Matrix();
        case 2:
            return new Matrix();
        case 3:
            return new Matrix();
        case 4:
            return new Matrix();
        case 5:
            return new Matrix();
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (true);
}

MathObject* initialization_object_second(MathObject* first_obj) {
    int choice;

    do {
        cout << "\nВыберите тип второго объекта:" << endl;
        cout << "1. " << first_obj->name_math_obj << " (такой же как первый)" << endl;
        cout << "2. Целое число" << endl;

        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            return first_obj->new_obj_return();
        case 2:
            // Возвращаем nullptr как индикатор числа
            return nullptr;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (true);
}

void perform_operation(MathObject* first_obj, bool is_second_number, int number = 0) {
    int choice;

    do {
        cout << "\nВыберите операцию:" << endl;

        if (is_second_number) {
            cout << "1. Умножение на число" << endl;
            cout << "Ваш выбор: ";
            cin >> choice;

            if (choice == 1) {
                MathObject* result = (*first_obj) * number;
                if (result) {
                    cout << "\nРезультат операции:" << endl;
                    result->str_view();
                    delete result;
                }
                return;
            }
            else {
                cout << "Неверный выбор. Попробуйте снова." << endl;
            }
        }
        else {
            cout << "1. Сложение" << endl;
            cout << "2. Вычитание" << endl;
            cout << "3. Умножение" << endl;
            cout << "Ваш выбор: ";
            cin >> choice;

            MathObject* second_obj = first_obj->new_obj_return();
            if (!second_obj) {
                cout << "Ошибка при создании второго объекта." << endl;
                return;
            }

            MathObject* result = nullptr;
            switch (choice) {
            case 1:
                result = (*first_obj) + (*second_obj);
                break;
            case 2:
                result = (*first_obj) - (*second_obj);
                break;
            case 3:
                result = (*first_obj) * (*second_obj);
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
                delete second_obj;
                continue;
            }

            delete second_obj;

            if (result) {
                cout << "\nРезультат операции:" << endl;
                result->str_view();
                delete result;
            }
            return;
        }
    } while (true);
}

void menu() {
    cout << "Добро пожаловать в консольное меню для выполнения математических операций с различными объектами!\n\n";

    MathObject* first_obj = initialization_object_first();

    cout << "\nПервый объект:" << endl;
    first_obj->str_view();

    MathObject* second_obj_ptr = initialization_object_second(first_obj);

    if (second_obj_ptr) {
        // Второй объект - такой же как первый
        cout << "\nВторой объект:" << endl;
        second_obj_ptr->str_view();
        perform_operation(first_obj, second_obj_ptr, false);
        delete second_obj_ptr;
    }
    else {
        // Второй объект - число
        int number;
        cout << "Введите целое число: ";
        cin >> number;
        perform_operation(first_obj, true, number);
    }

    delete first_obj;
}

int main() {
    setlocale(LC_ALL, "RU");
    menu();
    return 0;
}
