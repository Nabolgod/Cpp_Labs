#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <stdexcept>

using namespace std;

const double PI = 3.141592653589793;

double round_to_precision(double value, int precision = 6) {
	double factor = pow(10.0, precision);
	return round(value * factor) / factor;
}

// Базовый класс фигуры
class Shape {
public:
	virtual ~Shape() = default;

	// Основные операции
	virtual string get_name() const = 0;
	virtual void move(double dx, double dy) = 0;
	virtual void rotate(double angle) = 0; // угол в градусах
	virtual double get_area() const = 0;
	virtual double get_perimeter() const = 0;

	// Рисование (упрощённое - вывод координат вершин)
	virtual void draw() const = 0;
};

// Базовый класс для многоугольников
class Polygon : public Shape {
protected:
	struct Point {
		double x, y;
		Point(double x = 0, double y = 0) : x(x), y(y) {}
	};

	vector<Point> vertices;
	Point center; // центр фигуры для вращения

	// Вычисление центра тяжести
	void calculate_center() {
		double sum_x = 0, sum_y = 0;
		for (const auto& p : vertices) {
			sum_x += p.x;
			sum_y += p.y;
		}
		center.x = sum_x / vertices.size();
		center.y = sum_y / vertices.size();
	}

	// Расстояние между двумя точками
	double distance(const Point& p1, const Point& p2) const {
		return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
	}

public:
	virtual ~Polygon() = default;

	void move(double dx, double dy) override {
		for (auto& p : vertices) {
			p.x += dx;
			p.y += dy;
		}
		center.x += dx;
		center.y += dy;
	}

	void rotate(double angle) override {
		// Преобразуем угол в радианы
		double rad = angle * PI / 180.0;
		double cos_a = cos(rad);
		double sin_a = sin(rad);

		// Поворачиваем каждую вершину относительно центра
		for (auto& p : vertices) {
			double dx = p.x - center.x;
			double dy = p.y - center.y;

			p.x = center.x + dx * cos_a - dy * sin_a;
			p.y = center.y + dx * sin_a + dy * cos_a;
		}
	}

	double get_perimeter() const override {
		double perimeter = 0;
		size_t n = vertices.size();

		for (size_t i = 0; i < n; i++) {
			size_t next = (i + 1) % n;
			perimeter += distance(vertices[i], vertices[next]);
		}

		return perimeter;
	}

	// Формула площади Гаусса (шнуровки)
	double get_area() const override {
		double area = 0;
		size_t n = vertices.size();

		for (size_t i = 0; i < n; i++) {
			size_t next = (i + 1) % n;
			area += vertices[i].x * vertices[next].y;
			area -= vertices[i].y * vertices[next].x;
		}

		return fabs(area) / 2.0;
	}

	void draw() const override {
		cout << "\nКоординаты вершин:" << endl;
		for (size_t i = 0; i < vertices.size(); i++) {
			cout << "Вершина " << i + 1 << ": ("
				<< vertices[i].x << ", " << vertices[i].y << ")" << endl;
		}
		cout << "Центр: (" << center.x << ", " << center.y << ")" << endl;
	}
};

// Класс Треугольник
class Triangle : public Polygon {
private:
	void initialize_triangle() {
		vertices.resize(3);
		calculate_center();
	}

public:
	Triangle() {
		cout << "\nСоздание треугольника:" << endl;
		cout << "Введите координаты трех вершин:" << endl;

		for (int i = 0; i < 3; i++) {
			cout << "Вершина " << i + 1 << " (x y): ";
			double x, y;
			cin >> x >> y;
			vertices.push_back(Point(x, y));
		}

		// Проверка, что точки не лежат на одной прямой
		if (get_area() < 1e-10) {
			throw invalid_argument("Точки лежат на одной прямой - это не треугольник!");
		}

		initialize_triangle();
	}

	Triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
		vertices.push_back(Point(x1, y1));
		vertices.push_back(Point(x2, y2));
		vertices.push_back(Point(x3, y3));

		if (get_area() < 1e-10) {
			throw invalid_argument("Точки лежат на одной прямой - это не треугольник!");
		}

		initialize_triangle();
	}

	string get_name() const override {
		return "Треугольник";
	}

};

// Класс Прямоугольник
class Rectangle : public Polygon {
private:
	double width, height;

	void initialize_rectangle(double x, double y, double w, double h) {
		vertices.clear();
		vertices.push_back(Point(x, y));
		vertices.push_back(Point(x + w, y));
		vertices.push_back(Point(x + w, y + h));
		vertices.push_back(Point(x, y + h));

		calculate_center();
		width = w;
		height = h;
	}

public:
	Rectangle() {
		cout << "\nСоздание прямоугольника:" << endl;

		double x, y, w, h;
		cout << "Введите координаты левого нижнего угла (x y): ";
		cin >> x >> y;

		do {
			cout << "Введите ширину: ";
			cin >> w;
			cout << "Введите высоту: ";
			cin >> h;

			if (w <= 0 || h <= 0) {
				cout << "Ошибка: ширина и высота должны быть положительными!" << endl;
			}
		} while (w <= 0 || h <= 0);

		initialize_rectangle(x, y, w, h);
	}

	Rectangle(double x, double y, double w, double h) {
		if (w <= 0 || h <= 0) {
			throw invalid_argument("Ширина и высота должны быть положительными!");
		}
		initialize_rectangle(x, y, w, h);
	}

	string get_name() const override {
		return "Прямоугольник";
	}

	double get_area() const override {
		return width * height;
	}

};

// Класс Ромб
class Rhombus : public Polygon {
private:
	double diagonal1, diagonal2;

	void initialize_rhombus(double center_x, double center_y, double d1, double d2) {
		vertices.clear();
		vertices.push_back(Point(center_x, center_y + d2 / 2));
		vertices.push_back(Point(center_x + d1 / 2, center_y));
		vertices.push_back(Point(center_x, center_y - d2 / 2));
		vertices.push_back(Point(center_x - d1 / 2, center_y));

		center.x = center_x;
		center.y = center_y;
		diagonal1 = d1;
		diagonal2 = d2;
	}

public:
	Rhombus() {
		cout << "\nСоздание ромба:" << endl;

		double cx, cy, d1, d2;
		cout << "Введите координаты центра (x y): ";
		cin >> cx >> cy;

		do {
			cout << "Введите длину первой диагонали: ";
			cin >> d1;
			cout << "Введите длину второй диагонали: ";
			cin >> d2;

			if (d1 <= 0 || d2 <= 0) {
				cout << "Ошибка: диагонали должны быть положительными!" << endl;
			}
		} while (d1 <= 0 || d2 <= 0);

		initialize_rhombus(cx, cy, d1, d2);
	}

	Rhombus(double center_x, double center_y, double d1, double d2) {
		if (d1 <= 0 || d2 <= 0) {
			throw invalid_argument("Диагонали должны быть положительными!");
		}
		initialize_rhombus(center_x, center_y, d1, d2);
	}

	string get_name() const override {
		return "Ромб";
	}

	double get_area() const override {
		return diagonal1 * diagonal2 / 2;
	}
};

// Класс Эллипс
class Ellipse : public Shape {
private:
	double center_x, center_y;
	double semi_major; // большая полуось
	double semi_minor; // малая полуось
	double rotation_angle; // угол поворота в градусах

public:
	Ellipse() {
		cout << "\nСоздание эллипса:" << endl;

		cout << "Введите координаты центра (x y): ";
		cin >> center_x >> center_y;

		do {
			cout << "Введите длину большой полуоси: ";
			cin >> semi_major;
			cout << "Введите длину малой полуоси: ";
			cin >> semi_minor;

			if (semi_major <= 0 || semi_minor <= 0) {
				cout << "Ошибка: полуоси должны быть положительными!" << endl;
			}
			else if (semi_major < semi_minor) {
				cout << "Ошибка: большая полуось должна быть больше или равна малой!" << endl;
			}
		} while (semi_major <= 0 || semi_minor <= 0 || semi_major < semi_minor);

		rotation_angle = 0;
	}

	Ellipse(double cx, double cy, double a, double b)
		: center_x(cx), center_y(cy), semi_major(a), semi_minor(b), rotation_angle(0) {
		if (a <= 0 || b <= 0) {
			throw invalid_argument("Полуоси должны быть положительными!");
		}
		if (a < b) {
			throw invalid_argument("Большая полуось должна быть больше или равна малой!");
		}
	}

	string get_name() const override {
		return "Эллипс";
	}

	void move(double dx, double dy) override {
		center_x += dx;
		center_y += dy;
	}

	void rotate(double angle) override {
		rotation_angle += angle;
		if (rotation_angle >= 360) rotation_angle -= 360;
		if (rotation_angle < 0) rotation_angle += 360;
	}

	double get_area() const override {
		return PI * semi_major * semi_minor;
	}

	double get_perimeter() const override {
		// Приближенная формула Рамануджана для периметра эллипса
		double h = pow((semi_major - semi_minor) / (semi_major + semi_minor), 2);
		return PI * (semi_major + semi_minor) * (1 + 3 * h / (10 + sqrt(4 - 3 * h)));
	}

	void draw() const override {
		cout << "\nЭллипс:" << endl;
		cout << "Центр: (" << center_x << ", " << center_y << ")" << endl;
		cout << "Большая полуось: " << semi_major << endl;
		cout << "Малая полуось: " << semi_minor << endl;
		cout << "Угол поворота: " << rotation_angle << " градусов" << endl;

		// Выводим несколько точек на эллипсе для визуализации
		cout << "Точки на эллипсе (при 0° поворота):" << endl;
		double angles[] = { 0, 45, 90, 135, 180, 225, 270, 315 };
		for (double a : angles) {
			double rad = a * PI / 180.0;
			double x = center_x + semi_major * cos(rad);
			double y = center_y + semi_minor * sin(rad);
			cout << "Угол " << a << "°: (" << x << ", " << y << ")" << endl;
		}
	}

};

// Класс Трапеция
class Trapezoid : public Polygon {
private:
	double base1, base2, height;

	void initialize_trapezoid(double x, double y, double b1, double b2, double h) {
		vertices.clear();
		vertices.push_back(Point(x, y));
		vertices.push_back(Point(x + b1, y));
		vertices.push_back(Point(x + b2 + (b1 - b2) / 2, y + h));
		vertices.push_back(Point(x + (b1 - b2) / 2, y + h));

		calculate_center();
		base1 = b1;
		base2 = b2;
		height = h;
	}

public:
	Trapezoid() {
		cout << "\nСоздание трапеции:" << endl;

		double x, y, b1, b2, h;
		cout << "Введите координаты левого нижнего угла (x y): ";
		cin >> x >> y;

		do {
			cout << "Введите длину нижнего основания: ";
			cin >> b1;
			cout << "Введите длину верхнего основания: ";
			cin >> b2;
			cout << "Введите высоту: ";
			cin >> h;

			if (b1 <= 0 || b2 <= 0 || h <= 0) {
				cout << "Ошибка: все параметры должны быть положительными!" << endl;
			}
		} while (b1 <= 0 || b2 <= 0 || h <= 0);

		initialize_trapezoid(x, y, b1, b2, h);
	}

	Trapezoid(double x, double y, double b1, double b2, double h) {
		if (b1 <= 0 || b2 <= 0 || h <= 0) {
			throw invalid_argument("Все параметры должны быть положительными!");
		}
		initialize_trapezoid(x, y, b1, b2, h);
	}

	string get_name() const override {
		return "Трапеция";
	}

	double get_area() const override {
		return (base1 + base2) * height / 2;
	}

};

// Функции меню по аналогии с MathObject проектом
Shape* create_shape() {
	int choice;

	do {
		cout << "\n=== СОЗДАНИЕ ФИГУРЫ ===" << endl;
		cout << "Выберите тип фигуры:" << endl;
		cout << "1. Треугольник" << endl;
		cout << "2. Прямоугольник" << endl;
		cout << "3. Ромб" << endl;
		cout << "4. Эллипс" << endl;
		cout << "5. Трапеция" << endl;
		cout << "0. Выход" << endl;
		cout << "Ваш выбор: ";
		cin >> choice;

		try {
			switch (choice) {
			case 1: return new Triangle();
			case 2: return new Rectangle();
			case 3: return new Rhombus();
			case 4: return new Ellipse();
			case 5: return new Trapezoid();
			case 0: return nullptr;
			default:
				cout << "Неверный выбор. Попробуйте снова." << endl;
			}
		}
		catch (const invalid_argument& e) {
			cout << "Ошибка: " << e.what() << endl;
			cout << "Попробуйте снова." << endl;
		}
	} while (true);
}

void perform_operations(Shape* shape) {
	if (!shape) return;

	int choice;

	do {
		cout << "\n=== ОПЕРАЦИИ С ФИГУРОЙ ===" << endl;
		cout << "Фигура: " << shape->get_name() << endl;
		cout << "Выберите операцию:" << endl;
		cout << "1. Перемещение" << endl;
		cout << "2. Поворот" << endl;
		cout << "3. Показать площадь" << endl;
		cout << "4. Показать периметр" << endl;
		cout << "5. Нарисовать фигуру" << endl;
		cout << "6. Создать фигуру того же типа" << endl;
		cout << "0. Назад в меню" << endl;
		cout << "Ваш выбор: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			double dx, dy;
			cout << "Введите смещение по x: ";
			cin >> dx;
			cout << "Введите смещение по y: ";
			cin >> dy;
			shape->move(dx, dy);
			cout << "Фигура перемещена." << endl;
			break;
		}
		case 2: {
			double angle;
			cout << "Введите угол поворота в градусах: ";
			cin >> angle;
			shape->rotate(angle);
			cout << "Фигура повернута на " << angle << " градусов." << endl;
			break;
		}
		case 3:
			cout << "Площадь фигуры: " << shape->get_area() << endl;
			break;
		case 4:
			cout << "Периметр фигуры: " << shape->get_perimeter() << endl;
			break;
		case 5:
			shape->draw();
			break;
		case 0:
			return;
		default:
			cout << "Неверный выбор. Попробуйте снова." << endl;
		}
	} while (true);
}

void main_menu() {
	cout << "=== ГЕОМЕТРИЧЕСКИЕ ФИГУРЫ НА ПЛОСКОСТИ ===" << endl;
	cout << "Программа для работы с геометрическими фигурами" << endl;

	while (true) {
		Shape* shape = create_shape();
		if (!shape) break;

		perform_operations(shape);

		delete shape;

		char choice;
		cout << "\nХотите продолжить работу с другими фигурами? (y/n): ";
		cin >> choice;
		if (choice != 'y' && choice != 'Y') {
			break;
		}
	}

	cout << "\nПрограмма завершена. До свидания!" << endl;
}

int main() {
	setlocale(LC_ALL, "RU");

	try {
		main_menu();
	}
	catch (const exception& e) {
		cerr << "Произошла ошибка: " << e.what() << endl;
		return 1;
	}

	return 0;
}
