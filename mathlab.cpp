#include <iostream>
#include <string>

using namespace std;

class MathObject {
public:
	virtual ~MathObject() = default;

	virtual string get_name() const = 0;

	virtual MathObject* operator+(const MathObject& other) const = 0;
	virtual MathObject* operator-(const MathObject& other) const = 0;
	virtual MathObject* operator*(const MathObject& other) const = 0;
	virtual MathObject* operator*(int scalar) const = 0;

	virtual void str_view() const = 0;
	virtual MathObject* new_obj_return() const = 0;

	// Методы проверки возможности операций
	virtual bool can_add(const MathObject& other) const = 0;
	virtual bool can_subtract(const MathObject& other) const = 0;
	virtual bool can_multiply(const MathObject& other) const = 0;
	virtual bool can_multiply_scalar() const { return true; }
};

class Matrix : public MathObject {
private:
	int rows, cols;
	int** content;

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
	string get_name() const override {
		return "Матрица";
	}

	Matrix() {
		cout << "\nСоздание матрицы:" << endl;

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

		content = new int*[rows];
		for (int i = 0; i < rows; i++) {
			content[i] = new int[cols];
		}

		fill_matrix();
	}

	Matrix(int r, int c) : rows(r), cols(c) {
		content = new int*[rows];
		for (int i = 0; i < rows; i++) {
			content[i] = new int[cols]();
		}
	}

	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] content[i];
		}
		delete[] content;
	}

	// Проверка возможности операций
	bool can_add(const MathObject& other) const override {
		const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
		if (!other_matrix) return false;
		return (rows == other_matrix->rows && cols == other_matrix->cols);
	}

	bool can_subtract(const MathObject& other) const override {
		return can_add(other);
	}

	bool can_multiply(const MathObject& other) const override {
		const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
		if (!other_matrix) return false;
		return (cols == other_matrix->rows);
	}

	// Операции
	Matrix* operator+(const MathObject& other) const override {
		const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
		if (!other_matrix || !can_add(other)) return nullptr;

		Matrix* result = new Matrix(rows, cols);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result->content[i][j] = content[i][j] + other_matrix->content[i][j];
			}
		}
		return result;
	}

	Matrix* operator-(const MathObject& other) const override {
		const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
		if (!other_matrix || !can_subtract(other)) return nullptr;

		Matrix* result = new Matrix(rows, cols);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result->content[i][j] = content[i][j] - other_matrix->content[i][j];
			}
		}
		return result;
	}

	Matrix* operator*(const MathObject& other) const override {
		const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
		if (!other_matrix || !can_multiply(other)) return nullptr;

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

	Matrix* operator*(int scalar) const override {
		Matrix* result = new Matrix(rows, cols);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result->content[i][j] = content[i][j] * scalar;
			}
		}
		return result;
	}

	Matrix* new_obj_return() const override {
		return new Matrix();
	}

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

class Polynomial : public MathObject {
private:
	int degree;
	int* coefficients; // coefficients[i] - коэффициент при x^i

	void normalize() {
		// Убираем нулевые старшие коэффициенты
		while (degree > 0 && coefficients[degree] == 0) {
			degree--;
		}
	}

	void copy_coefficients(const Polynomial& other) {
		degree = other.degree;
		coefficients = new int[degree + 1];
		for (int i = 0; i <= degree; i++) {
			coefficients[i] = other.coefficients[i];
		}
	}

public:
	string get_name() const override {
		return "Полином";
	}

	Polynomial() {
		cout << "\nСоздание полинома:" << endl;

		cout << "Введите степень полинома: ";
		do {
			cin >> degree;

			if (degree < 0) {
				cout << "Ошибка: степень не может быть отрицательной.\nПопробуйте снова: ";
			}

		} while (degree < 0);


		coefficients = new int[degree + 1];

		cout << "Введите коэффициенты полинома (от свободного члена до старшего):" << endl;
		for (int i = 0; i <= degree; i++) {
			cout << "Коэффициент при x^" << i << ": ";
			cin >> coefficients[i];
		}

		normalize();
	}

	Polynomial(int deg, int* coeffs) : degree(deg) {
		coefficients = new int[degree + 1];
		for (int i = 0; i <= degree; i++) {
			coefficients[i] = coeffs[i];
		}
		normalize();
	}

	Polynomial(const Polynomial& other) {
		copy_coefficients(other);
	}

	~Polynomial() {
		delete[] coefficients;
	}

	bool can_add(const MathObject& other) const override {
		return dynamic_cast<const Polynomial*>(&other) != nullptr;
	}

	bool can_subtract(const MathObject& other) const override {
		return can_add(other);
	}

	bool can_multiply(const MathObject& other) const override {
		return can_add(other);
	}

	Polynomial* operator+(const MathObject& other) const override {
		const Polynomial* other_poly = dynamic_cast<const Polynomial*>(&other);
		if (!other_poly) return nullptr;

		int max_degree = (degree > other_poly->degree) ? degree : other_poly->degree;
		int* result_coeffs = new int[max_degree + 1]();

		for (int i = 0; i <= degree; i++) {
			result_coeffs[i] += coefficients[i];
		}

		for (int i = 0; i <= other_poly->degree; i++) {
			result_coeffs[i] += other_poly->coefficients[i];
		}

		Polynomial* result = new Polynomial(max_degree, result_coeffs);
		delete[] result_coeffs;
		return result;
	}

	Polynomial* operator-(const MathObject& other) const override {
		const Polynomial* other_poly = dynamic_cast<const Polynomial*>(&other);
		if (!other_poly) return nullptr;

		int max_degree = (degree > other_poly->degree) ? degree : other_poly->degree;
		int* result_coeffs = new int[max_degree + 1]();

		for (int i = 0; i <= degree; i++) {
			result_coeffs[i] += coefficients[i];
		}

		for (int i = 0; i <= other_poly->degree; i++) {
			result_coeffs[i] -= other_poly->coefficients[i];
		}

		Polynomial* result = new Polynomial(max_degree, result_coeffs);
		delete[] result_coeffs;
		return result;
	}

	Polynomial* operator*(const MathObject& other) const override {
		const Polynomial* other_poly = dynamic_cast<const Polynomial*>(&other);
		if (!other_poly) return nullptr;

		int result_degree = degree + other_poly->degree;
		int* result_coeffs = new int[result_degree + 1]();

		for (int i = 0; i <= degree; i++) {
			for (int j = 0; j <= other_poly->degree; j++) {
				result_coeffs[i + j] += coefficients[i] * other_poly->coefficients[j];
			}
		}

		Polynomial* result = new Polynomial(result_degree, result_coeffs);
		delete[] result_coeffs;
		return result;
	}

	Polynomial* operator*(int scalar) const override {
		if (scalar == 0) {
			int* zero_coeff = new int[1] {0};
			Polynomial* result = new Polynomial(0, zero_coeff);
			delete[] zero_coeff;
			return result;
		}

		int* result_coeffs = new int[degree + 1];
		for (int i = 0; i <= degree; i++) {
			result_coeffs[i] = coefficients[i] * scalar;
		}

		Polynomial* result = new Polynomial(degree, result_coeffs);
		delete[] result_coeffs;
		return result;
	}

	Polynomial* new_obj_return() const override {
		return new Polynomial();
	}

	void str_view() const override {
		cout << "\nПолином степени " << degree << ":" << endl;

		if (degree == 0 && coefficients[0] == 0) {
			cout << "0" << endl;
			return;
		}

		bool first_term = true;

		for (int i = degree; i >= 0; i--) {
			int coeff = coefficients[i];

			if (coeff == 0) continue;

			// Знак
			if (!first_term) {
				if (coeff > 0) cout << " + ";
				else {
					cout << " - ";
					coeff = -coeff;
				}
			}
			else if (coeff < 0) {
				cout << "-";
				coeff = -coeff;
			}

			// Коэффициент
			if (coeff != 1 || i == 0) {
				cout << coeff;
			}

			// Переменная
			if (i > 0) {
				cout << "x";
				if (i > 1) {
					cout << "^" << i;
				}
			}

			first_term = false;
		}
		cout << endl;
	}
};

class Vector : public MathObject {
private:
	double x, y;
	bool is_scalar_result; // Флаг, что это результат скалярного произведения
	bool is_2d; // Флаг, что это 2D вектор

public:
	string get_name() const override {
		if (is_scalar_result) {
			return "Скалярное произведение";
		}
		return "Вектор";
	}

	Vector() : is_scalar_result(false), is_2d(true) {
		cout << "\nСоздание вектора:" << endl;

		cout << "Введите координату x: ";
		cin >> x;

		cout << "Введите координату y: ";
		cin >> y;
	}

	// Конструктор для 2D вектора
	Vector(double x_val, double y_val)
		: x(x_val), y(y_val), is_scalar_result(false), is_2d(true) {}

	// Конструктор для 3D вектора (не используется в базовом случае)
	Vector(double x_val, double y_val, double z_val, bool is_3d = false)
		: x(x_val), y(y_val), is_scalar_result(false), is_2d(!is_3d) {}

	// Конструктор для результата скалярного произведения
	Vector(double scalar_result) : x(scalar_result), y(0), is_scalar_result(true), is_2d(true) {}

	bool can_add(const MathObject& other) const override {
		const Vector* other_vec = dynamic_cast<const Vector*>(&other);
		if (!other_vec) return false;
		// Можно складывать только обычные векторы, не результаты скалярных произведений
		return !is_scalar_result && !other_vec->is_scalar_result;
	}

	bool can_subtract(const MathObject& other) const override {
		return can_add(other);
	}

	bool can_multiply(const MathObject& other) const override {
		const Vector* other_vec = dynamic_cast<const Vector*>(&other);
		if (!other_vec) return false;
		// Можно умножать только обычные векторы
		return !is_scalar_result && !other_vec->is_scalar_result;
	}

	Vector* operator+(const MathObject& other) const override {
		const Vector* other_vec = dynamic_cast<const Vector*>(&other);
		if (!other_vec || !can_add(other)) return nullptr;

		return new Vector(x + other_vec->x, y + other_vec->y);
	}

	Vector* operator-(const MathObject& other) const override {
		const Vector* other_vec = dynamic_cast<const Vector*>(&other);
		if (!other_vec || !can_subtract(other)) return nullptr;

		return new Vector(x - other_vec->x, y - other_vec->y);
	}

	// Умножение векторов - с выбором типа произведения
	Vector* operator*(const MathObject& other) const override {
		const Vector* other_vec = dynamic_cast<const Vector*>(&other);
		if (!other_vec || !can_multiply(other)) return nullptr;

		// Для 2D векторов предлагаем только скалярное произведение
		// или псевдоскалярное произведение (аналог векторного для 2D)

		cout << "\nВыберите тип умножения векторов:" << endl;
		cout << "1. Скалярное произведение (результат - число)" << endl;

		if (is_2d) {
			cout << "2. Псевдоскалярное произведение (косое произведение) для 2D векторов" << endl;
			cout << "   (результат - число, равное ориентированной площади параллелограмма)" << endl;
		}

		int choice;
		do {
			cout << "Ваш выбор: ";
			cin >> choice;

			if (choice < 1 || choice > 2) {
				cout << "Неверный выбор. Попробуйте снова." << endl;
			}
		} while (choice < 1 || choice > 2);

		if (choice == 1) {
			// Скалярное произведение
			double dot_product = x * other_vec->x + y * other_vec->y;
			return new Vector(dot_product); // Используем конструктор для скалярного результата
		}
		else {
			// Псевдоскалярное (косое) произведение для 2D векторов
			// Равно ориентированной площади параллелограмма, натянутого на векторы
			double cross_product = x * other_vec->y - y * other_vec->x;

			// Проверка коллинеарности для 2D векторов
			// Векторы коллинеарны, если их псевдоскалярное произведение равно 0
			const double epsilon = 1e-10;
			if (fabs(cross_product) < epsilon) {
				cout << "\nВнимание: Векторы коллинеарны!" << endl;
				cout << "Псевдоскалярное произведение коллинеарных векторов равно 0." << endl;
			}

			// Возвращаем как скалярный результат
			return new Vector(cross_product);
		}
	}

	// Умножение вектора на скаляр
	Vector* operator*(int scalar) const override {
		if (is_scalar_result) {
			// Если это уже результат скалярного произведения, умножаем его на скаляр
			return new Vector(x * scalar);
		}
		return new Vector(x * scalar, y * scalar);
	}

	Vector* new_obj_return() const override {
		return new Vector();
	}

	void str_view() const override {
		if (is_scalar_result) {
			cout << "\nРезультат умножения векторов = " << x << endl;
			if (fabs(x) < 1e-10) {
				cout << "(Векторы коллинеарны)" << endl;
			}
		}
		else {
			cout << "\nВектор: (" << x << ", " << y << ")" << endl;
		}
	}

	// Дополнительные методы для работы с векторами
	double magnitude() const {
		return sqrt(x*x + y*y);
	}

	Vector* normalize() const {
		double mag = magnitude();
		if (mag == 0) {
			return new Vector(0, 0);
		}
		return new Vector(x / mag, y / mag);
	}

	// Метод для проверки коллинеарности 2D векторов
	bool are_collinear(const Vector* other) const {
		// Векторы коллинеарны, если их координаты пропорциональны
		// Или если их псевдоскалярное произведение равно 0

		// Проверяем нулевой вектор
		if ((x == 0 && y == 0) || (other->x == 0 && other->y == 0)) {
			return true;
		}

		// Проверяем пропорциональность
		const double epsilon = 1e-10;

		// Избегаем деления на 0
		if (fabs(other->x) > epsilon && fabs(other->y) > epsilon) {
			double ratio1 = x / other->x;
			double ratio2 = y / other->y;
			return fabs(ratio1 - ratio2) < epsilon;
		}
		else if (fabs(other->x) < epsilon && fabs(x) < epsilon) {
			// Оба x близки к 0 - векторы вертикальны
			return true;
		}
		else if (fabs(other->y) < epsilon && fabs(y) < epsilon) {
			// Оба y близки к 0 - векторы горизонтальны
			return true;
		}

		return false;
	}

	// Геттеры
	double get_x() const { return x; }
	double get_y() const { return y; }
	bool is_scalar() const { return is_scalar_result; }
	bool is_2d_vector() const { return is_2d; }
};

class Fraction : public MathObject {
private:
	int numerator;    // числитель
	int denominator;  // знаменатель

	// Сокращение дроби
	void simplify() {
		if (numerator == 0) {
			denominator = 1;
			return;
		}

		int a = abs(numerator);
		int b = abs(denominator);
		int gcd_val = gcd(a, b);

		numerator /= gcd_val;
		denominator /= gcd_val;

		// Знак храним в числителе
		if (denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}
	}

	// Наибольший общий делитель (алгоритм Евклида)
	int gcd(int a, int b) {
		while (b != 0) {
			int temp = b;
			b = a % b;
			a = temp;
		}
		return a;
	}

public:
	string get_name() const override {
		return "Дробь";
	}

	Fraction() {
		cout << "\nСоздание дроби:" << endl;

		cout << "Введите числитель: ";
		cin >> numerator;

		while (true) {
			cout << "Введите знаменатель (не равен 0): ";
			cin >> denominator;

			if (denominator != 0) {
				break;
			}
			cout << "Ошибка: знаменатель не может быть равен 0. Попробуйте снова." << endl;
		}

		simplify();
	}

	Fraction(int num, int den) : numerator(num), denominator(den) {
		if (denominator == 0) {
			throw invalid_argument("Знаменатель не может быть равен 0");
		}
		simplify();
	}

	// Проверка возможности операций
	bool can_add(const MathObject& other) const override {
		return dynamic_cast<const Fraction*>(&other) != nullptr;
	}

	bool can_subtract(const MathObject& other) const override {
		return can_add(other);
	}

	bool can_multiply(const MathObject& other) const override {
		const Fraction* other_frac = dynamic_cast<const Fraction*>(&other);
		if (other_frac) return true;

		// Дробь можно умножать на матрицу, полином и вектор через скалярное умножение
		return true;
	}

	bool can_multiply_scalar() const override {
		return true;
	}

	// Операции с другими дробями
	Fraction* operator+(const MathObject& other) const override {
		const Fraction* other_frac = dynamic_cast<const Fraction*>(&other);
		if (!other_frac) return nullptr;

		int new_num = numerator * other_frac->denominator +
			other_frac->numerator * denominator;
		int new_den = denominator * other_frac->denominator;

		return new Fraction(new_num, new_den);
	}

	Fraction* operator-(const MathObject& other) const override {
		const Fraction* other_frac = dynamic_cast<const Fraction*>(&other);
		if (!other_frac) return nullptr;

		int new_num = numerator * other_frac->denominator -
			other_frac->numerator * denominator;
		int new_den = denominator * other_frac->denominator;

		return new Fraction(new_num, new_den);
	}

	Fraction* operator*(const MathObject& other) const override {
		const Fraction* other_frac = dynamic_cast<const Fraction*>(&other);
		if (other_frac) {
			// Умножение дробей
			int new_num = numerator * other_frac->numerator;
			int new_den = denominator * other_frac->denominator;
			return new Fraction(new_num, new_den);
		}

		// Для других типов объектов - возвращаем nullptr
		// (в системе уже есть обработка умножения на скаляр через operator*(int))
		return nullptr;
	}

	// Умножение на скаляр (целое число)
	Fraction* operator*(int scalar) const override {
		return new Fraction(numerator * scalar, denominator);
	}

	Fraction* new_obj_return() const override {
		return new Fraction();
	}

	void str_view() const override {
		if (denominator == 1) {
			cout << "\nДробь: " << numerator << endl;
		}
		else if (numerator == 0) {
			cout << "\nДробь: 0" << endl;
		}
		else {
			cout << "\nДробь: " << numerator << "/" << denominator << endl;
		}
	}

};

class Complex : public MathObject {
private:
	double real;      // действительная часть
	double imag;      // мнимая часть

public:
	string get_name() const override {
		return "Комплексное число";
	}

	Complex() {
		cout << "\nСоздание комплексного числа:" << endl;

		cout << "Введите действительную часть: ";
		cin >> real;

		cout << "Введите мнимую часть: ";
		cin >> imag;
	}

	Complex(double re, double im) : real(re), imag(im) {}

	// Проверка возможности операций
	bool can_add(const MathObject& other) const override {
		const Complex* other_complex = dynamic_cast<const Complex*>(&other);
		if (other_complex) return true;

		// Комплексные числа можно складывать только с другими комплексными числами
		// и с дробями (если они реализованы как скаляры)
		return false;
	}

	bool can_subtract(const MathObject& other) const override {
		return can_add(other);
	}

	bool can_multiply(const MathObject& other) const override {
		const Complex* other_complex = dynamic_cast<const Complex*>(&other);
		if (other_complex) return true;

		// Комплексное число можно умножать на скаляр (целое число через operator*(int))
		return false;
	}

	// Операции с другими комплексными числами
	Complex* operator+(const MathObject& other) const override {
		const Complex* other_complex = dynamic_cast<const Complex*>(&other);
		if (!other_complex) return nullptr;

		return new Complex(real + other_complex->real,
			imag + other_complex->imag);
	}

	Complex* operator-(const MathObject& other) const override {
		const Complex* other_complex = dynamic_cast<const Complex*>(&other);
		if (!other_complex) return nullptr;

		return new Complex(real - other_complex->real,
			imag - other_complex->imag);
	}

	Complex* operator*(const MathObject& other) const override {
		const Complex* other_complex = dynamic_cast<const Complex*>(&other);
		if (!other_complex) return nullptr;

		// Формула умножения комплексных чисел:
		// (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
		double new_real = real * other_complex->real - imag * other_complex->imag;
		double new_imag = real * other_complex->imag + imag * other_complex->real;

		return new Complex(new_real, new_imag);
	}

	// Умножение на скаляр (целое число)
	Complex* operator*(int scalar) const override {
		return new Complex(real * scalar, imag * scalar);
	}

	Complex* new_obj_return() const override {
		return new Complex();
	}

	void str_view() const override {
		cout << "\nКомплексное число: ";

		if (real == 0 && imag == 0) {
			cout << "0" << endl;
		}
		else if (real == 0) {
			// Только мнимая часть
			if (imag == 1) {
				cout << "i" << endl;
			}
			else if (imag == -1) {
				cout << "-i" << endl;
			}
			else {
				cout << imag << "i" << endl;
			}
		}
		else if (imag == 0) {
			// Только действительная часть
			cout << real << endl;
		}
		else {
			// Обе части ненулевые
			cout << real;
			if (imag > 0) {
				cout << " + ";
				if (imag != 1) {
					cout << imag;
				}
				cout << "i";
			}
			else {
				cout << " - ";
				if (imag != -1) {
					cout << -imag;
				}
				cout << "i";
			}
			cout << endl;
		}
	}

	// Дополнительные методы для работы с комплексными числами
	Complex* conjugate() const {
		return new Complex(real, -imag);
	}

	double magnitude() const {
		return sqrt(real * real + imag * imag);
	}

	double phase() const {
		if (real == 0 && imag == 0) return 0;
		return atan2(imag, real);
	}

	double get_real() const { return real; }
	double get_imag() const { return imag; }
};

MathObject* initialization_object_first() {
	int choice;

	do {
		cout << "\nВыберите тип первого объекта:" << endl;
		cout << "1. Матрица" << endl;
		cout << "2. Полином" << endl;
		cout << "3. Вектор" << endl;
		cout << "4. Дробь" << endl;
		cout << "5. Комплексное число" << endl;  // Добавлено
		cout << "Ваш выбор: ";
		cin >> choice;

		if (choice == 1) {
			return new Matrix();
		}
		else if (choice == 2) {
			return new Polynomial();
		}
		else if (choice == 3) {
			return new Vector();
		}
		else if (choice == 4) {
			return new Fraction();
		}
		else if (choice == 5) {  // Добавлено
			return new Complex();
		}
		else {
			cout << "Неверный выбор. Попробуйте снова." << endl;
		}
	} while (true);
}

MathObject* initialization_object_second(MathObject* first_obj) {
	int choice;

	do {
		cout << "\nВыберите тип второго объекта:" << endl;
		cout << "1. " << first_obj->get_name() << endl;
		cout << "2. Целое число" << endl;

		cout << "Ваш выбор: ";
		cin >> choice;

		if (choice == 1) {
			return first_obj->new_obj_return();
		}
		else if (choice == 2) {
			return nullptr; // Индикатор числа
		}
		else {
			cout << "Неверный выбор. Попробуйте снова." << endl;
		}
	} while (true);
}

MathObject* perform_operation(MathObject* first_obj, MathObject* second_obj, int number) {
	if (second_obj == nullptr) {
		// Операция с числом
		cout << "\nДоступные операции:" << endl;
		cout << "1. Умножение на число" << endl;

		int choice;
		cout << "Ваш выбор: ";
		cin >> choice;

		if (choice == 1) {
			return (*first_obj) * number;
		}
		return nullptr;
	}

	// Операция с другим объектом
	cout << "\nДоступные операции:" << endl;

	bool has_operations = false;
	int option = 1;

	if (first_obj->can_add(*second_obj)) {
		cout << option << ". Сложение" << endl;
		has_operations = true;
		option++;
	}

	if (first_obj->can_subtract(*second_obj)) {
		cout << option << ". Вычитание" << endl;
		has_operations = true;
		option++;
	}

	if (first_obj->can_multiply(*second_obj)) {
		cout << option << ". Умножение" << endl;
		has_operations = true;
		option++;
	}

	if (!has_operations) {
		cout << "Нет доступных операций для данных объектов!" << endl;
		return nullptr;
	}

	int choice;
	cout << "Ваш выбор: ";
	cin >> choice;

	// Преобразуем выбор пользователя в соответствующую операцию
	int operation_count = 0;
	if (first_obj->can_add(*second_obj)) {
		operation_count++;
		if (operation_count == choice) {
			return (*first_obj) + (*second_obj);
		}
	}

	if (first_obj->can_subtract(*second_obj)) {
		operation_count++;
		if (operation_count == choice) {
			return (*first_obj) - (*second_obj);
		}
	}

	if (first_obj->can_multiply(*second_obj)) {
		operation_count++;
		if (operation_count == choice) {
			return (*first_obj) * (*second_obj);
		}
	}

	return nullptr;
}

void menu() {
	cout << "Добро пожаловать в консольное меню для выполнения математических операций с различными объектами!\n\n";

	while (true) {
		// Создаем первый объект
		MathObject* first_obj = initialization_object_first();
		cout << "\nПервый объект:" << endl;
		first_obj->str_view();

		// Создаем второй объект
		MathObject* second_obj = nullptr;
		int number = 0;

		while (true) {
			second_obj = initialization_object_second(first_obj);

			if (second_obj) {
				// Это объект
				cout << "\nВторой объект:" << endl;
				second_obj->str_view();

				// Проверяем доступные операции
				if (!first_obj->can_add(*second_obj) &&
					!first_obj->can_subtract(*second_obj) &&
					!first_obj->can_multiply(*second_obj)) {

					cout << "\nНет доступных операций для данных объектов!" << endl;
					cout << "Пожалуйста, введите другой второй объект." << endl;

					delete second_obj;
					second_obj = nullptr;
					continue;
				}
			}
			else {
				// Это число
				cout << "Введите целое число: ";
				cin >> number;
			}
			break;
		}

		// Выполняем операцию
		MathObject* result = nullptr;
		while (!result) {
			result = perform_operation(first_obj, second_obj, number);
			if (!result) {
				cout << "Неверный выбор операции. Попробуйте снова." << endl;
			}
		}

		// Выводим результат
		cout << "\nРезультат операции:" << endl;
		result->str_view();

		// Очистка памяти
		delete first_obj;
		if (second_obj) delete second_obj;
		delete result;

		// Повтор
		char again;
		cout << "\nХотите выполнить еще одну операцию? (y/n): ";
		cin >> again;
		if (again != 'y' && again != 'Y') {
			break;
		}
		cout << endl;
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	menu();
	return 0;
}
