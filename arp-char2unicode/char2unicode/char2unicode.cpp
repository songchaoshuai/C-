// char2unicode.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <wchar.h>
#include <windows.h>
using namespace std;
 
int _tmain(int argc, _TCHAR* argv[])
{
	//���ֽ�ת�����ֽ�
	char * ptr = "����123";
	cout << "strlen(ptr)= " << strlen(ptr) <<endl;//����7=2+2+1+1+1
	//����ת������Ҫ���ֽ���
	int len1 = MultiByteToWideChar(CP_ACP, 0, ptr, -1, NULL, 0); 
	cout << "len1: " << len1 << endl;//����6=5���ַ�+1��������
	//ת��
	wchar_t * pwtr = new wchar_t[len1];
	int len2 = MultiByteToWideChar(CP_ACP, 0, ptr, -1, pwtr, len1);
	cout << "len2: " << len2 <<endl;//����6 ͬ��
	cout << "wcslen(pwtr): " << wcslen(pwtr) <<endl;//����5=5���ַ�
	setlocale(LC_ALL,"chs");
	cout << "pwtr: ";
	wcout << pwtr << endl;
	if (pwtr != NULL)
	{
		delete [] pwtr;
		pwtr = NULL;
		cout << "pwtr has been deleted!" <<endl;
	}
 
	//���ַ�ת���ֽ�
	wchar_t pwtr1[10] = L"123����";
	cout << "wcslen(pwtr1): " << wcslen(pwtr1) << endl;//����5=1+1+1+1+1
	//����ת������Ҫ���ֽ���
	int len3 = WideCharToMultiByte(CP_ACP, 0, pwtr1, -1, NULL, 0, NULL, NULL);
	cout << "len3: " << len3 <<endl;//����8=1+1+1+2+2+1
	//ת�� 
	char * ptr1 = new char[len3];
	int len4 = WideCharToMultiByte(CP_ACP, 0 ,pwtr1, -1 , ptr1, len3, NULL, NULL);
	cout << "len4: " << len4 << endl;//����8 ͬ�� 
	cout << "strlen(ptr1): " << strlen(ptr1) << endl;//����7 ������������
	cout << "ptr1: " << ptr1 <<endl;//���"123����"
	if (ptr1 != NULL)
	{
		delete [] ptr1;
		pwtr = NULL;
		cout << "ptr1 has been deleted!" <<endl;
	}
	int i;
	cin>>i;
	return 0;
}

