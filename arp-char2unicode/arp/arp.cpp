// arp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Winsock2.h>
#include <iphlpapi.h>
#include <iostream>
#include <tchar.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <winnls.h>
#include<WINERROR.H>
#pragma comment (lib, "Ws2_32")
#pragma comment (lib, "iphlpapi")
using namespace std;

////////////////////////////////////////////////////////////
//description: upate the ip to the right mac in the index net interface
//input:
//index:   the net interface index
//ip:        the ip 
//mac:    the mac address(6 byte)
void updateARP( const int index,const char * ip,const char * mac)
{
	MIB_IPNETROW_LH aa;
	int ret=0;
	in_addr addr;
    aa.dwIndex=index;
	addr.S_un.S_addr=inet_addr(ip);
	aa.dwAddr=addr.S_un.S_addr;
	aa.dwPhysAddrLen=6;
	memset(aa.bPhysAddr,0,6);
	memcpy(aa.bPhysAddr,mac,6);
	aa.dwType=4;
    DeleteIpNetEntry(&aa);
    CreateIpNetEntry(&aa);
}

int _tmain(int argc, _TCHAR* argv[])
{
	PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
    ULONG outBufLen = 15000;
    DWORD dwRetVal = 0;
    char packet_filter[] = "ip and udp";
    u_int netmask;
    int res;
    const u_char *pkt_data;
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX | GAA_FLAG_INCLUDE_GATEWAYS;
	ULONG family = AF_INET;
	/*get all the interface in the system*/
    do
    {
        pAddresses = (IP_ADAPTER_ADDRESSES *)malloc(outBufLen);
        if (pAddresses == NULL)
		{
            return 0;
		}
        dwRetVal = GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);
        if (dwRetVal == ERROR_BUFFER_OVERFLOW)
        {
            free(pAddresses);
            pAddresses = NULL;
        }
        else
            break;
    } while (dwRetVal == ERROR_BUFFER_OVERFLOW);
    
	pCurrAddresses=pAddresses;
	do{
	cout<<"+++++++++++++++++++++++++++++++"<<endl;
	cout<<pCurrAddresses->AdapterName<<endl;
	cout<<pCurrAddresses->FriendlyName<<endl;
	cout<<pCurrAddresses->Ipv6IfIndex<<endl;
	cout<<"+++++++++++++++++++++++++++++++"<<endl;
	pCurrAddresses=pCurrAddresses->Next;
	}while (pCurrAddresses);
////////////////////////////////////////////////////////////////////////////
	char * mac="abcdeg";
    updateARP(7,"192.168.1.201",mac);
	int i;
	cin>>i;

	return 0;
}
