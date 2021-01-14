#include <iostream>
#include <chrono>
#include <thread>

#include "Event.h"
#include "Observer.h"


void freeFunction1() {
    std::cout << "freeFunction1 " << std::endl;
}

void freeFunction2(int i) {
    std::cout << "freeFunction2, i = " << i << std::endl;
}

constexpr auto lambda1 = []() { std::cout << "lambda1" << std::endl; };
constexpr auto lambda2 = [](int i) { std::cout << "lambda2 " << i << ")" << std::endl; };


class Test : public Observer {
    std::string _name;
public:
    explicit Test(std::string name) : _name(std::move(name)) {};

    Test(const Test &other) = default;

    Test(Test &&other) = default;

    ~Test() = default;

    void test1() {
        std::cout << "test1 (name: " << this->_name << ")" << std::endl;
    }

    void test2(int val) {
        std::cout << "test2 (name: " << this->_name << "), i = " << val << std::endl;
    }

    static void testStatic(int i) {
        std::cout << "test static: i = " << i << std::endl;
    }
};

int main() {
    Test t1("t1");
    auto t2 = new Test("t2");

    Event e;
    e.connect(&freeFunction1);
    e.connect(&t1, &Test::test1);
    e.connect(t2, &Test::test1);
    e();

    Event<int> e2;
    e2.connect(&freeFunction2);
    e2.connect(&Test::testStatic);
    e2.connect(&t1, &Test::test2);
    e2.connect(t2, &Test::test2);
    e2(5);

    std::cin.get();
    return 0;
}
