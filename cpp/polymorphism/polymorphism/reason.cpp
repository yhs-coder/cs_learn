#include <iostream>
#include <string>

// 计算器
class Caculator {
public:
	void setA(int a) {
		this->a_ = a;
	}
	void setB(int b) {
		this->b_ = b;
	}
	void setOperator(std::string oper) {
		this->operator_ = oper;
	}
	int get_result() {

		if (this->operator_ == "+") {
			return a_ + b_;
		}
		else if (this->operator_ == "-") {
			return a_ - b_;
		}
		else if (this->operator_ == "*") {
			return a_ * b_;
		}
		else if (this->operator_ == "/") {
			return a_ / b_;
		}
	}
private:
	int a_;
	int b_;
	std::string operator_;
};

/*
上面这种程序不利于扩展，维护困难，如果修改功能或者扩展功能需要在源代码基础上修改！
面向对象程序设计一个基本原则:开闭原则(对修改关闭，对扩展开放)
*/


//抽象基类
class AbstractCaculator {
public:
	void setA(int a) {
		this->a_ = a;
	}
	virtual void setB(int b) {
		this->b_ = b;
	}
	virtual int get_result() = 0;

protected:
	int a_;
	int b_;
	std::string operator_;
};

//加法计算器
class PlusCaculator : public AbstractCaculator {
public:
	virtual int get_result() {
		return a_ + b_;
	}
};

//减法计算器
class MinusCaculator : public AbstractCaculator {
public:
	virtual int get_result() {
		return a_ - b_;
	}
};

//乘法计算器
class MultipliesCaculator : public AbstractCaculator {
public:
	virtual int get_result() {
		return a_ * b_;
	}
};

void do_bussiness(AbstractCaculator* caculator) {
	int a = 10;
	int b = 20;
	caculator->setA(a);
	caculator->setB(b);
	std::cout << "计算结果：" << caculator->get_result() << std::endl;
	delete caculator;
}

int main()
{
	do_bussiness(new PlusCaculator);
	do_bussiness(new MinusCaculator);
	do_bussiness(new MultipliesCaculator);
	return 0;
}








