#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

// ��������� ���� ������������ ������
struct node {
    int data;       // ���� ��� �������� ������
    node* next;     // ��������� �� ��������� ����

    // ����������� �� ���������
    node() {
        next = nullptr;  // �������������� ��������� ��� nullptr
    }

    // ����������� � ����������
    node(int _data) {
        data = _data;    // ������������� ��������
        next = nullptr;  // �������������� ��������� ��� nullptr
    }
};

// ��������� ������� ��� ����� ������
template <typename diff>
void my_input(string text, diff& variable) {
    cout << text;     // ������� ���������
    cin >> variable;  // ��������� ��������
}

// ������� �������� ������� �������� ������
node* create_list() {
    // ������� ����� ���� �� ��������� ��������� �� 0 �� 100
    node* x = new node(rand() % 101);
    cout << "������ ������� ������������.\n";
    return x;  // ���������� ��������� �� ��������� ����
}

// ������� ������ ������
void my_input(node* x) {
    // �������� �� ���� ����� ������
    while (x) {
        cout << x->data << " ";  // ������� �������� �������� ����
        x = x->next;             // ��������� � ���������� ����
    }
    cout << endl;  // ������� �� ����� ������ ����� ������
}

// �������� ������� ��������� ������
void task(node** head) {
    // �������� �� ������ ������
    if (*head == nullptr) {
        cout << "��� ��������� � ������!\n";
        return;
    }

    // ������� ���������� ��������� � ������
    int count = 0;
    node* current = *head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    // ����������, ����� �������� ���������:
    // ���� ���������� ��������� ������ - ��������� �������� ��������
    // ���� �������� - ��������� ������
    bool keepOdd = (count % 2 == 0);

    // ������� ����� ������
    node* newHead = nullptr;
    node* tail = nullptr;
    current = *head;

    // �������� �� ��������� ������
    while (current != nullptr) {
        // ���������, ����� �� ��������� ������� �������
        bool shouldKeep = (keepOdd && current->data % 2 != 0) ||
            (!keepOdd && current->data % 2 == 0);

        if (shouldKeep) {
            // ������� ����� ���� � ����� �� ���������
            node* newNode = new node(current->data);

            // ��������� ��� � ����� ������
            if (newHead == nullptr) {
                newHead = newNode;  // ������ �������
                tail = newNode;
            }
            else {
                tail->next = newNode;  // ��������� � �����
                tail = newNode;
            }
        }
        current = current->next;  // ��������� � ���������� ����
    }

    // ������� ������ ������
    current = *head;
    while (current != nullptr) {
        node* temp = current;
        current = current->next;
        delete temp;  // ����������� ������
    }

    // ��������� ������ ������
    *head = newHead;

    // ������� ��������� ��������
    if (*head == nullptr) {
        cout << "��� ��������� � ������!\n";
    }
    else {
        cout << "������ �������!\n";
    }
}

// ������� ���������� ������ ���� � ����� ������
void �reation_node(node** head, int nodeData) {
    // ������� ����� ����
    node* tmp = new node(nodeData);

    // ���� ������ ����, ������ ����� ���� �������
    if (*head == nullptr) {
        *head = tmp;
        return;
    }

    // ���� ����� ������
    node* current = *head;
    while (current->next != nullptr) {
        current = current->next;
    }

    // ��������� ����� ���� � �����
    current->next = tmp;
}

// ������� ���������� N ����� ��������� � ������
void add_node(bool flag, node** head, int& N) {
    // ���������, ������ �� ������ �������
    if (!flag) {
        cout << "������ �������� ����� ��������, �� ������ ������\n";
    }
    else {
        // ����������� ���������� ����� ���������
        my_input("������� ���������� ����� ���������: ", N);

        // ��������� N ��������� ���������
        for (int i = 0; i < N; i++) {
            �reation_node(head, rand() % 101);
        }
        cout << N << " ����� ��������� ���������.\n";
    }
}

int main() {
    // ��������� ������ � ���������� ��������� �����
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    // ������������� ����������
    node* head = nullptr;
    char choice;
    int N;
    bool flag = false;

    // �������� ���� ����
    do {
        // ����� ���� � ���������� ������
        my_input("1. ������������� ������ ������� ������\n2. �������� N ����� ��������� � ������\n3. ������� ������ �� �����\n4. �������� ������ �� �������\n5. �����\n", choice);

        // ��������� ������ ������������
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
            cout << "����� �� ���������.\n";
            break;
        default:
            cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != '5');

    // ������� ������ ����� �������
    while (head != nullptr) {
        node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}