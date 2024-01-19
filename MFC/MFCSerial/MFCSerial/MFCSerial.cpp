#include <afxwin.h>
#include <iostream>
using namespace std;

/**
	序列化机制
**/

// 类内支持序列化机制需要添加宏
class CMyDoc : public CDocument
{
	DECLARE_SERIAL(CMyDoc)
public:
	CMyDoc(int age = 0, float score = 0.0, CString name = "")
		: m_age(age)
		, m_score(score)
		, m_name(name) 
	{
		cout << "name: " << name << " ,m_name: " << m_name << endl;
	}

	// 重写虚函数serialize
	virtual void Serialize(CArchive& ar);

	int m_age;
	float m_score;
	CString m_name;
};
IMPLEMENT_SERIAL(CMyDoc, CDocument, 1)

void CMyDoc::Serialize(CArchive& ar)
{
	
	if (ar.IsStoring()) {
		ar << m_age << m_score << m_name;  // 序列化基本类型变量
	} else {
		ar >> m_age >> m_score >> m_name;	// 反序列化基本类型变量
	}
}


// 序列化（存储、写）数据
void Store()
{
#if 0
	CFile file;
	file.Open("D:\\Github_cs_learn\\MFC\\MFCSerial\\MFCSerial\\serial.txt", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store, 4096);	// 归档类对象，维护缓冲区
	long age = 18;	// 将18保存到当前指向的位置（ar维护的缓冲区（即堆区内存！）），并向后移动当前指向 相应字节数
	ar << age;
	float score = 88.8;
	ar << score;
	CString name = "zhangsan";
	ar << name; // 存储到文件时，会再存储字符串的长度，导致文件增加一个字节
	ar.Close();
	file.Close();
#else
	// 自定义类型的数据序列化到文件中保存
	CMyDoc data(18, 9.9, "zhangsan");
	CFile file;
	file.Open("D:\\Github_cs_learn\\MFC\\MFCSerial\\MFCSerial\\serial_object.txt", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store, 4096);
	ar << &data;  // 序列化对象，就是将对象的各个成员变量序列化
	ar.Close();
	file.Close();
#endif
}

// 反序列化（加载、读）数据
void Load()
{
#if 0
	CFile file;
	file.Open("D:\\Github_cs_learn\\MFC\\MFCSerial\\MFCSerial\\serial.txt", CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	// 当反序列化第一个数据时，内部将文件中所有的数据读入ar维护的缓冲区中
	long age;
	ar >> age;
	float score;
	ar >> score; // 当反序列化后续数据时，不需要到硬盘文件读取数据，直接到ar维护的buff中读取
	CString name;
	ar >> name;
	cout << age << " " << score << " " << name;
	ar.Close();
	file.Close();
#else
	CFile file;
	file.Open("D:\\Github_cs_learn\\MFC\\MFCSerial\\MFCSerial\\serial_object.txt",CFile::modeRead);
	CArchive ar(&file, CArchive::load, 4096);
	CMyDoc* pdata = NULL; 
	ar >> pdata;
	ar.Close();
	file.Close();
	cout << pdata->m_age << " " << pdata->m_score << " " << pdata->m_name << endl;
#endif
}
int main()
{
	Store();
	Load();
	return 0;
}

