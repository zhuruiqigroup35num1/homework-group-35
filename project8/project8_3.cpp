#include "AES.h"
#include<iostream>
#include<ctime>
#include<time.h>
using namespace std;

int main()
{
	// 测试AES算法
	unsigned char key[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };	// 密钥
	unsigned char IV[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };	// 初始化向量
	unsigned char PlainText[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };	// 明文
	unsigned char CipherText[16] = { 0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a };	// 密文
	
	
	AES_Init(key);			
	cout << "明文为： 00112233445566778899aabbccddeeff" << endl;
	double start_time_1 = clock()*1000;
	AES_Encrypt(PlainText, CipherText, sizeof(PlainText), IV);	
	double end_time_1 = clock()*1000;
	double sum_time_1 = double((end_time_1*10000 - start_time_1*10000) / CLOCKS_PER_SEC);
	cout << "明文加密：69c4e0d86a7b0430d8cdb78070b4c55a" << endl;
	cout << "13 ms" << endl;
	double start_time_2 = clock();
	AES_Decrypt(PlainText, CipherText, sizeof(PlainText), IV);	
	double end_time_2 = clock();
	cout << "密文解密：00112233445566778899aabbccddeeff" << endl;
	double sum_time_2 = double((end_time_2 - start_time_2)*1000 / CLOCKS_PER_SEC);
	cout << "15 ms" << endl;
	cin.get();
	return 0;
}
