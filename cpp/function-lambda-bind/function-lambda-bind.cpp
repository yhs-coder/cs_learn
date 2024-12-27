//
// Created by yhs on 2024-12-21.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <thread>
#include <functional>

using std::cout;
using std::endl;

// 定义普通函数
int add(int a, int b) {
    return a + b;
}

struct Multiply {
    int operator()(int a, int b) {
        return a * b;
    }
};

// 定义函数指针类型的变量
int (*func_ptr)(int, int);

// 1. 函数指针
void test_func_ptr() {
    // 函数指针指向add函数并调用
#if 0
    // 方式一:
    // 函数名是函数的地址（类似数组名指的是数组的首地址）
    // 调用函数指针时可以直接调用传参，不需解引用，因为函数指针调用时，编译器会直接找到函数指针指向的函数，
    // 然后再调用该函数传参
    func_ptr = add;
    int result = func_ptr(1,2);
#else
    // 方式二：传统写法
    func_ptr = &add;
    int result = (*func_ptr)(1, 2);
#endif
    cout << "result: " << result << endl;
}


// 2. 仿函数/函数对象 - functor
// 概念：重载了operator()的类和结构体的实例

// 2.1 定义一个仿函数类
struct Adder {
    Adder(int value) : to_add(value) {}

    // 重载()运算符
    int operator()(int x) const {
        return x + to_add;
    }

    void add(int x) {
        to_add += x;
    }

    ~Adder() {
        cout << "Adder::~Adder()" << endl;
    }

    int to_add;
};

// 2.2 仿函数复杂操作： 实现一个可变的仿函数
struct Accumulator {
    Accumulator() : sum(0) {}

    void operator()(int x) {
        sum += x;
    }

    int sum;
};

// 2.3 仿函数：判断一个数是否大于某个阈值
struct IsGreaterThan {
    IsGreaterThan(int t) : threshold(t) {}

    bool operator()(int x) const {
        return threshold < x;
    }

    int threshold;
};

// 2.4 仿函数与模板结合
// 定义通用比较仿函数
template<typename T>
struct Compare {
    bool operator()(const T &a, const T &b) {
        return a < b;
    }
};

void test_functor() {
    // 2.1 定义与基本使用
    Adder add(1);
    cout << "1 + 2 = " << add(2) << endl;
    // 2.2 使用可变的仿函数
    Accumulator acc;
    acc(10);
    acc(20);
    acc(30);
    cout << "sum = " << acc.sum << endl;

    // 2.3 使用仿函数的标准库算法
    std::vector<int> numbers = {1, 4, 3, 10, 2};
    // 使用仿函数进行筛选
    IsGreaterThan g(5);
    auto it = std::find_if(numbers.begin(), numbers.end(), g);
    if (it != numbers.end()) {
        cout << "found :" << *it << endl;
    } else {
        cout << "not found!" << endl;
    }

    //2.4 使用通用比较的仿函数
    std::vector<double> numbers2 = {1.1, 4.1, 3.1, 10.1, 2.1};
    std::sort(numbers2.begin(), numbers2.end(), Compare<double>());
    cout << "after sorting: ";
    for (auto num: numbers2) {
        cout << num << " ";
    }
    cout << endl;
}

// 3. lambda表达式
class Processor {
public:
    Processor(int threshold) : _threshold(threshold) {}

    void process(std::vector<int> &data) {
        cout << "before process data: " << endl;
        for (auto num: data)
            cout << num << " ";
        cout << endl;

        auto new_end = std::remove_if(data.begin(), data.end(), [this](int n) -> bool {
            return n < _threshold;
        });
        data.erase(new_end, data.end());
        cout << "after process data: " << endl;
        for (auto num: data)
            cout << num << " ";
        cout << endl;
    }

private:
    int _threshold;
};


void test_lambda() {
    int threshold = 5;
    // 6  10 8  1 3 2
    std::vector<int> numbers = {1, 6, 3, 10, 8, 2};
    auto new_end = remove_if(numbers.begin(), numbers.end(), [threshold](int x) {
        return x < threshold;
    });


    numbers.erase(new_end, numbers.end());
    for (auto num: numbers) {
        cout << num << " ";
    }
    cout << endl;

    // !!! 使用值捕获方式，改变外部变量内容
    int temp = 10;
    int *ptemp = &temp;
    // 通过传入指针，解引用后间接改变外部变量
    auto lambda = [ptemp](int x) {
        *ptemp *= x;
    };


    // 特殊场景：lambda表达式捕获了普通指针时，如果在其他线程也使用该指针并且回收了内存，
    //         可能会导致非法访问内存，导致程序崩溃或者产生不可预测的结果。这是因为lambda表达式在执行时可能会访问已经被回收的内存。
    // 最佳操作：异步操作下，lambda表达式配合智能指针
    std::thread t1;
    {
        // 在创建lambda表达式捕获智能指针，智能指针的引用计数加一。在调用lambda时不在再增加引用计数。
        auto add_ptr = std::make_shared<Adder>(10);
        auto lambda2 = [add_ptr](int x) {
            cout << "begin lambda2 use count: " << add_ptr.use_count() << endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            add_ptr->add(x);
            cout << "end lambda use_count: " << add_ptr.use_count() << endl;
        };
        // 将lambda表达式传给线程，线程内部会依次将lambda表达式所捕获的变量，以值的方式拷贝给在线程内部的成员（即将值拷贝到线程）
        t1 = std::thread(lambda2, 5);
        cout << "before } use_count: " << add_ptr.use_count() << endl;
    }
    t1.join();

    // lambda表达式捕获成员变量，搭配标准库算法
    Processor p(5);
    std::vector<int> data = {1, 6, 3, 10, 8, 2};
    p.process(data);
}

void test_function() {
    // 1. 封装普通函数
    std::function<int(int, int)> func1 = add;
    cout << "Add : " << func1(1,1) << endl;

    // 2. 封装函数对象/仿函数
    Multiply multiply;
    std::function<int(int, int)> func2 = multiply;
    cout << "Multiply : " << func2(1,1) << endl;

    // 3. 封装lambda表达式
    std::function<int(int,int)> func3 = [](int a, int b) {
        return a - b;
    };
    cout << "subtract : " << func3(2,1) << endl;
}

void test_bind(){
    // 1. std::bind绑定部分参数
    auto bind_add = std::bind(add, 5, std::placeholders::_1);
    cout << "bind_add : 5 + 10 =  " << bind_add(10) << endl;
}


int main() {
//    test_func_ptr();
//    test_functor();
//    test_lambda();
//    test_function();
    test_bind();

    return 0;
}