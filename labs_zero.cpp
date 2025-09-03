#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>

using namespace std;

struct Student {
	string name;
	string surname;
	string fathername;
	string faculty;
	int course;
	int group;
	int avg_progress;

	void print_info_student() {
		cout << endl << "ФИО: " << surname << " " << name << " " << fathername << endl;
		cout << "Факультет: " << faculty << ". Курс: " << course << ". Группа: " << group + course * 10 << endl;
		cout << "Средняя успеваемость: " << avg_progress << endl << endl;
	}

};

Student create_student(){
	const size_t size_text = 10;

	string names[size_text] = {
		"Andrey",
		"Danil",
		"Vlad",
		"Roman",
		"Nikita",
		"Kirill",
		"Yra",
		"Jeniya",
		"Ilya",
		"Marat" };
	string lastnames[size_text] = {
		"Troshin",
		"Lobanov",
		"Kolchin",
		"Soldatov",
		"Vinogradov",
		"Jelonkin",
		"Safronov",
		"Usmankin",
		"Basharov",
		"Polyakov" };
	string fathernames[size_text] = {
		"Alekseevich",
		"Dmitrievich",
		"Ilych",
		"Petrovich",
		"Maksimovich",
		"Matveevich", 
		"Michalych", 
		"Renatovich", 
		"Romanovich", 
		"Valerevich" };
	string facultys[size_text] = {
		"MI", "FMF", "EEF", "ATI", "FFCSaT", 
		"IENaF", "PPF", "FIA", "HFF", "EF" };

	Student new_student = {
		names[rand() % 10],
		lastnames[rand() % 10],
		fathernames[rand() % 10],
		facultys[rand() % 10],
		1 + rand() % 5,
		1 + rand() % 3,
		rand() % 101
	};

	return new_student;
}

void filling_array(Student* s, size_t size) {
	for (int i = 0; i < size; i++) {
		s[i] = create_student();
	}
}

void print_array(Student* s, size_t size) {
	for (int i = 0; i < size; i++) {
		s[i].print_info_student();
	}
}

bool proper_facultet(string r_facultet){
	const size_t size_fac = 10;
	string facultys[size_fac] = {
		"MI", "FMF", "EEF", "ATI", "FFCSaT",
		"IENaF", "PPF", "FIA", "HFF", "EF" };

	for (int i = 0; i < size_fac; i++){
		if (r_facultet == facultys[i])
			return false;
	};

	return true;
}

string request_facultet(){
	string r_facultet;
	do {
		cout << "Введите существующий искомый факультет: ";
		cin >> r_facultet;
	} while (proper_facultet(r_facultet));

	cout << "Успешно!" << endl;
	return r_facultet;
}

int request_course(){
	int r_course;

	do {
		cout << "Введите искомый курс от 1 до 4: ";
		cin >> r_course;
	} while (r_course < 1 || r_course > 4);

	cout << "Успешно!" << endl;
	return r_course;
}

int request_group(int rec_course){
	int r_group;


}

int main(){
	setlocale(LC_ALL, "RU");
	srand(time(NULL));

	int MAXSIZE;
	do {
		cout << "Введите положительное целое число (кол-во студентов): ";
		cin >> MAXSIZE;

	} while (MAXSIZE <= 0);

	Student* students = new Student[MAXSIZE];
	filling_array(students, MAXSIZE);
	print_array(students, MAXSIZE);

	string rec_fac = request_facultet();
	int rec_course = request_course();
	int rec_group = request_group(rec_course);
	
	_getch();
	return 0;
}
