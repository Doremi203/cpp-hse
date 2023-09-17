#pragma once

#include <cstdint>

struct Node {
    int32_t value;
    Node* next;
    Node(int32_t value, Node* next);
};

class Queue {
private:
    Node* front_;
    Node* tail_;
    int32_t size_;

public:
    Queue();

    ~Queue();

    void Push(int32_t value);

    void Pop();

    int32_t Front() const;

    int32_t Size() const;

    void Clear();

    bool Empty() const;
};
