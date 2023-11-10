#include "HasPtr.h"

#if 0
HasPtr& 
HasPtr::operator=(const HasPtr& rhs)
{
    // ����Ը�ֵ����
    if (this == &rhs) {
        return *this;
    }

    auto newp = new std::string(*rhs._ps);   // �����ײ�string������
    delete _ps;  //�ͷž��ڴ�
    _ps = newp;  // ���Ҳ�����������ݿ�����������
    _i = rhs._i;
    return *this;
}
#endif

// �ڸ�ֵ�������ʹ��swap
HasPtr& HasPtr::operator= (HasPtr rhs)
{
    std::cout << "rhs._ps = " << rhs._ps << std::endl;
    swap(*this, rhs);
    return *this;
}

std::string* HasPtr::get_ps()
{
    return _ps;
}

inline
void swap(HasPtr& lhs, HasPtr& rhs)
{
    // ʹ�ñ�׼���swap
    using std::swap;
    swap(lhs._ps, rhs._ps);
    swap(lhs._i, rhs._i);

}
