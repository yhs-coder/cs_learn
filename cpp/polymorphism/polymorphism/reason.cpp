#include <iostream>
#include <string>

// ������
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
�������ֳ���������չ��ά�����ѣ�����޸Ĺ��ܻ�����չ������Ҫ��Դ����������޸ģ�
�������������һ������ԭ��:����ԭ��(���޸Ĺرգ�����չ����)
*/


//�������
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

//�ӷ�������
class PlusCaculator : public AbstractCaculator {
public:
	virtual int get_result() {
		return a_ + b_;
	}
};

//����������
class MinusCaculator : public AbstractCaculator {
public:
	virtual int get_result() {
		return a_ - b_;
	}
};

//�˷�������
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
	std::cout << "��������" << caculator->get_result() << std::endl;
	delete caculator;
}

int main()
{
	do_bussiness(new PlusCaculator);
	do_bussiness(new MinusCaculator);
	do_bussiness(new MultipliesCaculator);
	return 0;
}








