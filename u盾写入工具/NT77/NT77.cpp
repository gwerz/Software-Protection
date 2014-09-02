// NT77.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NT77Api.h"

int main(int argc, char* argv[])
{
	printf("Hello NT77!\n");

	long nRet = 0;
	char hwID[64] ={0};	
	
	nRet = NTFindFirst("NJUSNIS");
	if(0 != nRet)
	{
		printf("NT77 is not found! return %d\n ", nRet);
		return 1;
	}

	nRet = NTLogin("5d77a67b65d59b5ceec9a7e3cc068e6c");
	if( 0 != nRet)
	{
		printf("Failed to login! return %d\n ", nRet);
		return 2;
	}

//	nRet = NTGetHardwareID(hwID);
//	if( 0 != nRet)
//	{
//		printf("Failed to get hardware id! return %d\n ", nRet);
//		return 3;
//	}

	unsigned char data[128] ={0};
	for(int i = 0 ; i  <128 ; i ++)
	{
		data[i] = i;
	}

	nRet = NTWrite(0, 128, data);
	if( 0 != nRet)
	{
		printf("Failed to write data ! return %d\n ", nRet);
		return 4;
	}

	nRet = NTRead(0, 128, data);
	if( 0 != nRet)
	{
		printf("Failed to read data ! return %d\n ", nRet);
		return 4;
	}

	nRet = NTLogout();
	if( 0 != nRet)
	{
		printf("Failed to log out ! return %d\n ", nRet);
		return 5;
	}

	printf("Finished!\n");

	return 0;
}

