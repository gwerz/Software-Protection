#if !defined __NT77API_H__
#define __NT77API_H__

#ifdef __cplusplus 
extern "C" 
{
#endif	

 	 long  NTFindFirst(char appName[32]);

	 long  NTLogin(char * password);
	
	 long  NTGetHardwareID(char * hardwareID);

	 long  NTRead(long address, long length, unsigned char * pBuffer);

	 long  NTWrite(long address, long length, unsigned char * pBuffer);
	
	 long  NTLogout();
	

#ifdef __cplusplus 
}

#endif



#endif