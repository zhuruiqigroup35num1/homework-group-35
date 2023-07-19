
#ifndef __AES_H
#define __AES_H

#ifdef __cplusplus
extern "C" {
#endif

#define AES_KEY_LENGTH	128


#define AES_MODE_ECB	0				
#define AES_MODE_CBC	1				
#define AES_MODE		AES_MODE_CBC



	void AES_Init(const void* pKey);

	
	void AES_Encrypt(const unsigned char* pPlainText, unsigned char* pCipherText,
		unsigned int nDataLen, const unsigned char* pIV);

	
	void AES_Decrypt(unsigned char* pPlainText, const unsigned char* pCipherText,
		unsigned int nDataLen, const unsigned char* pIV);


#ifdef __cplusplus
}
#endif


#endif	// __AES_H

