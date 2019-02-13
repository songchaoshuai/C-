// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <time.h>
#include <ctime>
#include <iostream>
#include <fstream>

#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Sensapi.lib")
using namespace std;
static std::fstream outfile2;
int main(int argc, char argv[])
{
	//outfile2.open("D:\\netstat.dat", ios::binary | ios::app | ios::out);
	outfile2.open("netstat.dat", ios::binary | ios::app | ios::out);
	DWORD dw;
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量

	/*
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间
	printf("年：%d\n", t.tm_year + 1900);
	printf("月：%d\n", t.tm_mon + 1);
	printf("日：%d\n", t.tm_mday);
	printf("周：%d\n", t.tm_wday);
	printf("一年中：%d\n", t.tm_yday);
	printf("时：%d\n", t.tm_hour);
	printf("分：%d\n", t.tm_min);
	printf("秒：%d\n", t.tm_sec);
	*/
	while (1)
	{
		Sleep(1000);
		time(&now);      //获取系统日期和时间
		localtime_s(&t, &now);   //获取当地日期和时间
		if (!IsNetworkAlive(&dw))
		{
			// error or no connection
			DWORD const e = GetLastError();
			if (e == ERROR_SUCCESS)
			{
				outfile2 << t.tm_year<<"-"<< t.tm_mon << "-" << t.tm_mday << "  " << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "  " << "No connection!" << endl;
			}
		}
		else
		{
			outfile2 << t.tm_year << "-" << t.tm_mon << "-" << t.tm_mday << "  " << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "  " << "Connected to network!" << endl;
			if (dw == NETWORK_ALIVE_LAN)
			{
				//The computer has one or more LAN cards that are active
				outfile2 << t.tm_year << "-" << t.tm_mon << "-" << t.tm_mday << "  " << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "  "<< "Connected to lan network!" << endl;
			}
			else if (dw == NETWORK_ALIVE_WAN)
			{
				// The computer has one or more active RAS connections.
				outfile2 << t.tm_year << "-" << t.tm_mon << "-" << t.tm_mday << "  " << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "  " << "Connected to wan network!" << endl;
			}
			else
			{
				//invalid flag
				outfile2 << t.tm_year << "-" << t.tm_mon << "-" << t.tm_mday << "  " << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "  " << "Connected to invalid network!" << endl;
			}
		}
		outfile2.flush();
	}
	outfile2.close();
}
