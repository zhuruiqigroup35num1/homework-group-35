#include<iostream>
#include <stdint.h>
#include<time.h> 
using namespace std;

// S盒
uint8_t S[256] = {
0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

// AES-128轮常量
uint32_t rcon[10] = {
	0x01000000UL, 0x02000000UL, 0x04000000UL, 0x08000000UL, 0x10000000UL,
	0x20000000UL, 0x40000000UL, 0x80000000UL, 0x1B000000UL, 0x36000000UL
};

uint8_t T[11] = { 0x01,0x02,0x04 ,0x08 ,0x10 ,0x20 ,0x40 ,0x80 ,0x1B ,0x36,0x72 };

// 加密使用的列混合数组
uint8_t encry_s[16] = {
	0x02,0x03,0x01,0x01,
	0x01,0x02,0x03,0x01,
	0x01,0x01,0x02,0x03,
	0x03,0x01,0x01,0x02
};


uint8_t GFMul(uint8_t a, uint8_t b) {
	uint8_t p = 0;
	for (int i = 0; i < 8; i++) {
		//先判断b的低阶位		
		if ((b & 0x01) == 1)
			p ^= a;
		//拿到a的高阶位 
		int temp = (a&128)/128;
		a <<= 1;
		//左移导致溢出了 所以用假如没有丢失数据的左移后a mod m(x)  等价于丢失数据后a ^ 0x1b 
		if (temp == 1)
			a ^= 0x1b;
		b >>= 1;
	}
	return p;
}

static void dump_buf(uint8_t* buf, uint32_t len)
{
	int i;

	for (i = 0; i < len; i++) {
		printf("%s%02X%s", i % 16 == 0 ? "\r\n\t" : " ",
			buf[i],
			i == len - 1 ? "\r\n" : "");
	}
}

void ShiftRows(uint8_t* status) {
	uint8_t temp[3];

	temp[0] = status[4];
	status[4] = status[5];
	status[5] = status[6];
	status[6] = status[7];
	status[7] = temp[0];

	temp[0] = status[8];
	temp[1] = status[9];
	status[8] = status[10];
	status[9] = status[11];
	status[10] = temp[0];
	status[11] = temp[1];

	temp[0] = status[12];
	temp[1] = status[13];
	temp[2] = status[14];
	status[12] = status[15];
	status[13] = temp[0];
	status[14] = temp[1];
	status[15] = temp[2];

}

void SubBytes(uint8_t* status) {
	for (int i = 0; i < 16; i++) {
		status[i] = S[status[i]];
	}
}

void MixColumns(uint8_t sta_matr[4 * 4], uint8_t s[4 * 4]) {
	uint8_t matr[4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			matr[j] = sta_matr[i + j * 4];

		sta_matr[i] = GFMul(s[0], matr[0]) ^ GFMul(s[1], matr[1]) ^ GFMul(s[2], matr[2]) ^ GFMul(s[3], matr[3]);
		sta_matr[i + 4] = GFMul(s[4], matr[0]) ^ GFMul(s[5], matr[1]) ^ GFMul(s[6], matr[2]) ^ GFMul(s[7], matr[3]);
		sta_matr[i + 8] = GFMul(s[8], matr[0]) ^ GFMul(s[9], matr[1]) ^ GFMul(s[10], matr[2]) ^ GFMul(s[11], matr[3]);
		sta_matr[i + 12] = GFMul(s[12], matr[0]) ^ GFMul(s[13], matr[1]) ^ GFMul(s[14], matr[2]) ^ GFMul(s[15], matr[3]);
	}
}

void AddRoundKey(uint8_t* status, uint8_t* rkey) {
	for (int i = 0; i < 16; i++) {
		status[i] = rkey[i] xor status[i];
	}
}

void KeyExpansion(uint8_t* key, uint8_t** w) {
	uint8_t temp[4];
	for (int i = 0; i < 16; i++) {
		w[0][i] = key[i];
	}
	for (int j = 0; j < 11; j++) {
		for (int i = 0; i < 4; i++) {
			if (i != 3) {
				temp[i] = w[j][13 + i];
			}
			else {
				temp[i] = w[j][12];
			}
			temp[i] = S[temp[i]];
		}
		temp[0] = temp[0] ^ T[j];
		for (int i = 0; i < 16; i++) {
			if (i >= 0 && i < 4) {
				w[j + 1][i] = w[j][i] ^ temp[i];
			}
			else {
				w[j + 1][i] = w[j][i] ^ w[j + 1][i - 4];
			}
		}
	}
}

void rkey_change(uint8_t** rkey) {
	uint8_t rkey2[11][16] = { 0 };
	for (int i = 0; i < 11; i++) {
		int a = 0;
		int b = 4;
		int c = 8;
		int d = 12;
		for (int j = 0; j < 16; j++) {
			if (j % 4 == 0) {
				uint8_t temp[4];
				temp[a] = rkey[i][j];
				rkey2[i][a] = temp[a];
				a++;
			}
			if (j % 4 == 1) {
				uint8_t temp[4];
				temp[b-4] = rkey[i][j];
				rkey2[i][b] = temp[b-4];
				b++;
			}
			if (j % 4 == 2) {
				uint8_t temp[4];
				temp[c-8] = rkey[i][j];
				rkey2[i][c] = temp[c-8];
				c++;
			}
			if (j % 4 == 3) {
				uint8_t temp[4];
				temp[d-12] = rkey[i][j];
				rkey2[i][d] = temp[d-12];
				d++;
			}
		}
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 16; j++) {
			rkey[i][j] = rkey2[i][j];
		}
	}
}

void AES(char* key,char* input){
	uint8_t** rkey = 0;
	rkey = new uint8_t * [12];
	for (int i = 0; i < 12; i++)
	{
		*(rkey + i) = new uint8_t[16];
	}
	KeyExpansion((uint8_t*)key, rkey);
	rkey_change(rkey); 
	//dump_buf(rkey[0], 16);

	//dump_buf((uint8_t*)input, 16);

	AddRoundKey((uint8_t*)input, rkey[0]);
	for (int i = 0; i < 9; i++) {
		ShiftRows((uint8_t*)input);
		SubBytes((uint8_t*)input);
		MixColumns((uint8_t*)input, encry_s);
		AddRoundKey((uint8_t*)input, rkey[i + 1]);
	}
	SubBytes((uint8_t*)input);
	ShiftRows((uint8_t*)input);
	AddRoundKey((uint8_t*)input, rkey[10]);
	//cout << "得到密文为： ";
	//dump_buf((uint8_t*)input, 16);
}


int main() {

	
	
    //char* input = "2021001611600000";
    //input[0] = 256;
    
    //AES(key,input);



	time_t start,end;
	start = clock();
    char* key="2021001611600000";
    uint8_t input[16]{};
    for(int i=0;i<100;i++){
    	input[2]=i; 
		for(int j=0;j<256;j++){
			input[0]=j;
			AES(key,(char*)input);
			
		}

	}
	end = clock();
	cout<<"100次加密时间为："<<(end-start)<<"ms"<<endl; 

	return 0;

}
