#pragma once

template <typename T>
class DoublyList {
private:
    struct Node {
        T     data;
        Node* prev;
        Node* next;
        Node(const T& value, Node* p = nullptr, Node* n = nullptr)
            : data(value), prev(p), next(n) {
        }
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int sz = 0;

public:
    class Iterator {
    private:
        Node* current = nullptr;
        Iterator(Node* ptr) {
            current = ptr;
        }
        friend class DoublyList<T>;
    public:

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return current;
        }
        Iterator operator++(int) {
            auto temp = current;
            current = current->next;
            return temp;
        }

        Iterator& operator--() {
            current = current->prev;
            return current;
        }
        Iterator operator--(int) {
            auto temp = current;
            current = current->prev;
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    DoublyList() {}
    ~DoublyList() {
        while (head) {
            auto temp = head;
            head = head->next;
            delete temp;
        }
    }
    DoublyList(const DoublyList& other) {
        for (auto i = other.begin(); i != other.end(); i++)
            this->push_back(*i);
    }
    DoublyList& operator=(const DoublyList& other) {
        this->~DoublyList();
        for (auto i = other.begin(); i != other.end(); i++)
            this->push_back(*i);
        return *this;
    }

    bool empty() const {
        return head == tail == nullptr;
    }
    int size() const {
        return sz;
    }

    T& front() {
        return head->data;
    }
    const T& front() const {
        return head->data;
    }

    T& back() {
        return tail->data;
    }
    const T& back() const {
        return tail->data;
    }

    T& operator[](int i) {
        auto temp = head;
        for (int idx = 0; idx < i; idx++)
            temp = temp->next;
        return temp->data;
    }
    const T& operator[](int i) const {
        auto temp = head;
        for (auto idx = begin(); idx != begin() + i; idx++)
            temp = temp->next;
        return temp->data;
    }

    void push_front(const T& value) {
        if (!head) {
            head = tail = new Node(value);
        }
        else {
            Node* temp = head;
            head = new Node(value, nullptr, head);
            temp->prev = head;
        }
        sz++;
    }
    void push_back(const T& value) {
        if (!head)
            head = tail = new Node(value);
        else {
            auto temp = tail;
            tail = new Node(value, tail, nullptr);
            temp->next = tail;
        }
        sz++;
    }

    void pop_front() {
        if (!head)
            return;
        auto temp = head;
        head->next->prev = nullptr;
        head = head->next;
        delete temp;
        sz--;
    }
    void pop_back() {
        if (!head)
            return;
        auto temp = tail;
        tail->prev->next = nullptr;
        tail = tail->prev;
        delete temp;
        sz--;
    }

    void insert_at(Iterator pos, const T& value) {
        if (!head) {
            push_back(value);
        }

        if (pos == begin())
            return push_front(value);
        if (pos.current == tail)
            return push_back(value);

        Node* temp = new Node(value, pos.current->prev, pos.current);
        pos.current->prev->next = temp;
        pos.current->prev = temp;
    }
    void erase_at(Iterator pos) {
        if (!head)
            return;
        if (pos == begin())
            return pop_front();
        if (pos.current == tail)
            return pop_back();
        auto temp = pos.current;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }

    Iterator begin() const {
        return Iterator(head);
    }
    Iterator end() const {
        return Iterator(nullptr);
    }
    Iterator rbegin() const {
        return Iterator(tail);
    }
    Iterator rend() const {
        return Iterator(nullptr);
    }
};
