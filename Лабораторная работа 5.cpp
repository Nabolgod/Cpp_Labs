#include <iostream>

using namespace std;

//void print_table_element(int one, int two) {
//    cout << "Первый массив: " << one << "\t";
//    cout << "Второй массив: " << two << endl;
//
//}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    int nums_one[30]{ 6 };
    int nums_two[30]{ 6 };

    for (int i = 1; i < 30; i++) {
        nums_one[i] = rand() % 101 - 50;
        nums_two[i] = rand() % 101 - 50;
    }

    int min_number;
    bool min_flag = true;

    for (int i = 0; i < 30; i++) {
        bool flag_equal = true;

        for (int j = 0; j < 30; j++) {
            if (nums_one[i] == nums_two[j]) {
                flag_equal = false;
                break;
            }
        }

        if (flag_equal) {
            if (min_flag || nums_one[i] < min_number) {
                min_number = nums_one[i];
                min_flag = false;
            }
        }
        //print_table_element(nums_one[i], nums_two[i]);
    }

    if (min_flag)
        cout << "Нет уникальных значений в первом массиве.";
    else
        cout << "Наименьшее число среди тех чисел первого массива,\
 которые не входят во второй массив равно: " << min_number << endl;

    return 0;
}
