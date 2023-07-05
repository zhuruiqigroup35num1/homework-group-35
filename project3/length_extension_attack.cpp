#include "mysm3.h"
//SM3实现的头文件
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

void attack(unsigned char* h, unsigned char* m, int len_of_m, int len_of_h) {
    SM3_CTX ctx;
    unsigned char fake_h[SM3_DIGEST_LENGTH];
    unsigned char h2[SM3_DIGEST_LENGTH], m2[SM3_BLOCK_SIZE + 1];

    memset(fake_h, 0x00, SM3_DIGEST_LENGTH);
    fake_h[SM3_DIGEST_LENGTH - 1] = (unsigned char)len_of_h;

    SM3_init(&ctx);
    SM3_process(&ctx, m, len_of_m);
    SM3_paddingpart(&ctx, h2);
    //拓展部分


    for (int k = 0; k < SM3_BLOCK_SIZE; k++) {
        m2[k] = m[k];
    }
    m2[SM3_BLOCK_SIZE] = 0x80;

    int len_of_fake_h = len_of_h - SM3_DIGEST_LENGTH;

    unsigned char* new_h = (unsigned char*)malloc(sizeof(unsigned char) * len_of_fake_h);
    memset(new_h, 0x00, len_of_fake_h);

    memcpy(new_h, h2, SM3_DIGEST_LENGTH);
    SM3_CTX fake_ctx;
    fake_ctx.msgLen = len_of_fake_h * 8;
    memcpy(fake_ctx.state, fake_h, SM3_DIGEST_LENGTH);

    SM3_process(&fake_ctx, new_h, len_of_fake_h);

    SM3_process(&fake_ctx, m2, SM3_BLOCK_SIZE + 1);
    //攻击尝试
    unsigned char fakehash[(len_of_fake_h + SM3_BLOCK_SIZE + 1)];

    SM3_paddingpart(&fake_ctx, fakehash);

    cout << "Original hash value: ";
    print_Hashvalue(h2, SM3_DIGEST_LENGTH);

    cout << "Modified hash value: ";
    SM3_done(&fake_ctx, h2);
    print_Hashvalue(h2, SM3_DIGEST_LENGTH);

    cout << "Fake hash value:     ";
    print_Hashvalue(fakehash, len_of_fake_h + SM3_BLOCK_SIZE + 1);

    return;
}

int main() {
    ifstream fin;
    fin.open("message.txt");
    if (!fin.is_open()) {
        cout << "Cannot open file.\n";
        return 0;
    }

    int len_of_m = 0;
    unsigned char m[SM3_BLOCK_SIZE];
    memset(m, 0x00, SM3_BLOCK_SIZE);

    int len_of_h = SM3_DIGEST_LENGTH;
    unsigned char h[SM3_DIGEST_LENGTH];
    memset(h, 0x00, SM3_DIGEST_LENGTH);

    while (!fin.eof()) {
        fin.read((char*)m, SM3_BLOCK_SIZE);
        len_of_m += fin.gcount();

        SM3_CTX ctx;
        SM3_init(&ctx);
        SM3_process(&ctx, m, SM3_BLOCK_SIZE);
        SM3_done(&ctx, h);
    }

    fin.close();

    attack(h, m, len_of_m, len_of_h);

    return 0;
}
