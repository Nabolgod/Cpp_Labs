#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

enum WEEKDAY {
    Monday,
    Tuesday,
    Wednesday,
    Friday,
    Saturday,
    Sunday,

    length
};

struct Employee {
    size_t id_record;
    const char* name;
    const char* lastname;
    const char* fathername;
    size_t number_of_products;
    WEEKDAY working_day;

    void print_employee() {
        static const char* day_names[] = {
            "Понедельник", "Вторник", "Среда",
            "Четверг", "Пятница", "Суббота", "Воскресенье"
        };

        cout << "ID работника -> " << id_record << endl;
        cout << "ФИО рабочего: " << lastname << " " << name << " " << fathername << endl;
        cout << "День недели: " << day_names[working_day] << " (" << working_day << ") " << endl;
        cout << "Количество собранных изделий: " << number_of_products << endl;
    }
};

Employee create_employee() { // создать случайного сотрудника
    static const char* names[] = { // статичный массив случ. имен (иниц. один раз)
       "Andrey", "Danil", "Vlad", "Roman", "Nikita",
       "Kirill", "Yra", "Jeniya", "Ilya", "Marat"
    };

    static const char* lastnames[] = { // статичный массив случ. фамилий
        "Troshin", "Lobanov","Kolchin", "Soldatov","Vinogradov",
        "Jelonkin","Safronov", "Usmankin","Basharov", "Polyakov"
    };

    static const char* fathernames[] = { // статичный массив случ. отчеств
        "Alekseevich", "Dmitrievich","Ilych", "Petrovich","Maksimovich",
        "Matveevich","Michalych", "Renatovich","Romanovich", "Valerevich"
    };

    static size_t id_current = 0;

    Employee new_empl = {
        id_current++,                       // ID
        names[rand() % 10],                 // Name
        lastnames[rand() % 10],             // Lastname
        fathernames[rand() % 10],           // Fathername
        rand() % 100,                       // Number of production
        WEEKDAY(rand() % WEEKDAY::length),  // WEEK DAY
    };

    return new_empl;
}

//
// Работа с массивом
//

Employee* array_init(size_t size) {
    if (size <= 0) return nullptr;

    Employee* array = new Employee[size];

    for (size_t i = 0; i < size; ++i)
        array[i] = create_employee();

    return array;
}

void array_print(Employee* arr, size_t sz) {
    for (size_t i = 0; i < sz; ++i) {
        cout << "[ " << i << " ]" << endl;
        arr[i].print_employee();
        cout << endl;
    }
}

Employee* array_delete_at_index(Employee* array, size_t& size, size_t index) { // возвращает новый массив с удаленными элементами
    if (index >= size) {
        cout << "Ошибка: индекс вне диапазона" << endl;
        return array;
    }

    Employee* newArray = new Employee[size - 1];

    for (size_t i = 0, j = 0; i < size; ++i) {
        if (i != index) {
            newArray[j++] = array[i];
        }
    }

    delete[] array; // сносим старый массив
    --size; // уменьшаем размер, переменная передается по ссылке
    return newArray; // возвращаем новый
}

void array_clear(Employee* array) {
    delete[] array;
    array = nullptr;
}

Employee* array_find_by_lastname(Employee* arr, size_t size, const char* lastname, size_t& out_size) {
    out_size = 0;

    // Сначала считаем, сколько совпадений
    for (size_t i = 0; i < size; ++i) {
        if (strcmp(arr[i].lastname, lastname) == 0) {
            ++out_size;
        }
    }

    if (out_size == 0)
        return nullptr;

    // Выделим массив под найденные записи
    Employee* results = new Employee[out_size];
    size_t j = 0;

    for (size_t i = 0; i < size; ++i) {
        if (strcmp(arr[i].lastname, lastname) == 0) {
            results[j++] = arr[i];
        }
    }

    return results;
}

void array_sort(Employee* array, size_t size) {
    if (!array || size < 2) return;

    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = 0; j < size - 1 - i; ++j) {
            if (array[j].number_of_products > array[j + 1].number_of_products) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}


//
// Работа с файлами
//

void write_to_binary(const char* filename, Employee* array, size_t sz) {
    ofstream out(filename, ios::binary);
    if (!out.is_open()) {
        cout << "Ошибка при открытии файла для записи" << endl;
        return;
    }

    out.write(reinterpret_cast<char*>(&sz), sizeof(sz)); // сохраняем размер
    out.write(reinterpret_cast<char*>(array), sizeof(Employee) * sz);

    out.close();
}

Employee* read_from_binary(const char* filename, size_t& size_out) {
    ifstream in(filename, ios::binary);
    if (!in.is_open()) {
        cout << "Ошибка при открытии файла для чтения" << endl;
        return nullptr;
    }

    in.read(reinterpret_cast<char*>(&size_out), sizeof(size_out));
    if (size_out == 0) {
        return nullptr;
    }

    Employee* array = new Employee[size_out];
    in.read(reinterpret_cast<char*>(array), sizeof(Employee) * size_out);

    in.close();
    return array;
}

//
// Действия над записями
//

const size_t MAX_RECORDS = 10;
const char* FILENAME = "my_binary_file.bin";

void action_delete() {
    size_t size = 0;
    Employee* array = read_from_binary(FILENAME, size);
    if (array == nullptr) return;

    int number_record = -1;
    string input;
    do {
        number_record = -1;
        cout << "Выберите номер записи (или -1 для отмены): ";
        cin >> input;
        try {
            number_record = stoi(input);
            if (number_record == -1) return;
        }
        catch (...) {
            std::cout << "Неверный ввод, попробуйте снова.\n";
        }

    } while (number_record < 0 || number_record >= size);


    try { // пробуем удалить элемент и затем сохранить всё в файле
        array = array_delete_at_index(array, size, number_record);

        cout << "Обновленный список: " << endl;
        array_print(array, size);

        write_to_binary(FILENAME, array, size);
    }
    catch (...) {
        cout << "Что-то пошло не так при попытке удалить запись!" << endl;
        // Если что-то пошло не по плану, то мы всегда удаляем список
    }

    array_clear(array);
}

void action_find() {
    size_t size = 0;
    Employee* array = read_from_binary(FILENAME, size);
    if (array == nullptr) return;

    string lastname;
    cout << "Введите фамилию сотрудника: ";
    cin >> lastname;

    try { 
        size_t seek_size = 0;
        Employee* seek_array = array_find_by_lastname(array, size, lastname.c_str(), seek_size);

        if (seek_array == nullptr) {
            cout << "Сотрудник с фамилией " << lastname << " не найден" << endl;
        }
        else {
            cout << "Результат поиска: " << endl;
            array_print(seek_array, seek_size);
            array_clear(seek_array);
        }
    }
    catch (...) {
        cout << "Что-то пошло не так при попытке поиска!" << endl;
        // Если что-то пошло не по плану, то мы всегда удаляем список
    }

    array_clear(array);
}

void action_sort() {
    size_t size = 0;
    Employee* array = read_from_binary(FILENAME, size);
    if (array == nullptr) return;

    try { // пробуем отсортировать список и сохраним результат
        array_sort(array, size);
        cout << "Обновленный список: " << endl;
        write_to_binary(FILENAME, array, size);
        array_print(array, size);
    }
    catch (...) {
        cout << "Что-то пошло не так при попытке сортировать список!" << endl;
    }

    array_clear(array);
}

bool menu() {
    size_t choice;
    cout << "\nВозможные действия с записями: ";
    cout << "\n\t1 - Удалить запись по её номеру \n\t2 - Поиск по фамилии \n\t3 - Сортировать по кол-ву продукции\n\t4 - Выход из меню" << endl;
    cout << "Введите действие: ";
    cin >> choice;

    switch (choice) {
    case 1: action_delete(); break;
    case 2: action_find(); break;
    case 3: action_sort(); break;
    default: return false;
    }

    return true;
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    // Создаём и заполняем массив из рабочих.
    Employee* array = array_init(MAX_RECORDS);

    // Записываем данные из массива в бинарный файл
    array_print(array, MAX_RECORDS);
    write_to_binary(FILENAME, array, MAX_RECORDS);
    array_clear(array);

    // Действия с меню
    bool flag_menu = true;
    do {
        // Menu
        size_t size_check;
        Employee* check = read_from_binary(FILENAME, size_check);
        if (size_check > 0) {
            flag_menu = menu();
        }
        else {
            cout << "В файле не осталось записей, выход из программы!" << endl;
            flag_menu = false;
        }
        array_clear(check);
    } while (flag_menu);

    return 0;
}