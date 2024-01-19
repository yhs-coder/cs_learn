#include <afxwin.h>
#include <iostream>
using namespace std;

/**
	���л�����
**/

// ����֧�����л�������Ҫ��Ӻ�
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

	// ��д�麯��serialize
	virtual void Serialize(CArchive& ar);

	int m_age;
	float m_score;
	CString m_name;
};
IMPLEMENT_SERIAL(CMyDoc, CDocument, 1)

void CMyDoc::Serialize(CArchive& ar)
{
	
	if (ar.IsStoring()) {
		ar << m_age << m_score << m_name;  // ���л��������ͱ���
	} else {
		ar >> m_age >> m_score >> m_name;	// �����л��������ͱ���
	}
}


// ���л����洢��д������
void Store()
{
#if 0
	CFile file;
	file.Open("D:\\Github_cs_learn\\MFC\\MFCSerial\\MFCSerial\\serial.txt", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store, 4096);	// �鵵�����ά��������
	long age = 18;	// ��18���浽��ǰָ���λ�ã�arά���Ļ��������������ڴ棡������������ƶ���ǰָ�� ��Ӧ�ֽ���
	ar << age;
	float score = 88.8;
	ar << score;
	CString name = "zhangsan";
	ar << name; // �洢���ļ�ʱ�����ٴ洢�ַ����ĳ��ȣ������ļ�����һ���ֽ�
	ar.Close();
	file.Close();
#else
	// �Զ������͵��������л����ļ��б���
	CMyDoc data(18, 9.9, "zhangsan");
	CFile file;
	file.Open("D:\\Github_cs_learn\\MFC\\MFCSerial\\MFCSerial\\serial_object.txt", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store, 4096);
	ar << &data;  // ���л����󣬾��ǽ�����ĸ�����Ա�������л�
	ar.Close();
	file.Close();
#endif
}

// �����л������ء���������
void Load()
{
#if 0
	CFile file;
	file.Open("D:\\Github_cs_learn\\MFC\\MFCSerial\\MFCSerial\\serial.txt", CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	// �������л���һ������ʱ���ڲ����ļ������е����ݶ���arά���Ļ�������
	long age;
	ar >> age;
	float score;
	ar >> score; // �������л���������ʱ������Ҫ��Ӳ���ļ���ȡ���ݣ�ֱ�ӵ�arά����buff�ж�ȡ
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

