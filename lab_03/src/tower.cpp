#include <iostream>

// Узел двусвязного списка
struct Node {
    int disk;   // номер перемещаемого кольца
    int from;   // исходный стержень
    int to;     // целевой стержень
    Node* prev; // указатель на предыдущий ход
    Node* next; // указатель на следующий ход

    Node(int d, int f, int t) : disk(d), from(f), to(t), prev(nullptr), next(nullptr) {}
};

// Добавление элемента в конец списка
void append(Node*& head, Node*& tail, int disk, int from, int to) {
    Node* newNode = new Node(disk, from, to);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void printList(Node* head) {
    Node* cur = head;
    while (cur) {
        std::cout << "Move disk " << cur->disk << " from " << cur->from
                  << " to " << cur->to << '\n';
        cur = cur->next;
    }
}

// Полное освобождение памяти списка
void clearList(Node*& head, Node*& tail) {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
}

void hanoy(int n, int from, int to, int temp, Node*& head, Node*& tail) {
    if (n == 1) {
        append(head, tail, 1, from, to);
        return;
    }
    hanoy(n - 1, from, temp, to, head, tail);
    append(head, tail, n, from, to);
    hanoy(n - 1, temp, to, from, head, tail);
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;

    hanoy(8, 1, 3, 2, head, tail);

    // Вывод результата
    printList(head);

    // Освобождение памяти
    clearList(head, tail);

    return 0;
}