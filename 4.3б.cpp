#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <iomanip> // Для форматированного вывода

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    // Конструкторы
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    // Оператор присваивания
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Деструктор
    ~DoublyLinkedList() {
        clear();
    }

    // Конструктор перемещения
    DoublyLinkedList(DoublyLinkedList&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    // Оператор перемещающего присваивания
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Инициализация первого элемента
    void init_first(const T& value) {
        if (empty()) {
            head = tail = new Node(value);
            size = 1;
        }
        else {
            std::cout << "List is not empty. First element already exists.\n";
        }
    }

    // Добавление элемента в конец
    void push_back(const T& value) {
        if (empty()) {
            init_first(value);
        }
        else {
            Node* newNode = new Node(value);
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
            size++;
        }
    }

    // Добавление элемента в начало
    void push_front(const T& value) {
        if (empty()) {
            init_first(value);
        }
        else {
            Node* newNode = new Node(value);
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            size++;
        }
    }

    // Удаление элемента по значению
    bool remove(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }

                if (current->next) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = current->prev;
                }

                delete current;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Поиск элемента по значению
    bool contains(const T& value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Вывод элементов на экран
    void print() const {
        if (empty()) {
            std::cout << "List is empty.\n";
            return;
        }

        Node* current = head;
        std::cout << "List contents: ";
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }

    // Очистка списка
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    // Проверка на пустоту
    bool empty() const {
        return size == 0;
    }

    // Получение размера списка
    size_t get_size() const {
        return size;
    }

    // Доступ к элементам по индексу
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
};

void display_menu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Initialize first element\n";
    std::cout << "2. Add element to front\n";
    std::cout << "3. Add element to back\n";
    std::cout << "4. Remove element\n";
    std::cout << "5. Search for element\n";
    std::cout << "6. Print list\n";
    std::cout << "7. Clear list\n";
    std::cout << "8. Solve the problem\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";
}

template <typename T>
void menu_loop(DoublyLinkedList<T>& list) {
    int choice;
    T value;

    while (true) {
        display_menu();
        std::cin >> choice;

        // Очистка буфера ввода
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            std::cout << "Enter value for first element: ";
            std::cin >> value;
            list.init_first(value);
            break;
        }
        case 2: {
            std::cout << "Enter value to add to front: ";
            std::cin >> value;
            list.push_front(value);
            break;
        }
        case 3: {
            std::cout << "Enter value to add to back: ";
            std::cin >> value;
            list.push_back(value);
            break;
        }
        case 4: {
            std::cout << "Enter value to remove: ";
            std::cin >> value;
            if (list.remove(value)) {
                std::cout << "Element removed successfully.\n";
            }
            else {
                std::cout << "Element not found.\n";
            }
            break;
        }
        case 5: {
            std::cout << "Enter value to search: ";
            std::cin >> value;
            if (list.contains(value)) {
                std::cout << "Element found in the list.\n";
            }
            else {
                std::cout << "Element not found.\n";
            }
            break;
        }
        case 6: {
            list.print();
            break;
        }
        case 7: {
            list.clear();
            std::cout << "List cleared.\n";
            break;
        }
        case 8: {
            if (list.empty()) {
                std::cout << "List is empty. Cannot solve the problem.\n";
                break;
            }

            size_t size = list.get_size();
            if (size % 2 != 0) {
                std::cout << "List size must be even (2n elements). Current size: " << size << "\n";
                break;
            }

            int n = size / 2;
            std::cout << "\nComparing pairs:\n";
            std::cout << std::setw(10) << "Pair" << std::setw(15) << "Elements" << std::setw(15) << "Min" << "\n";
            std::cout << "---------------------------------\n";

            T max_value = std::min(list[0], list[2 * n - 1]);
            std::cout << std::setw(10) << "1"
                << std::setw(15) << list[0] << "," << list[2 * n - 1]
                << std::setw(15) << std::min(list[0], list[2 * n - 1]) << "\n";

            for (int i = 1; i < n; ++i) {
                T current_min = std::min(list[i], list[2 * n - 1 - i]);
                if (current_min > max_value) {
                    max_value = current_min;
                }
                std::cout << std::setw(10) << i + 1
                    << std::setw(15) << list[i] << "," << list[2 * n - 1 - i]
                    << std::setw(15) << current_min << "\n";
            }

            std::cout << "---------------------------------\n";
            std::cout << "Final result (max of mins): " << max_value << "\n";
            break;
        }
        case 9: {
            std::cout << "Exiting...\n";
            return;
        }
        default: {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    }
}

int main() {
    DoublyLinkedList<double> list;

    try {
        menu_loop(list);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}