#ifndef AES_H
#define AES_H

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

int SubBytes(uint8_t* state);

void xorSwap(uint8_t* x, uint8_t* y);

int ShiftRows(uint8_t* state);

#define X2(I) (I<<1)^((I & 0x80) ? 0x1b : 0x00)
#define X3(I) X2(I)^I

int MixColumns(uint8_t* state);

uint32_t RotWord(uint32_t word);

uint32_t SubWord(uint32_t word);

void ExpandKey(const uint32_t* key, uint32_t* w);

int AddRoundKey(uint8_t* state, uint32_t* roundKeys);

int aes(uint8_t* state, uint32_t* key);

void aes_ctr(uint8_t state_num, uint8_t state[16*state_num], uint32_t key[4*state_num],uint64_t nonce);

#endif
