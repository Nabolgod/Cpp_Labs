#include <iostream>
#include <string>

using namespace std;

class MathObject {
public:
    virtual ~MathObject() = default;

    virtual string get_name() const = 0;

    virtual MathObject* operator+(const MathObject& other) const = 0;
    virtual MathObject* operator-(const MathObject& other) const = 0;
    virtual MathObject* operator*(const MathObject& other) const = 0;
    virtual MathObject* operator*(int scalar) const = 0;

    virtual void str_view() const = 0;
    virtual MathObject* new_obj_return() const = 0;

    // Методы проверки возможности операций
    virtual bool can_add(const MathObject& other) const = 0;
    virtual bool can_subtract(const MathObject& other) const = 0;
    virtual bool can_multiply(const MathObject& other) const = 0;
    virtual bool can_multiply_scalar() const { return true; }
};

class Matrix : public MathObject {
private:
    int rows, cols;
    int** content;

    void fill_matrix() {
        cout << "Заполните матрицу " << rows << "x" << cols << ":" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "Введите значения для элемента [" << i + 1 << ", " << j + 1 << "] : ";
                cin >> content[i][j];
            }
        }
    }

public:
    string get_name() const override {
        return "Матрица";
    }

    Matrix() {
        cout << "\nСоздание матрицы:" << endl;

        while (true) {
            cout << "Введите кол-во строк: ";
            cin >> rows;
            cout << "Введите кол-во столбцов: ";
            cin >> cols;

            if (rows > 0 && cols > 0) {
                break;
            }
            cout << "Ошибка: размеры должны быть положительными числами. Попробуйте снова.\n";
        }

        content = new int* [rows];
        for (int i = 0; i < rows; i++) {
            content[i] = new int[cols];
        }

        fill_matrix();
    }

    Matrix(int r, int c) : rows(r), cols(c) {
        content = new int* [rows];
        for (int i = 0; i < rows; i++) {
            content[i] = new int[cols]();
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] content[i];
        }
        delete[] content;
    }

    // Проверка возможности операций
    bool can_add(const MathObject& other) const override {
        const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
        if (!other_matrix) return false;
        return (rows == other_matrix->rows && cols == other_matrix->cols);
    }

    bool can_subtract(const MathObject& other) const override {
        return can_add(other);
    }

    bool can_multiply(const MathObject& other) const override {
        const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
        if (!other_matrix) return false;
        return (cols == other_matrix->rows);
    }

    // Операции
    Matrix* operator+(const MathObject& other) const override {
        const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
        if (!other_matrix || !can_add(other)) return nullptr;

        Matrix* result = new Matrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result->content[i][j] = content[i][j] + other_matrix->content[i][j];
            }
        }
        return result;
    }

    Matrix* operator-(const MathObject& other) const override {
        const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
        if (!other_matrix || !can_subtract(other)) return nullptr;

        Matrix* result = new Matrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result->content[i][j] = content[i][j] - other_matrix->content[i][j];
            }
        }
        return result;
    }

    Matrix* operator*(const MathObject& other) const override {
        const Matrix* other_matrix = dynamic_cast<const Matrix*>(&other);
        if (!other_matrix || !can_multiply(other)) return nullptr;

        Matrix* result = new Matrix(rows, other_matrix->cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other_matrix->cols; j++) {
                result->content[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result->content[i][j] += content[i][k] * other_matrix->content[k][j];
                }
            }
        }
        return result;
    }

    Matrix* operator*(int scalar) const override {
        Matrix* result = new Matrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result->content[i][j] = content[i][j] * scalar;
            }
        }
        return result;
    }

    Matrix* new_obj_return() const override {
        return new Matrix();
    }

    void str_view() const override {
        cout << "\nМатрица " << rows << "x" << cols << ":" << endl;
        for (int i = 0; i < rows; i++) {
            cout << "[ ";
            for (int j = 0; j < cols; j++) {
                cout << content[i][j] << " ";
            }
            cout << "]" << endl;
        }
    }
};

class Polynomial : public MathObject {
private:
    int degree;
    int* coefficients; // coefficients[i] - коэффициент при x^i

    void normalize() {
        // Убираем нулевые старшие коэффициенты
        while (degree > 0 && coefficients[degree] == 0) {
            degree--;
        }
    }

    void copy_coefficients(const Polynomial& other) {
        degree = other.degree;
        coefficients = new int[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = other.coefficients[i];
        }
    }

public:
    string get_name() const override {
        return "Полином";
    }

    Polynomial() {
        cout << "\nСоздание полинома:" << endl;

        cout << "Введите степень полинома: ";
        do {
            cin >> degree;

            if (degree < 0) {
                cout << "Ошибка: степень не может быть отрицательной.\nПопробуйте снова: " ;
            }
        
        } while (degree < 0);


        coefficients = new int[degree + 1];

        cout << "Введите коэффициенты полинома (от свободного члена до старшего):" << endl;
        for (int i = 0; i <= degree; i++) {
            cout << "Коэффициент при x^" << i << ": ";
            cin >> coefficients[i];
        }

        normalize();
    }

    Polynomial(int deg, int* coeffs) : degree(deg) {
        coefficients = new int[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = coeffs[i];
        }
        normalize();
    }

    Polynomial(const Polynomial& other) {
        copy_coefficients(other);
    }

    ~Polynomial() {
        delete[] coefficients;
    }

    bool can_add(const MathObject& other) const override {
        return dynamic_cast<const Polynomial*>(&other) != nullptr;
    }

    bool can_subtract(const MathObject& other) const override {
        return can_add(other);
    }

    bool can_multiply(const MathObject& other) const override {
        return can_add(other);
    }

    Polynomial* operator+(const MathObject& other) const override {
        const Polynomial* other_poly = dynamic_cast<const Polynomial*>(&other);
        if (!other_poly) return nullptr;

        int max_degree = (degree > other_poly->degree) ? degree : other_poly->degree;
        int* result_coeffs = new int[max_degree + 1]();

        for (int i = 0; i <= degree; i++) {
            result_coeffs[i] += coefficients[i];
        }

        for (int i = 0; i <= other_poly->degree; i++) {
            result_coeffs[i] += other_poly->coefficients[i];
        }

        Polynomial* result = new Polynomial(max_degree, result_coeffs);
        delete[] result_coeffs;
        return result;
    }

    Polynomial* operator-(const MathObject& other) const override {
        const Polynomial* other_poly = dynamic_cast<const Polynomial*>(&other);
        if (!other_poly) return nullptr;

        int max_degree = (degree > other_poly->degree) ? degree : other_poly->degree;
        int* result_coeffs = new int[max_degree + 1]();

        for (int i = 0; i <= degree; i++) {
            result_coeffs[i] += coefficients[i];
        }

        for (int i = 0; i <= other_poly->degree; i++) {
            result_coeffs[i] -= other_poly->coefficients[i];
        }

        Polynomial* result = new Polynomial(max_degree, result_coeffs);
        delete[] result_coeffs;
        return result;
    }

    Polynomial* operator*(const MathObject& other) const override {
        const Polynomial* other_poly = dynamic_cast<const Polynomial*>(&other);
        if (!other_poly) return nullptr;

        int result_degree = degree + other_poly->degree;
        int* result_coeffs = new int[result_degree + 1]();

        for (int i = 0; i <= degree; i++) {
            for (int j = 0; j <= other_poly->degree; j++) {
                result_coeffs[i + j] += coefficients[i] * other_poly->coefficients[j];
            }
        }

        Polynomial* result = new Polynomial(result_degree, result_coeffs);
        delete[] result_coeffs;
        return result;
    }

    Polynomial* operator*(int scalar) const override {
        if (scalar == 0) {
            int* zero_coeff = new int[1] {0};
            Polynomial* result = new Polynomial(0, zero_coeff);
            delete[] zero_coeff;
            return result;
        }

        int* result_coeffs = new int[degree + 1];
        for (int i = 0; i <= degree; i++) {
            result_coeffs[i] = coefficients[i] * scalar;
        }

        Polynomial* result = new Polynomial(degree, result_coeffs);
        delete[] result_coeffs;
        return result;
    }

    Polynomial* new_obj_return() const override {
        return new Polynomial();
    }

    void str_view() const override {
        cout << "\nПолином степени " << degree << ":" << endl;

        if (degree == 0 && coefficients[0] == 0) {
            cout << "0" << endl;
            return;
        }

        bool first_term = true;

        for (int i = degree; i >= 0; i--) {
            int coeff = coefficients[i];

            if (coeff == 0) continue;

            // Знак
            if (!first_term) {
                if (coeff > 0) cout << " + ";
                else {
                    cout << " - ";
                    coeff = -coeff;
                }
            }
            else if (coeff < 0) {
                cout << "-";
                coeff = -coeff;
            }

            // Коэффициент
            if (coeff != 1 || i == 0) {
                cout << coeff;
            }

            // Переменная
            if (i > 0) {
                cout << "x";
                if (i > 1) {
                    cout << "^" << i;
                }
            }

            first_term = false;
        }
        cout << endl;
    }
};

class Vector : public MathObject {
private:
    double x, y;
    bool is_scalar_result; // Флаг, что это результат скалярного произведения

public:
    string get_name() const override {
        if (is_scalar_result) {
            return "Скалярное произведение";
        }
        return "Вектор";
    }

    Vector() : is_scalar_result(false) {
        cout << "\nСоздание вектора:" << endl;

        cout << "Введите координату x: ";
        cin >> x;

        cout << "Введите координату y: ";
        cin >> y;
    }

    // Конструктор для обычного вектора
    Vector(double x_val, double y_val) : x(x_val), y(y_val), is_scalar_result(false) {}

    // Конструктор для результата скалярного произведения
    Vector(double scalar_result) : x(scalar_result), y(0), is_scalar_result(true) {}

    bool can_add(const MathObject& other) const override {
        const Vector* other_vec = dynamic_cast<const Vector*>(&other);
        if (!other_vec) return false;
        // Можно складывать только обычные векторы, не результаты скалярных произведений
        return !is_scalar_result && !other_vec->is_scalar_result;
    }

    bool can_subtract(const MathObject& other) const override {
        return can_add(other);
    }

    bool can_multiply(const MathObject& other) const override {
        const Vector* other_vec = dynamic_cast<const Vector*>(&other);
        if (!other_vec) return false;
        // Можно умножать только обычные векторы
        return !is_scalar_result && !other_vec->is_scalar_result;
    }

    Vector* operator+(const MathObject& other) const override {
        const Vector* other_vec = dynamic_cast<const Vector*>(&other);
        if (!other_vec || !can_add(other)) return nullptr;

        return new Vector(x + other_vec->x, y + other_vec->y);
    }

    Vector* operator-(const MathObject& other) const override {
        const Vector* other_vec = dynamic_cast<const Vector*>(&other);
        if (!other_vec || !can_subtract(other)) return nullptr;

        return new Vector(x - other_vec->x, y - other_vec->y);
    }

    // Скалярное произведение векторов
    Vector* operator*(const MathObject& other) const override {
        const Vector* other_vec = dynamic_cast<const Vector*>(&other);
        if (!other_vec || !can_multiply(other)) return nullptr;

        double dot_product = x * other_vec->x + y * other_vec->y;
        return new Vector(dot_product); // Используем конструктор для скалярного результата
    }

    // Умножение вектора на скаляр
    Vector* operator*(int scalar) const override {
        if (is_scalar_result) {
            // Если это уже результат скалярного произведения, умножаем его на скаляр
            return new Vector(x * scalar);
        }
        return new Vector(x * scalar, y * scalar);
    }

    Vector* new_obj_return() const override {
        return new Vector();
    }

    void str_view() const override {
        if (is_scalar_result) {
            cout << "\nСкалярное произведение векторов = " << x << endl;
        }
        else {
            cout << "\nВектор: (" << x << ", " << y << ")" << endl;
        }
    }
};

MathObject* initialization_object_first() {
    int choice;

    do {
        cout << "\nВыберите тип первого объекта:" << endl;
        cout << "1. Матрица" << endl;
        cout << "2. Полином" << endl;
        cout << "3. Вектор" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) {
            return new Matrix();
        }
        else if (choice == 2) {
            return new Polynomial();
        }
        else if (choice == 3) {
            return new Vector();
        }
        else {
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (true);
}

MathObject* initialization_object_second(MathObject* first_obj) {
    int choice;

    do {
        cout << "\nВыберите тип второго объекта:" << endl;
        cout << "1. " << first_obj->get_name() << endl;
        cout << "2. Целое число" << endl;

        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) {
            return first_obj->new_obj_return();
        }
        else if (choice == 2) {
            return nullptr; // Индикатор числа
        }
        else {
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (true);
}

MathObject* perform_operation(MathObject* first_obj, MathObject* second_obj, int number) {
    if (second_obj == nullptr) {
        // Операция с числом
        cout << "\nДоступные операции:" << endl;
        cout << "1. Умножение на число" << endl;

        int choice;
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) {
            return (*first_obj) * number;
        }
        return nullptr;
    }

    // Операция с другим объектом
    cout << "\nДоступные операции:" << endl;

    bool has_operations = false;
    int option = 1;

    if (first_obj->can_add(*second_obj)) {
        cout << option << ". Сложение" << endl;
        has_operations = true;
        option++;
    }

    if (first_obj->can_subtract(*second_obj)) {
        cout << option << ". Вычитание" << endl;
        has_operations = true;
        option++;
    }

    if (first_obj->can_multiply(*second_obj)) {
        cout << option << ". Умножение" << endl;
        has_operations = true;
        option++;
    }

    if (!has_operations) {
        cout << "Нет доступных операций для данных объектов!" << endl;
        return nullptr;
    }

    int choice;
    cout << "Ваш выбор: ";
    cin >> choice;

    // Преобразуем выбор пользователя в соответствующую операцию
    int operation_count = 0;
    if (first_obj->can_add(*second_obj)) {
        operation_count++;
        if (operation_count == choice) {
            return (*first_obj) + (*second_obj);
        }
    }

    if (first_obj->can_subtract(*second_obj)) {
        operation_count++;
        if (operation_count == choice) {
            return (*first_obj) - (*second_obj);
        }
    }

    if (first_obj->can_multiply(*second_obj)) {
        operation_count++;
        if (operation_count == choice) {
            return (*first_obj) * (*second_obj);
        }
    }

    return nullptr;
}

void menu() {
    cout << "Добро пожаловать в консольное меню для выполнения математических операций с различными объектами!\n\n";

    while (true) {
        // Создаем первый объект
        MathObject* first_obj = initialization_object_first();
        cout << "\nПервый объект:" << endl;
        first_obj->str_view();

        // Создаем второй объект
        MathObject* second_obj = nullptr;
        int number = 0;

        while (true) {
            second_obj = initialization_object_second(first_obj);

            if (second_obj) {
                // Это объект
                cout << "\nВторой объект:" << endl;
                second_obj->str_view();

                // Проверяем доступные операции
                if (!first_obj->can_add(*second_obj) &&
                    !first_obj->can_subtract(*second_obj) &&
                    !first_obj->can_multiply(*second_obj)) {

                    cout << "\nНет доступных операций для данных объектов!" << endl;
                    cout << "Пожалуйста, введите другой второй объект." << endl;

                    delete second_obj;
                    second_obj = nullptr;
                    continue;
                }
            }
            else {
                // Это число
                cout << "Введите целое число: ";
                cin >> number;
            }
            break;
        }

        // Выполняем операцию
        MathObject* result = nullptr;
        while (!result) {
            result = perform_operation(first_obj, second_obj, number);
            if (!result) {
                cout << "Неверный выбор операции. Попробуйте снова." << endl;
            }
        }

        // Выводим результат
        cout << "\nРезультат операции:" << endl;
        result->str_view();

        // Очистка памяти
        delete first_obj;
        if (second_obj) delete second_obj;
        delete result;

        // Повтор
        char again;
        cout << "\nХотите выполнить еще одну операцию? (y/n): ";
        cin >> again;
        if (again != 'y' && again != 'Y') {
            break;
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    menu();
    return 0;
}
