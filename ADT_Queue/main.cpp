#include <iostream>
#include "Queue.cpp"

int main() {
    Queue q;
    q.push(4);
    q.push(3);
    q.push(12);

    std::cout << "Back: " << q.back() << '\n';
    std::cout << q.currentMin() << '\n';
    std::cout << "Front  : " << q.front() << '\n';
    q.pop();
    std::cout << "Front : " << q.front() << '\n';
    std::cout << "Back: " << q.back() << '\n';

    return 0;
}
