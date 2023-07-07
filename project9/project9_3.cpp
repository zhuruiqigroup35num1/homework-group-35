#include <iostream>
#include <string>
#include <cmath>
#include<time.h>
#include<ctime>

using namespace std;

string BinToHex(string str) 
{
	string hex = "";
	int temp = 0;
	while (str.size() % 4 != 0) {
		str = "0" + str;
	}
	for (int i = 0; i < str.size(); i += 4) {
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;
		if (temp < 10) {
			hex += to_string(temp);
		}
		else {
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

string HexToBin(string str)
{
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			bin += table[str[i] - 'A' + 10];
		}
		else {
			bin += table[str[i] - '0'];
		}
	}
	return bin;
}


int HexToDec(char str)
{
	int dec = 0;
	if (str >= 'A' && str <= 'F') {
		dec += (str - 'A' + 10);
	}
	else {
		dec += (str - '0');
	}
	return dec;
}


//ѭ������
string LeftShift(string str, int len) 
{
	string res = HexToBin(str);
	res = res.substr(len) + res.substr(0, len);
	return BinToHex(res);
}


//���
string XOR(string str1, string str2) 
{
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == res2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BinToHex(res);
}

//�����Ա任t
string NLTransform(string str) 
{
	string Sbox[16][16] = { {"D6","90","E9","FE","CC","E1","3D","B7","16","B6","14","C2","28","FB","2C","05"},
						 {"2B","67","9A","76","2A","BE","04","C3","AA","44","13","26","49","86","06","99"},
						 {"9C","42","50","F4","91","EF","98","7A","33","54","0B","43","ED","CF","AC","62"},
						 {"E4","B3","1C","A9","C9","08","E8","95","80","DF","94","FA","75","8F","3F","A6"},
						 {"47","07","A7","FC","F3","73","17","BA","83","59","3C","19","E6","85","4F","A8"},
						 {"68","6B","81","B2","71","64","DA","8B","F8","EB","0F","4B","70","56","9D","35"},
						 {"1E","24","0E","5E","63","58","D1","A2","25","22","7C","3B","01","21","78","87"},
						 {"D4","00","46","57","9F","D3","27","52","4C","36","02","E7","A0","C4","C8","9E"},
						 {"EA","BF","8A","D2","40","C7","38","B5","A3","F7","F2","CE","F9","61","15","A1"},
						 {"E0","AE","5D","A4","9B","34","1A","55","AD","93","32","30","F5","8C","B1","E3"},
						 {"1D","F6","E2","2E","82","66","CA","60","C0","29","23","AB","0D","53","4E","6F"},
						 {"D5","DB","37","45","DE","FD","8E","2F","03","FF","6A","72","6D","6C","5B","51"},
						 {"8D","1B","AF","92","BB","DD","BC","7F","11","D9","5C","41","1F","10","5A","D8"},
						 {"0A","C1","31","88","A5","CD","7B","BD","2D","74","D0","12","B8","E5","B4","B0"},
						 {"89","69","97","4A","0C","96","77","7E","65","B9","F1","09","C5","6E","C6","84"},
						 {"18","F0","7D","EC","3A","DC","4D","20","79","EE","5F","3E","D7","CB","39","48"} };
	string res = "";
	for (int i = 0; i < 4; i++) {
		res = res + Sbox[HexToDec(str[2 * i])][HexToDec(str[2 * i + 1])];
	}
	return res;
}

string LTransform(string str) 
{
	return XOR(XOR(XOR(XOR(str, LeftShift(str, 2)), LeftShift(str, 10)), LeftShift(str, 18)), LeftShift(str, 24));
}

//L���Ա任
string L2Transform(string str) 
{
	return XOR(XOR(str, LeftShift(str, 13)), LeftShift(str, 23));
}

//�ӽ��ܺϳ�T�û�
string T(string str) 
{
	return LTransform(NLTransform(str));
}

//��Կ��չ�ϳ�T�û�
string T2(string str) 
{
	return L2Transform(NLTransform(str));
}

string KeyExtension(string MK) 
{
	string FK[4] = { "A3B1BAC6", "56AA3350", "677D9197", "B27022DC" };
	string CK[32] = { "00070E15", "1C232A31", "383F464D", "545B6269",
					  "70777E85", "8C939AA1", "A8AFB6BD", "C4CBD2D9",
					  "E0E7EEF5", "FC030A11", "181F262D", "343B4249",
					  "50575E65", "6C737A81", "888F969D", "A4ABB2B9",
					  "C0C7CED5", "DCE3EAF1", "F8FF060D", "141B2229",
					  "30373E45", "4C535A61", "686F767D", "848B9299",
					  "A0A7AEB5", "BCC3CAD1", "D8DFE6ED", "F4FB0209",
					  "10171E25", "2C333A41", "484F565D", "646B7279" };
	string K[36] = { XOR(MK.substr(0,8),FK[0]),XOR(MK.substr(8,8),FK[1]),XOR(MK.substr(16,8),FK[2]),XOR(MK.substr(24),FK[3]) };
	string rks = "";
	for (int i = 0; i < 32; i++) {
		K[i + 4] = XOR(K[i], T2(XOR(XOR(XOR(K[i + 1], K[i + 2]), K[i + 3]), CK[i])));
		rks += K[i + 4];
	}
	return rks;
}

//Enc_coding(����)
string encode(string plain, string key) 
{

	string cipher[36] = { plain.substr(0,8),plain.substr(8,8),plain.substr(16,8),plain.substr(24) };
	string rks = KeyExtension(key);
	for (int i = 0; i < 32; i++) {
		cipher[i + 4] = XOR(cipher[i], T(XOR(XOR(XOR(cipher[i + 1], cipher[i + 2]), cipher[i + 3]), rks.substr(8 * i, 8))));
	}

	return cipher[35] + cipher[34] + cipher[33] + cipher[32];
}

//Dnc_coding�����ܣ�
string decode(string cipher, string key) 
{
	string plain[36] = { cipher.substr(0,8),cipher.substr(8,8), cipher.substr(16,8), cipher.substr(24,8) };
	string rks = KeyExtension(key);
	for (int i = 0; i < 32; i++) {
		plain[i + 4] = XOR(plain[i], T(XOR(XOR(XOR(plain[i + 1], plain[i + 2]), plain[i + 3]), rks.substr(8 * (31 - i), 8))));
		
	}
	
	return plain[35] + plain[34] + plain[33] + plain[32];
}

int main() 
{
	double start_time_1 = clock();
	string str = "20212220221900000000000000000000";
	cout << "��    �ģ�" << str.substr(0, 8) << "  " << str.substr(8, 8) << "  " << str.substr(16, 8) << "  " << str.substr(24, 8) << endl;
	cout << endl;
	string key = "20212220221900000000000000000000";
	cout << "������Կ��" << key.substr(0, 8) << "  " << key.substr(8, 8) << "  " << key.substr(16, 8) << "  " << key.substr(24, 8) << endl;
	cout << endl;
	string cipher = encode(str, key);
	cout << "��    �ģ�" << cipher.substr(0, 8) << "  " << cipher.substr(8, 8) << "  " << cipher.substr(16, 8) << "  " << cipher.substr(24, 8) << endl;
	cout << endl;
	double end_time_1 = clock();
	double sum_time_1 = ((end_time_1 - start_time_1) / CLOCKS_PER_SEC);
	cout << sum_time_1 << " s" << endl;
	cout << endl;
	double start_time_2 = clock();
	cout << "��    �ģ�" << cipher.substr(0, 8) << "  " << cipher.substr(8, 8) << "  " << cipher.substr(16, 8) << "  " << cipher.substr(24, 8) << endl;
	cout << endl;
	cout << "������Կ��" << key.substr(0, 8) << "  " << key.substr(8, 8) << "  " << key.substr(16, 8) << "  " << key.substr(24, 8) << endl;
	cout << endl;
	string plain = decode(cipher, key);
	cout << "��    �ģ�" << plain.substr(0, 8) << "  " << plain.substr(8, 8) << "  " << plain.substr(16, 8) << "  " << plain.substr(24, 8) << endl;
	double end_time_2 = clock();
	double sum_time_2 = ((end_time_2 - start_time_2) / CLOCKS_PER_SEC);
	cout << sum_time_2 << " s" << endl;
	cout << endl;

	return 0;
}
