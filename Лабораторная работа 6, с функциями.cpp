#include <iostream>
#include <string>

// Вводим строку, удаляем каждую 3 букву, подсчитываем удаления. Выводим первое и последнее слово получившейся строки.

using namespace std;

template <typename MYL> void my_print(string text, MYL& value) {
    cout << text;
    getline(cin, value);
}

bool is_alpha(char letter) {
    // Строка для проверки на буквенность
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return alphabet.find(letter) != -1;
}

void del_free_char_alpha(string &line_proc) {

    // Задаём начало строки
    int ind = 0;

    // Задаём счётчик, который будет считать каждую БУКВУ в нашем слове.
    int count_char = 0;

    // Задаём счётчик, который будет считать кол-во удалённых символов
    int count_delete = 0;

    // Проход по всем символам строки, удаляя каждую третью БУКВУ
    while (ind < line_proc.size()) {
        if (is_alpha(line_proc[ind])){
            count_char++;
            if (count_char % 3 == 0) {
                line_proc.erase(ind, 1);
                count_delete++;
                continue;
            }
        }
        ind++;
    }   

    // Выводим кол-во удалений
    cout << "Количество удалённых символов = " << count_delete << endl;
}

void l_strip(string &line, string sep) {
    while (!line.empty() && line.find(sep) == 0) {
        line.erase(0, sep.length());
    }
}

void r_strip(string &line, string sep) {
    while (!line.empty() && line.rfind(sep) == line.length() - sep.length()) {
        line.erase(line.rfind(sep), sep.length());
    }
}

string get_first_word(string new_line, string sep) {
    string first_word = new_line.substr(0, new_line.find(sep));
    return first_word;
}

string get_last_word(string new_line, string sep) {
    string last_word = new_line.substr(new_line.rfind(sep) + sep.length());
    return last_word;
}

int main() {
    setlocale(LC_ALL, "RU");

    // Вводим строку, которую будем обрабатывать
    string line;
    my_print("Введите строку для обработки: ", line);

    // Вводим разделитель между словами в нашей строке
    string separator;
    my_print("Введите разделитель строки: ", separator);

    // Проверяем пустая ли строка введена
    if (line.empty()) {
        cout << endl << "Строка не содержит слов и не может быть обработана" << endl;
    }
    else {
        // Удаляем каждый третий символ в строке и выводим кол-во удалений
        del_free_char_alpha(line);
        cout << "Финальный вид строки: " << line << endl;

        // Удаляем разделители в начале строки 
        l_strip(line, separator);

        // Удаляем разделители в конце строки
        r_strip(line, separator);

        // Выводим на экран первое слово нашей обновлённой строки
        cout << "Первое слово обновлённой строки: " << get_first_word(line, separator) << endl;

        // Выводим на экран последнее слово нашей обновлённой строки
        cout << "Последнее слово обновлённой строки: " << get_last_word(line, separator) << endl;

    }

    system("pause");
    return 0;
}
