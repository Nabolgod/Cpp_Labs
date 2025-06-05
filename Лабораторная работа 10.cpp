#include <iostream>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;

// Структура узла односвязного списка
struct node {
    int data;       // Поле для хранения данных
    node* next;     // Указатель на следующий узел

    // Конструктор по умолчанию
    node() {
        next = nullptr;  // Инициализируем указатель как nullptr
    }

    // Конструктор с параметром
    node(int _data) {
        data = _data;    // Устанавливаем значение
        next = nullptr;  // Инициализируем указатель как nullptr
    }
};

// Шаблонная функция для ввода данных
template <typename diff>
void my_input(string text, diff& variable) {
    cout << text;     // Выводим подсказку
    cin >> variable;  // Считываем значение
}

// Функция создания первого элемента списка
node* create_list() {
    // Создаем новый узел со случайным значением от 0 до 100
    node* x = new node(rand() % 101);
    cout << "Первый элемент сгенерирован.\n";
    return x;  // Возвращаем указатель на созданный узел
}

// Функция вывода списка
void list_print(node* x) {
    // Проходим по всем узлам списка
    while (x) {
        cout << x->data << " ";  // Выводим значение текущего узла
        x = x->next;             // Переходим к следующему узлу
    }
    cout << endl;  // Переход на новую строку после вывода
}

size_t list_size(node* head) {
    size_t count = 0;
    node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Основная функция обработки списка
node* task(node* head) {
    // Проверка на пустой список
    if (head == nullptr) {
        cout << "Нет элементов в списке!\n";
        return nullptr;
    }

    // Подсчет количества элементов в списке
    size_t count = list_size(head);

    // Определяем, какие элементы сохранять:
    // Если количество элементов четное - сохраняем нечетные значения
    // Если нечетное - сохраняем четные
    bool keepOdd = (count % 2 == 0);

    node* current = head;
    node* prev = nullptr;
    size_t index = 1;

    while (current != nullptr) {
        bool remove_this = ((current->data) % 2 == 0) == keepOdd;

        if (remove_this) {
            node* to_remove = current;
            if (prev) prev->next = current->next;
            else head = current->next; // удаляет нач. ноду (head)

            current = current->next;
            delete to_remove;
        }
        else {
            prev = current;
            current = current->next;
        }
        ++index;
    }

    // Выводим результат операции
    if (head == nullptr) {
        cout << "Нет элементов в списке!\n";
    }
    else {
        cout << "Список изменен!\n";
    }

    return head;
}

// Функция добавления нового узла в конец списка
void сreation_node(node** head, int nodeData) {
    // Создаем новый узел
    node* tmp = new node(nodeData);

    // Если список пуст, делаем новый узел головой
    if (*head == nullptr) {
        *head = tmp;
        return;
    }

    // Ищем конец списка
    node* current = *head;
    while (current->next != nullptr) {
        current = current->next;
    }

    // Добавляем новый узел в конец
    current->next = tmp;
}

// Функция добавления N новых элементов в список
void add_node(bool flag, node** head, int& N) {
    // Проверяем, создан ли первый элемент
    if (!flag) {
        cout << "Нельзя добавить новые элементы, не создав первый\n";
    }
    else {
        // Запрашиваем количество новых элементов
        my_input("Введите количество новых элементов: ", N);

        // Добавляем N случайных элементов
        for (int i = 0; i < N; i++) {
            сreation_node(head, rand() % 101);
        }
        cout << N << " новых элементов добавлены.\n";
    }
}

void menu() {
    // Инициализация переменных
    node* head = nullptr;
    char choice;
    int N;
    bool flag = false;

    // Основной цикл меню
    do {
        // Вывод меню и считывание выбора
        my_input("1. Сгенерировать первый элемент списка\n2.\
 Добавить N новых элементов в список\n3. Вывести список на экран\n4.\
 Изменить список по заданию\n5. Выход\n", choice);

        // Обработка выбора пользователя
        switch (choice) {
        case '1':
            head = create_list();
            flag = true;
            break;
        case '2':
            add_node(flag, &head, N);
            break;
        case '3':
            list_print(head);
            break;
        case '4':
            head = task(head);
            break;
        case '5':
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != '5');

    // Очистка памяти перед выходом
    while (head != nullptr) {
        node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // Настройка локали и генератора случайных чисел
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    menu();
    return 0;
}
