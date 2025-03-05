#include <iostream>
#include <ctime>

using namespace std;

// Функция для вывода массива
void print_array(int* matrix, int len_mtx) {
    for (size_t i = 0; i < len_mtx; i++) {
        cout.width(3);
        cout << *matrix << " ";
        matrix++;
    }
    cout << endl;
}

// Функция для генерации массива случайных чисел
void gen_array(int* matrix, int len_mtx) {
    for (size_t i = 0; i < len_mtx; i++) {
        *matrix = rand() % 101 - 50; // Генерация чисел от -50 до 50
        matrix++;
    }
}

// Функция для поиска наименьшего числа из первого массива, которого нет во втором
void smaller_of_the_two(int* mtx_one, int* mtx_two, int len_mtx) {
    int min_number = 0;
    bool min_flag = true;

    for (size_t i = 0; i < len_mtx; i++) {
        bool flag_equal = true;
        int nums_one = *mtx_one;

        // Сбрасываем указатель mtx_two на начало массива
        int* temp_mtx_two = mtx_two;

        for (size_t j = 0; j < len_mtx; j++) {
            int nums_two = *temp_mtx_two;

            if (nums_one == nums_two) {
                flag_equal = false;
                break;
            }

            temp_mtx_two++;
        }

        // Если число из первого массива не найдено во втором
        if (flag_equal) {
            if (min_flag || nums_one < min_number) {
                min_number = nums_one;
                min_flag = false;
            }
        }

        mtx_one++;
    }

    if (min_flag) {
        cout << "Нет уникальных значений в первом массиве." << endl;
    }
    else {
        cout << "Наименьшее число среди тех чисел первого массива, которые не входят во второй массив равно: " << min_number << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    const size_t len_arr = 30;
    int nums_one[len_arr]{ 6 };
    int nums_two[len_arr]{ 6 };

    // Генерация и вывод массивов
    gen_array(nums_one + 1, len_arr - 1);
    gen_array(nums_two + 1, len_arr - 1);

    cout << "Первый массив: ";
    print_array(nums_one, len_arr);

    cout << "Второй массив: ";
    print_array(nums_two, len_arr);

    // Поиск наименьшего уникального числа
    smaller_of_the_two(nums_one, nums_two, len_arr);

    return 0;
}
