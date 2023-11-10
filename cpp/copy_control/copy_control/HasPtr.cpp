#include "HasPtr.h"

#if 0
HasPtr& 
HasPtr::operator=(const HasPtr& rhs)
{
    // 检查自赋值操作
    if (this == &rhs) {
        return *this;
    }

    auto newp = new std::string(*rhs._ps);   // 拷贝底层string的内容
    delete _ps;  //释放旧内存
    _ps = newp;  // 将右侧运算对象数据拷贝到本对象
    _i = rhs._i;
    return *this;
}
#endif

// 在赋值运算符中使用swap
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
    // 使用标准库的swap
    using std::swap;
    swap(lhs._ps, rhs._ps);
    swap(lhs._i, rhs._i);

}
