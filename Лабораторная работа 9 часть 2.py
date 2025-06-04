from collections import namedtuple
import random
import pickle

FILENAME = "my_binary_file"

"Это именованный кортеж, описывающий рабочего, который заменяет структуру"
Employee = namedtuple('Employee', [
    'name',
    "lastname",
    "fathername",
    "number_of_products",
    "working_day"
])

"Это именованный кортеж, описывающий день недели который заменяет структуру"
WeekDay = namedtuple('WeekDay', ["serial_number", "name_day"])


def get_employee():
    """Эта функция генерирует и возвращает экземпляр структуры Employee"""

    _names: tuple = ("Andrey", "Danil", "Vlad", "Roman", "Nikita",
                     "Kirill", "Yra", "Jeniya", "Ilya", "Marat")
    name = random.choice(_names)

    _lastname: tuple = ("Troshin", "Lobanov", "Kolchin", "Soldatov", "Vinogradov",
                        "Jelonkin", "Safronov", "Usmankin", "Basharov", "Polyakov")
    lastname = random.choice(_lastname)

    _fathernames: tuple = ("Alekseevich", "Dmitrievich", "Ilych", "Petrovich", "Maksimovich",
                           "Matveevich", "Michalych", "Renatovich", "Romanovich", "Valerevich")
    fathername = random.choice(_fathernames)

    number_of_products = random.randint(10, 100)
    week_day = get_weekday()

    return Employee(name, lastname, fathername, number_of_products, week_day)


def get_weekday():
    """Эта функция генерирует и возвращает экземпляр структуры WeekDay"""

    _days = ("Monday",
             "Tuesday",
             "Wednesday",
             "Thursday",
             "Friday",
             "Saturday",
             "Sunday")

    serial_number = random.randint(0, len(_days) - 1)
    day = _days[serial_number]

    return WeekDay(serial_number, day)


def get_array_employee():
    """Содание словаря экземпляров Employee с уникальным id-номером"""

    _workpeople = []

    for _ in range(10):
        _workpeople.append(get_employee())

    return _workpeople


def print_records():
    for ind, content in read_binary_file().items():
        ord_ind, day_name = content.working_day
        print(f"{ind} запись:", end=" ")
        print(f"ФИО: {content.name}, {content.lastname}, {content.fathername} |", end=" ")
        print(f"День недели: {day_name}({ord_ind}) | Кол-во изделий: {content.number_of_products}")


def write_to_binary_file(records: list):
    """Запись словаря экземпляров Employee с уникальным id-номером в бинарный файл"""

    try:
        with open(FILENAME, "wb") as fw:
            content = {}
            for ind, record in enumerate(records, start=1):
                content.update({str(ind): record})
            pickle.dump(content, fw)
    except FileNotFoundError:
        print(f"Ошибка открытия файла {FILENAME} для ЗАПИСИ в бинарном виде!")


def read_binary_file():
    """Чтение словаря экземпляров Employee с уникальным id-номером из бинарного файла"""

    try:
        with open(FILENAME, "rb") as fr:
            return pickle.load(fr)
    except FileNotFoundError:
        print(f"Ошибка открытия файла {FILENAME} для ЧТЕНИЯ в бинарном виде!")


def menu():
    def validate(func):
        def wrapper(*args, **kwargs):
            while True:
                try:
                    result = func(*args, **kwargs)
                    return result
                except ValueError as e:
                    print(e, "Попробуйте ещё раз!")

        return wrapper

    @validate
    def validate_action(text: str):
        user_input = input(text)
        if user_input in ("1", "2", "3", "4"):
            return user_input
        raise ValueError("Такого действия нет!")

    @validate
    def validate_index_record(text: str, records: dict):
        user_input = input(text)
        if user_input in records:
            return user_input
        raise ValueError("Такой записи нет!")

    @validate
    def validate_search_record(text: str):
        user_input = input(text)
        if user_input and user_input.isalpha():
            return user_input
        raise ValueError("Введите строку для поиска фамилии!")

    @validate
    def validate_sort_key(text: str):
        user_input = input(text)
        if user_input in ("1", "2", "3"):
            return user_input
        raise ValueError("Такого поля нет!")

    def is_empty_records(records: dict):
        if len(records) <= 0:
            print("Записи в файле закончились, спасибо за то, что выбрали нашу программу!")
            exit_menu()
        return True

    def deleted_record():
        current_records = read_binary_file()
        if is_empty_records(current_records):
            index_record: str = validate_index_record("Введите номер запсии для удаления -> ", current_records)
            del current_records[index_record]
            write_to_binary_file(list(current_records.values()))
            print_records()

    def search_record():
        current_records = read_binary_file()
        lastname_search = validate_search_record("Введите фамилию для поиска записей -> ")

        if lastname_search in map(lambda x: x.lastname, current_records.values()):
            print("Доступные записи:")
            for ind, content in current_records.items():
                if content.lastname == lastname_search:
                    ord_ind, day_name = content.working_day
                    print(f"{ind} запись:", end=" ")
                    print(f"ФИО: {content.name}, {content.lastname}, {content.fathername} |", end=" ")
                    print(f"День недели: {day_name}({ord_ind}) | Кол-во изделий: {content.number_of_products}")
        else:
            print("Не удалось найти записи о таком работнике!")

    def sort_records():
        current_records = read_binary_file()

        def sort_name():
            sort_result = sorted(current_records.values(), key=lambda x: x.name)
            write_to_binary_file(sort_result)

        def sort_number_of_products():
            sort_result = sorted(current_records.values(), key=lambda x: x.number_of_products)
            write_to_binary_file(sort_result)

        def sort_working_day():
            sort_result = sorted(current_records.values(), key=lambda x: x.working_day.serial_number)
            write_to_binary_file(sort_result)

        if is_empty_records(current_records):
            print("\nСортировка доступна по следующим полям:",
                  "\n1 - Имя",
                  "\n2 - Кол-во обработанных изделий",
                  "\n3 - День недели")
            sort_key = validate_sort_key("Выберите поле, по которому хотите произвести сортировку -> ")

            if sort_key == "1":
                sort_name()

            elif sort_key == "2":
                sort_number_of_products()

            elif sort_key == "3":
                sort_working_day()

            print_records()

    def exit_menu():
        raise TypeError("Выход из меню!")

    def interaction_menu():
        print("Добрый день! Это меню взаимодействий с бинарным файлом,",
              "который содержит в себе следующие данные о рабочих:\n")
        print_records()
        try:
            while True:
                print("\nДля вас доступны такие действия, как:",
                      "\n1 - Удаление записи по её номeру",
                      "\n2 - Поиск по фамилии рабочего",
                      "\n3 - Сортировка по одному из полей",
                      "\n4 - Выход из меню")

                action: str = validate_action("Введите действие -> ")

                if action == "1":
                    deleted_record()
                elif action == "2":
                    search_record()
                elif action == "3":
                    sort_records()
                elif action == "4":
                    exit_menu()

        except Exception as e:
            print(e)

    interaction_menu()


original_records = get_array_employee()
write_to_binary_file(original_records)
menu()
