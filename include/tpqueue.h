// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>

template<typename T>
class TPQueue {
  private:
    struct Node {
        T data;
        Node next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) { }
    };
    Node* head; 

public:
    TPQueue() : head(nullptr) { }
    ~TPQueue() {
        while (!empty()) {
            pop();
        }
    }
    bool empty() const {
        return head == nullptr;
    }
    void push(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr || value.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->data.prior >= value.prior) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    void pop() {
        if (empty()) {
            throw std::underflow_error("Попытка извлечь элемент из пустой очереди");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    T& front() {
        if (empty()) {
            throw std::underflow_error("Попытка обратиться к элементу в пустой очереди");
        }
        return head->data;
    }
    const T& front() const {
        if (empty()) {
            throw std::underflow_error("Попытка обратиться к элементу в пустой очереди");
        }
        return head->data;
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
