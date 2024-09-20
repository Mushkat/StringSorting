#include "Stack.cpp"


class Queue {
public:
    Queue() = default;

    void push(int value) {
        pushStack.push(value);
    }

    void pop() {
        if (popStack.empty()) {
            shiftPop();
        }
        if (!popStack.empty()) {
            popStack.pop();
        }
    }

    int front() {
        if (popStack.empty()) {
            shiftPop();
        }
        if (popStack.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return popStack.top();
    }

    int back() {
        if (pushStack.empty()) {
            shiftPush();
        }
        if (pushStack.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return pushStack.top();
    }


    bool empty() const {
        return pushStack.empty() && popStack.empty();
    }

    int currentMin() const {
        if (pushStack.empty() && popStack.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        if (pushStack.empty()) {
            return popStack.getMin();
        }
        if (popStack.empty()) {
            return pushStack.getMin();
        }
        return std::min(pushStack.getMin(), popStack.getMin());
    }

private:
    Stack pushStack;
    Stack popStack;

    void shiftPop() {
        while (!pushStack.empty()) {
            popStack.push(pushStack.top());
            pushStack.pop();
        }
    }
    void shiftPush() {
        while (!popStack.empty()) {
            pushStack.push(popStack.top());
            popStack.pop();
        }
    }
};