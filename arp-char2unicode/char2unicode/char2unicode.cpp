// char2unicode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <wchar.h>
#include <windows.h>
using namespace std;
 
int _tmain(int argc, _TCHAR* argv[])
{
	//多字节转换宽字节
	char * ptr = "测试123";
	cout << "strlen(ptr)= " << strlen(ptr) <<endl;//返回7=2+2+1+1+1
	//计算转换后需要的字节数
	int len1 = MultiByteToWideChar(CP_ACP, 0, ptr, -1, NULL, 0); 
	cout << "len1: " << len1 << endl;//返回6=5个字符+1个结束符
	//转换
	wchar_t * pwtr = new wchar_t[len1];
	int len2 = MultiByteToWideChar(CP_ACP, 0, ptr, -1, pwtr, len1);
	cout << "len2: " << len2 <<endl;//返回6 同上
	cout << "wcslen(pwtr): " << wcslen(pwtr) <<endl;//返回5=5个字符
	setlocale(LC_ALL,"chs");
	cout << "pwtr: ";
	wcout << pwtr << endl;
	if (pwtr != NULL)
	{
		delete [] pwtr;
		pwtr = NULL;
		cout << "pwtr has been deleted!" <<endl;
	}
 
	//宽字符转多字节
	wchar_t pwtr1[10] = L"123测试";
	cout << "wcslen(pwtr1): " << wcslen(pwtr1) << endl;//返回5=1+1+1+1+1
	//计算转换后需要的字节数
	int len3 = WideCharToMultiByte(CP_ACP, 0, pwtr1, -1, NULL, 0, NULL, NULL);
	cout << "len3: " << len3 <<endl;//返回8=1+1+1+2+2+1
	//转换 
	char * ptr1 = new char[len3];
	int len4 = WideCharToMultiByte(CP_ACP, 0 ,pwtr1, -1 , ptr1, len3, NULL, NULL);
	cout << "len4: " << len4 << endl;//返回8 同上 
	cout << "strlen(ptr1): " << strlen(ptr1) << endl;//返回7 不包含结束符
	cout << "ptr1: " << ptr1 <<endl;//输出"123测试"
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

