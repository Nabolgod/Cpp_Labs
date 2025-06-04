#include <iostream>
#include <ctime>
#include <cmath>

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
void my_input(node* x) {
    // Проходим по всем узлам списка
    while (x) {
        cout << x->data << " ";  // Выводим значение текущего узла
        x = x->next;             // Переходим к следующему узлу
    }
    cout << endl;  // Переход на новую строку после вывода
}

// Основная функция обработки списка
void task(node** head) {
    // Проверка на пустой список
    if (*head == nullptr) {
        cout << "Нет элементов в списке!\n";
        return;
    }

    // Подсчет количества элементов в списке
    int count = 0;
    node* current = *head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    // Определяем, какие элементы сохранять:
    // Если количество элементов четное - сохраняем нечетные значения
    // Если нечетное - сохраняем четные
    bool keepOdd = (count % 2 == 0);

    // Создаем новый список
    node* newHead = nullptr;
    node* tail = nullptr;
    current = *head;

    // Проходим по исходному списку
    while (current != nullptr) {
        // Проверяем, нужно ли сохранять текущий элемент
        bool shouldKeep = (keepOdd && current->data % 2 != 0) ||
            (!keepOdd && current->data % 2 == 0);

        if (shouldKeep) {
            // Создаем новый узел с таким же значением
            node* newNode = new node(current->data);

            // Добавляем его в новый список
            if (newHead == nullptr) {
                newHead = newNode;  // Первый элемент
                tail = newNode;
            }
            else {
                tail->next = newNode;  // Добавляем в конец
                tail = newNode;
            }
        }
        current = current->next;  // Переходим к следующему узлу
    }

    // Удаляем старый список
    current = *head;
    while (current != nullptr) {
        node* temp = current;
        current = current->next;
        delete temp;  // Освобождаем память
    }

    // Обновляем голову списка
    *head = newHead;

    // Выводим результат операции
    if (*head == nullptr) {
        cout << "Нет элементов в списке!\n";
    }
    else {
        cout << "Список изменен!\n";
    }
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

int main() {
    // Настройка локали и генератора случайных чисел
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    // Инициализация переменных
    node* head = nullptr;
    char choice;
    int N;
    bool flag = false;

    // Основной цикл меню
    do {
        // Вывод меню и считывание выбора
        my_input("1. Сгенерировать первый элемент списка\n2. Добавить N новых элементов в список\n3. Вывести список на экран\n4. Изменить список по заданию\n5. Выход\n", choice);

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
            my_input(head);
            break;
        case '4':
            task(&head);
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

    return 0;
}
