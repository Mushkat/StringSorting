#include <stdexcept>
#include <limits>

class Stack {
private:
    int *data;
    int *min_data;
    size_t capacity;
    size_t size;

    void resize() {
        size_t new_capacity = capacity * 2;
        int *new_data = new int[new_capacity];
        int *new_min_data = new int[new_capacity];

        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
            new_min_data[i] = min_data[i];
        }

        delete[] data;
        delete[] min_data;

        data = new_data;
        min_data = new_min_data;
        capacity = new_capacity;
    }

public:
    Stack() : capacity(10), size(0) {
        data = new int[capacity];
        min_data = new int[capacity];
    }

    ~Stack() {
        delete[] data;
        delete[] min_data;
    }

    void push(int value) {
        if (size == capacity) {
            resize();
        }
        data[size] = value;

        if (size == 0) {
            min_data[size] = value;
        } else {
            min_data[size] = std::min(value, min_data[size - 1]);
        }

        ++size;
    }

    void pop() {
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        --size;
    }

    int top() const {
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return data[size - 1];
    }

    bool empty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    int getMin() const {
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return min_data[size - 1];
    }
};
