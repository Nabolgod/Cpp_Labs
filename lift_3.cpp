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

class Elevator {
protected:
	static unsigned int global_id;

	unsigned int id;
	int current_floor;
	bool is_move = false;

public:
	Elevator() {
		id = global_id++;
		current_floor = 1;
	}

	Elevator(int cur_f) {
		id = global_id++;
		current_floor = cur_f;
	}

	void print_state() {
		if (is_move)
			cout << "Лифт находится в движении!" << endl;
		else
			cout << "Лифт стоит на месте!" << endl;
	}

	void move(int target_floor) {
		int diff_floor = abs(target_floor - current_floor);
		cout << "Лифт №" << id << " переместился с " << current_floor
			<< " на " << target_floor << " этаж (пройдено " << diff_floor << ")" << endl;
		current_floor = target_floor;
	}

	virtual void print_info() {
		cout << left << setw(10) << id;
		cout << left << setw(15) << current_floor;
	};
};

class ElevatorPassenger : public Elevator {
private:
	int count_passenger;

public:
	ElevatorPassenger(): Elevator() {
		count_passenger = (rand()% 10) + 1;
	}

	ElevatorPassenger(int cur_f) : Elevator(cur_f) {
		count_passenger = (rand() % 10) + 1;
	}

	void print_info() override {
		cout << left << setw(15) << "Пассажирский";
		Elevator::print_info();
		cout << left << setw(10) << (to_string(count_passenger) + " чел.");
		cout << endl;
	}
};

class ElevatorFreight : public Elevator {
private:
	int capacity;

public:
	ElevatorFreight() : Elevator() {
		capacity = (rand() % 400) + 100;
	}

	ElevatorFreight(int cur_f) : Elevator(cur_f) {
		capacity = (rand() % 400) + 100;
	}

	void print_info() override {
		cout << left << setw(15) << "Грузовой";
		Elevator::print_info();
		cout << left << setw(10) << (to_string(capacity) + " кг.");
		cout << endl;
	}
};

unsigned int Elevator::global_id = 0;

class Building {
private:
	int min_floor;
	int max_floor;
	int elevators_count;
	Elevator** elevators = nullptr;

	void create_elevators() {
		elevators = new Elevator*[elevators_count];
		for (int i = 0; i < elevators_count; i++) {
			if (i % 2 == 0)
				elevators[i] = new ElevatorPassenger(min_floor);
			else
				elevators[i] = new ElevatorFreight(min_floor);
		}
	}

public:
	Building() {
		min_floor = 1;
		max_floor = 10;
		elevators_count = 5;
		create_elevators();
	}

	Building(int min_f, int max_f, int elev_count) {
		min_floor = min_f;
		max_floor = max_f;
		elevators_count = elev_count;
		create_elevators();
	}

	void print_info() {
		cout << endl <<"Информация здания: " << endl;
		cout << "Минимальный этаж: " << min_floor << endl;
		cout << "Максимальный этаж: " << max_floor << endl;
		cout << "Количество лифтов: " << elevators_count << endl << endl;
		print_info_el();
	}

	void print_info_el() {
		cout << left << setw(15) << "Тип лифта";
		cout << left << setw(10) << "ID-лифта";
		cout << left << setw(15) << "Текущий этаж";
		cout << left << setw(10) << "Грузоподъёмность";
		cout << endl << endl;

		for (int i = 0; i < elevators_count; i++) {
			elevators[i]->print_info();
		}
	}

	Elevator* get_elevator(unsigned int id) {
		return elevators[id];
	}
};

void user_interface() {
	int minf, maxf;
	int count_el = 5;

	my_input(minf, "Введите минимальный этаж здания (положительное целое число): ");
	do {
		my_input(maxf, "Введите максимальный этаж здания (положительное целое число): ");
	} while (maxf <= minf);

	Building main_house = Building(minf, maxf, count_el);
	main_house.print_info();

	int choice_elev;
	bool flag_end = false;

	do {
		my_input(choice_elev, "Укажите ID-лифта: ");

		if (choice_elev >= count_el || choice_elev < 0)
			continue;

		int action;
		cout << endl << "1. Вызвать лифт на этаж." << endl;
		cout << "2. Статус лифта." << endl;
		cout << "3. Вывести информацию по лифтам." << endl;
		cout << "4. Выбрать другой лифт." << endl;
		cout << "5. Закончить сеанс." << endl;

		do {
			do {
				my_input(action, "Выберите действие: ");
			} while (action < 1 || action > 5);

			switch (action) {
			case 1:
				int target_floor;
				do {
					my_input(target_floor, "Укажите этаж назначения: ");
				} while (target_floor < minf || target_floor > maxf);

				main_house.get_elevator(choice_elev)->move(target_floor);
				break;
			case 2:
				main_house.get_elevator(choice_elev)->print_state();
				break;
			case 3:
				main_house.print_info_el();
				break;
			case 4:
				break;
			case 5:
				flag_end = true;
				break;
			}
		} while (action < 4);

	} while (!flag_end);
}

int main() {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	
	user_interface();
	
	return 0;
}
