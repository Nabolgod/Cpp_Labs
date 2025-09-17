#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

const double PI = 3.14;

class Ellipse {
private:
	static unsigned int global_id;
	unsigned int id; // чтобы не было отрицательных значений
	double a, b;

	void set_a(double aa) {
		a = aa;
	}

	void set_b(double bb) {
		b = bb;
	}

	void set_id(int id_num) {
		id = id_num;
	}

public:
	Ellipse(){
		set_id(global_id++);
		a = 1;
		b = 1;
	}

	Ellipse(double a, double b) {
		set_id(global_id++);
		set_a(a);
		set_b(b);
	}

	double get_a() {
		return a;
	}

	double get_b() {
		return b;
	}

	void print_info() {
		cout << left << setw(10) << id;
		cout << left << setw(15) << a;
		cout << left << setw(15) << b;
		cout << left << setw(15) << get_area();
		cout << left << setw(15) << get_perimeter();
		cout << endl;
	}

	double get_area() {
		return PI * a * b;
	}

	double get_perimeter() {
		return PI * (a + b);
	}

	unsigned int get_id() {
		return id;
	}

};

unsigned int Ellipse::global_id = 0;

Ellipse create_el() {
	double a, b;
	do {
		cout << "Введите значение оси a (положительное): ";
		cin >> a;

	} while (a <= 0);

	do {
		cout << "Введите значение оси b (положительное): ";
		cin >> b;

	} while (b <= 0);

	return Ellipse(a, b);
}

void print_array(Ellipse* array, int size_array) {
	cout << left << setw(10) << "id";
	cout << left << setw(15) << "Значение a";
	cout << left << setw(15) << "Значение b";
	cout << left << setw(15) << "Площадь";
	cout << left << setw(15) << "Периметр";
	cout << endl << endl;

	for (int i = 0; i < size_array; i++) {
		array[i].print_info();
	}
	cout << endl;
}

void fill_array(Ellipse* array, int size_array) {
	for (int i = 0; i < size_array; i++) {
		cout << "Введите данные для " << i + 1 << " объекта" << endl;
		array[i] = create_el();
		cout << endl;
	}
}

double max_area(Ellipse* array, int size_array) {
	double max_value = 0;
	for (int i = 0; i < size_array; i++) {
		double value = array[i].get_area();
		if (value > max_value) {
			max_value = value;
		}
		
	}

	return max_value;
}

double max_perimeter(Ellipse* array, int size_array) {
	double max_value = 0;
	for (int i = 0; i < size_array; i++) {
		double value = array[i].get_perimeter();
		if (value > max_value) {
			max_value = value;
		}

	}

	return max_value;
}

void print_max_main(Ellipse* array, int size_array) {
	int count_area = 0;
	int count_perimeter = 0;

	double max_val_area = max_area(array, size_array);
	unsigned int max_id_area;
	double max_val_perimeter = max_perimeter(array, size_array);
	unsigned int max_id_perimeter;

	for (int i = 0; i < size_array; i++) {
		if (max_val_area <= array[i].get_area()) {
			count_area++;
			max_id_area = array[i].get_id();
		}
		if (max_val_perimeter <= array[i].get_perimeter()) {
			count_perimeter++;
			max_id_perimeter = array[i].get_id();
		}
	}

	if (count_area > 1) {
		cout << "Эллписа с наибольшой площадью не найдено." << endl;
	}
	else {
		cout << "ID эллписа с наибольшей площадью: " << max_id_area << endl;
	}

	if (count_perimeter > 1) {
		cout << "Эллписа с наибольшим периметром не найдено." << endl;
	}
	else {
		cout << "ID эллписа с наибольшим периметром: " << max_id_perimeter << endl;
	}

}

int main() {
	setlocale(LC_ALL, "RU");

	int count_obj_el;

	do {
		cout << "Введите количество эллипсов (положительное целое число): ";
		cin >> count_obj_el;
	} while (count_obj_el <= 0);

	Ellipse* array_el = new Ellipse[count_obj_el];

	fill_array(array_el, count_obj_el);
	print_array(array_el, count_obj_el);
	print_max_main(array_el, count_obj_el);

	delete[] array_el;
	array_el = nullptr;
	return 0;
}
