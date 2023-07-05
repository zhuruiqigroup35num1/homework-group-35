#ifndef MY_SM3_H_INCLUDED
#define MY_SM3_H_INCLUDED

#include <stdint.h>

#ifndef SM3_DIGEST_LENGTH
#define SM3_DIGEST_LENGTH       32
#endif

#define SM3_BLOCK_SIZE          64

typedef struct {
	unsigned int state[8], msgLen, curlen;
	unsigned char buf[SM3_BLOCK_SIZE];
} SM3_CTX;

void SM3_init(SM3_CTX*);
void SM3_process(SM3_CTX*, const void*, unsigned int);
void SM3_done(SM3_CTX*, void*);
void SM3_paddingpart(SM3_CTX*, unsigned char out[SM3_DIGEST_LENGTH]);
void print_Hashvalue(unsigned char hash_value[], int len);

#endif 
