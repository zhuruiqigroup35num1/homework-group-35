#include"mysm3.h"  
//SM3实现相关的头文件  
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<string>
#include<iostream>

using namespace std;

const int MAX_BITS = SM3_OUTLEN * 8;

int SM3_RhoAttack(int bits)
{
    if (bits <= 0 || bits > MAX_BITS) {
        cerr << "Error: bits out of range." << endl;
        return -1;
    }
    uint mask = (1 << bits) - 1;
    uint m = rand() & mask;
    uchar h1[SM3_OUTLEN];
    uchar h2[SM3_OUTLEN];

    int ret = SM3(to_string(m), h1);
    if (ret == -1) {
        cerr << "Error: SM3 function failed." << endl;
        return -1;
    }

    ret = SM3(h1, SM3_OUTLEN, h2);
    if (ret == -1) {
        cerr << "Error: SM3 function failed." << endl;
        return -1;
    }

    while (true)
    {
        ret = SM3(h1, SM3_OUTLEN, h1);
        if (ret == -1) {
            cerr << "Error: SM3 function failed." << endl;
            return -1;
        }

        ret = SM3(h2, SM3_OUTLEN, h2);
        if (ret == -1) {
            cerr << "Error: SM3 function failed." << endl;
            return -1;
        }

        ret = SM3(h2, SM3_OUTLEN, h2);
        if (ret == -1) {
            cerr << "Error: SM3 function failed." << endl;
            return -1;
        }

        if (!memcmp(h1, h2, bits / 8))
        {
            cout << "Found a collision with " << bits << " bits." << endl;
            cout << "hash1:" << endl;
            print_Hashvalue(h1, SM3_OUTLEN);
            cout << "hash2:" << endl;
            print_Hashvalue(h2, SM3_OUTLEN);
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <bits>" << endl;
        return -1;
    }

    int bits = stoi(argv[1]);
    srand(time(NULL));

    clock_t start, end;
    start = clock();
    int ret = SM3_RhoAttack(bits);
    end = clock();

    if (ret == -1) {
        cerr << "Error: Rho attack failed." << endl;
        return -1;
    }

    cout << "Sum_time: " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}
