#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <iomanip>

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
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    DoublyLinkedList(std::initializer_list<T> init_list) : head(nullptr), tail(nullptr), size(0) {
        for (const auto& item : init_list) {
            push_back(item);
        }
    }

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

    ~DoublyLinkedList() {
        clear();
    }

    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

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

    void init_first(const T& value) {
        if (empty()) {
            head = tail = new Node(value);
            size = 1;
        }
        else {
            std::cout << "List is not empty. First element already exists.\n";
        }
    }

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

    bool empty() const {
        return size == 0;
    }

    size_t get_size() const {
        return size;
    }

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

    // Public iterator-like interface for solving the problem
    class Iterator {
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        T& operator*() { return current->data; }
        Iterator& operator++() { current = current->next; return *this; }
        Iterator& operator--() { current = current->prev; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    Iterator rbegin() { return Iterator(tail); }
    Iterator rend() { return Iterator(nullptr); }
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

void handle_init_first(DoublyLinkedList<double>& list) {
    double value;
    std::cout << "Enter value for first element: ";
    std::cin >> value;
    list.init_first(value);
}

void handle_push_front(DoublyLinkedList<double>& list) {
    double value;
    std::cout << "Enter value to add to front: ";
    std::cin >> value;
    list.push_front(value);
}

void handle_push_back(DoublyLinkedList<double>& list) {
    double value;
    std::cout << "Enter value to add to back: ";
    std::cin >> value;
    list.push_back(value);
}

void handle_remove(DoublyLinkedList<double>& list) {
    double value;
    std::cout << "Enter value to remove: ";
    std::cin >> value;
    if (list.remove(value)) {
        std::cout << "Element removed successfully.\n";
    }
    else {
        std::cout << "Element not found.\n";
    }
}

void handle_contains(DoublyLinkedList<double>& list) {
    double value;
    std::cout << "Enter value to search: ";
    std::cin >> value;
    if (list.contains(value)) {
        std::cout << "Element found in the list.\n";
    }
    else {
        std::cout << "Element not found.\n";
    }
}

void handle_print(const DoublyLinkedList<double>& list) {
    list.print();
}

void handle_clear(DoublyLinkedList<double>& list) {
    list.clear();
    std::cout << "List cleared.\n";
}

void solve_problem(DoublyLinkedList<double>& list) {
    if (list.empty()) {
        std::cout << "List is empty. Cannot solve the problem.\n";
        return;
    }

    size_t size = list.get_size();
    if (size % 2 != 0) {
        std::cout << "List size must be even (2n elements). Current size: " << size << "\n";
        return;
    }

    int n = size / 2;
    std::cout << "\nComparing pairs:\n";
    std::cout << std::setw(10) << "Pair" << std::setw(15) << "Elements" << std::setw(15) << "Min" << "\n";
    std::cout << "---------------------------------\n";

    auto front = list.begin();
    auto back = list.rbegin();
    double max_value = std::min(*front, *back);

    std::cout << std::setw(10) << "1"
        << std::setw(15) << *front << "," << *back
        << std::setw(15) << std::min(*front, *back) << "\n";

    for (int i = 1; i < n; ++i) {
        ++front;
        --back;

        double current_min = std::min(*front, *back);
        if (current_min > max_value) {
            max_value = current_min;
        }
        std::cout << std::setw(10) << i + 1
            << std::setw(15) << *front << "," << *back
            << std::setw(15) << current_min << "\n";
    }

    std::cout << "---------------------------------\n";
    std::cout << "Final result (max of mins): " << max_value << "\n";
}

void menu_loop(DoublyLinkedList<double>& list) {
    int choice;

    while (true) {
        display_menu();

        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: handle_init_first(list); break;
        case 2: handle_push_front(list); break;
        case 3: handle_push_back(list); break;
        case 4: handle_remove(list); break;
        case 5: handle_contains(list); break;
        case 6: handle_print(list); break;
        case 7: handle_clear(list); break;
        case 8: solve_problem(list); break;
        case 9: std::cout << "Exiting...\n"; return;
        default: std::cout << "Invalid choice. Please try again.\n"; break;
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