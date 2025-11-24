#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

class FileManager{
private:
    string path;
    string filename;

public:
    FileManager() {
        path = current_path().string() + "\\";
        filename = "example.txt";
    }

    FileManager(string p, string fn){
        set_path(p);
        set_filename(fn);
    }

    void set_path(string p){
        path = p;
    }

    void set_filename(string fn){
        filename = fn;
    }

    string fullname(){
        return path + filename;
    }

    void create_file(){
        ofstream file(fullname());
        if (file.is_open()) {
            cout << "Файл успешно создан!" << endl;
            file.close();
        }
        else 
            cout << "Ошибка при создании файла!" << endl;
    }

    void read_to_print_file(){
        ifstream file(fullname());
        if (file.is_open()){
            cout << "Файл успешно открыт для чтения!" << endl;
            cout << "\n=== Содержимое файла " << filename << " ===" << endl;
            string line;
            while (getline(file, line)){
                cout << line << endl;
            }
            file.close();
            cout << "=== Конец файла ===\n" << endl;
        }
        else
            cout << "Ошибка открытия файла для чтения!" << endl;
    }

    void update_to_end_file(string data){
        ofstream file(fullname(), ios::app);
        if (file.is_open()){
            cout << "Файл успешно открыт для добавления данных в конец!" << endl;
            file << data << endl;
            file.close();
        }
        else
            cout << "Ошибка открытия файла для добавления данных!" << endl;
    }

    void clear_file(){
        ofstream file(fullname());
        if (file.is_open()) {
            cout << "Файл успешно очищен!" << endl;
            file.close();
        }
        else
            cout << "Ошибка при очистке файла!" << endl;
    }
};

void interface(FileManager object){
    int choice;
    do {
        cout << "1. Создать файл\n2. Добавить данные в файл\n3. Чтение файла\n4. Очистить файл\n5. Изменить путь файла\n6. Изменить имя файла\n7. Выйти из интерфейса" << endl;
        cout << "Выберите одно из действий: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
            object.create_file();
        else if (choice == 2){
            string input_data;
            cout << "Введите данные для добавления: ";
            getline(cin, input_data);
            object.update_to_end_file(input_data);
        }
        else if (choice == 3)
            object.read_to_print_file();
        else if (choice == 4)
            object.clear_file();
        else if (choice == 5){
            string new_path;
            cout << "Введите новый путь до файла: ";
            getline(cin, new_path);
            object.set_path(new_path);
        }
        else if (choice == 6){
            string new_filename;
            cout << "Введите новое имя файла: ";
            getline(cin, new_filename);
            object.set_filename(new_filename);
        }
        else if (choice == 7)
            break;
        else
            cout << "Неверный выбор!" << endl;
        cout << endl;
    } while (true);
}

int main(){
    setlocale(LC_ALL, "RU");

    int choice;
    cout << "=== Выбор режима инициализации ===" << endl;
    cout << "1. Ввести путь и имя файла вручную" << endl;
    cout << "2. Использовать настройки по умолчанию" << endl;
    cout << "Выберите режим: ";
    cin >> choice;
    cin.ignore();

    FileManager obj;

    if (choice == 1) {
        string input_path;
        cout << "Введите путь до файла: ";
        getline(cin, input_path);
            
        string input_filename;
        cout << "Введите имя файла: ";
        getline(cin, input_filename);

        obj = FileManager(input_path, input_filename);
    } else {
        cout << "Используются настройки по умолчанию:" << endl;
        cout << "Путь: " << obj.get_path() << endl;
        cout << "Имя файла: " << obj.get_filename() << endl;
    }

    interface(obj);
    
    return 0;
}
