#include <iostream>
#include <string>

// Вводим строку, удаляем каждую 3 букву, подсчитываем удаления. Выводим первое и последнее слово получившейся строки.

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    // Вводим строку, которую будем обрабатывать
    string line;
    cout << "Введите строку для обработки: ";
    getline(cin, line);

    // Вводим разделитель между словами в нашей строке
    string separator;
    cout << "Введите разделитель строки: ";
    getline(cin, separator);

    // Строка для проверки на буквенность
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Задаём начало строки
    int ind = 0;

    // Задаём счётчик, который будет считать каждую БУКВУ в нашем слове.
    int count_char = 0;

    // Задаём счётчик, который будет считать кол-во удалённых символов
    int count_delete = 0;

    // Проход по всем символам строки, удаляя каждую третью БУКВУ
    while (ind < line.size()) {
        if (alphabet.find(line[ind]) != -1)
            count_char++;
        if (count_char % 3 == 0 && alphabet.find(line[ind]) != -1) {
            line.erase(ind, 1);
            count_delete++;
            ind--;
        }
        ind++;
    }

    if (line.empty()) {
        cout << endl << "Строка не содержит слов и не может быть обработана" << endl;
    }
    else {

        cout << "Финальный вид строки: " << line << endl;

        // Удаляем разделители в начале строки 
        while (!line.empty() && line.find(separator) == 0) {
            line.erase(0, separator.length());
        }

        // Удаляем разделители в конце строки
        while (!line.empty() && line.rfind(separator) == line.length() - separator.length()) {
            line.erase(line.rfind(separator), separator.length());
        }

        // Выводим на экран первое слово нашей обновлённой строки
        string first_word = line.substr(0, line.find(separator));
        cout << "Первое слово: " << first_word << endl;

        // Выводим на экран последнее слово нашей обновлённой строки
        string last_word = line.substr(line.rfind(separator) + separator.length());
        cout << "Последнее слово: " << last_word << endl;

        // Выводим кол-во удалений
        cout << "Количество удалённых символов = " << count_delete << endl;
    }

    system("pause");
    return 0;
}
