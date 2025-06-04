#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

template <typename diff>
void my_print(string text, diff &variable) {
	cout << text;
	cin >> variable;
}

void processing_fullname(string &file_name) {
	while (file_name.find('"') != string::npos)
		file_name.erase(file_name.find('"'), 1);
}

bool check_bracket(string row) {
	int balance = 0;
	for (int i = 0; i < row.length(); i++) {
		if (row[i] == '(')
			balance++;
		else if (row[i] == ')') {
			balance--;
			if (balance < 0)
				return false;
		}
	}
	return balance == 0;
}

void check_open(ifstream &file) {
	if (!file.is_open()) {
		cout << "�� ������� ������� ����!" << endl;
		exit(EXIT_FAILURE);
	}
	cout << "���� ������!" << endl;
}

void check_open(ofstream& file) {
	if (!file.is_open()) {
		cout << "�� ������� ������� ����!" << endl;
		exit(EXIT_FAILURE);
	}
	cout << "���� ������!" << endl;
}

void record_result(ifstream &file_read, ofstream &file_write) {
	string str;
	int id_row = 1;

	while (!file_read.eof()) {
		getline(file_read, str);
		if (str.find(')') != string::npos || str.find('(') != string::npos) {
			if (check_bracket(str))
				file_write << id_row << ". True" << endl;
			else
				file_write << id_row << ". False" << endl;
		}
		else
			file_write << id_row << ". � ������ ��� ��������!" << endl;

		id_row++;
	}
}

int main() {
	setlocale(LC_ALL, "RU");

	// ����������� ��� ����� �� �������� ����� ������ ������.

	string fullname;
	my_print("������� ������ ��� ����� ��� ������: ", fullname);
	processing_fullname(fullname);

	ifstream file_read;
	file_read.open(fullname);

	check_open(file_read);

	// ����������� ��� ����� � ������� ����� ���������� ��������� ������.

	string fullname_write;
	my_print("������� ��� ����� ��� ������: ", fullname_write);
	processing_fullname(fullname_write);

	ofstream file_write;
	file_write.open(fullname_write + ".txt");

	check_open(file_write);

	// ������ ��������� � ��������� ���������

	record_result(file_read, file_write);

	file_read.close();
	file_write.close();

	return 0;
}

