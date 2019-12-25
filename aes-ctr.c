#include <inttypes.h>
#include <stdio.h>
#include <string.h>

uint8_t sbox[] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

void print_state(uint8_t* state){
	unsigned char output_data[17] = {};
	memcpy(output_data, state, 16);
	printf("state : ");
	for(int i=0; i<16; i+=4){
		for(int j=0; j<4; j++){
			printf("%02x ", output_data[i+j]);
		}
		//printf("\n");
	}
	printf("\n");
}

void print_state_n(uint8_t* state, uint64_t n){
	for(uint64_t i=0; i<n; i++){
		printf("[%0ld]", i); print_state(&state[16*i]);
	}
}

void print_key(uint32_t* key){
	printf("key   : ");
	for(int i=0; i<4; i++){
		printf("%04x ", key[i]);
	}
	printf("\n");
}

void print_round_key(uint32_t* key){
	for(int i=0; i<11; i++){
		printf("[%02d] ", i); print_key(key+i*4);
	}
}

void print_key_n(uint32_t* key, uint64_t n){
	for(uint64_t i=0; i<n; i++){
		printf("[%0ld]", i); print_key(key);
	}
}

void print_ctr(uint64_t* ctr){
	printf("ctr   : %016lx %016lx \n", ctr[1], ctr[0]);
}

int SubBytes(uint8_t* state){
	for(int i=0; i<16; i++){
		state[i] = sbox[state[i]];
	}

	return 0;
}

void xorSwap(uint8_t* x, uint8_t* y){
	if (x != y) {
		*x ^= *y;
		*y ^= *x;
		*x ^= *y;
	}
}

int ShiftRows(uint8_t* state){
	for(int i=1; i<4; i++){
		for(int j=0; j<i; j++){
			xorSwap(&state[ 4+i],&state[  i]);
			xorSwap(&state[ 8+i],&state[4+i]);
			xorSwap(&state[12+i],&state[8+i]);
		}
	}
	return 0;
}

#define X2(I) (I<<1)^((I & 0x80) ? 0x1b : 0x00)
#define X3(I) X2(I)^I

int MixColumns(uint8_t* state){
	/*
	 * Over GF(2**8)
	 *
	 * a^b : a+b = a-b
	 * a<<1 : a x 2
	 * a^(a<<1) : a + (a x 2) = a x 3
	 */

	uint8_t tmp[4] = {};
	uint8_t* s = state;

	for(int i=0; i<4; i++){
		tmp[0] = X2(s[0]) ^ X3(s[1]) ^   (s[2]) ^   (s[3]);
		tmp[1] =   (s[0]) ^ X2(s[1]) ^ X3(s[2]) ^   (s[3]);
		tmp[2] =   (s[0]) ^   (s[1]) ^ X2(s[2]) ^ X3(s[3]);
		tmp[3] = X3(s[0]) ^   (s[1]) ^   (s[2]) ^ X2(s[3]);
		memcpy(s, tmp, 4);
		s += 4;
	}

	return 0;
}

uint32_t rcon[11] = {
	0x00000000,
	0x00000001,
	0x00000002,
	0x00000004,
	0x00000008,
	0x00000010,
	0x00000020,
	0x00000040,
	0x00000080,
	0x0000001B,
	0x00000036
};

uint32_t RotWord(uint32_t word){
	return word << 24 | word >> 8;
}

uint32_t SubWord(uint32_t word){
	uint32_t val = word;
	uint8_t* p = (uint8_t*)&val;
	p[0] = sbox[p[0]];
	p[1] = sbox[p[1]];
	p[2] = sbox[p[2]];
	p[3] = sbox[p[3]];
	return val;
}

extern void ExpandKey(const uint32_t* key, uint32_t* w){
	memcpy(w, key, 16);
	for (int i=4; i<44; i++) {
		uint32_t temp = w[i-1];
		if (i%4 == 0) {
			temp = SubWord(RotWord(temp)) ^ rcon[i/4];
		}
		w[i] = w[i-4] ^ temp;
	}
}

int AddRoundKey(uint8_t* state, uint32_t* roundKeys){
	uint32_t* state32 = (uint32_t*)state;
	for(int i=0; i<4; i++){
		state32[i] ^= roundKeys[i];
	}

	return 0;
}

int aes(uint8_t* state, uint32_t* key){
	uint32_t roundKeys[44] = {};
	ExpandKey(key, roundKeys);
	AddRoundKey(state, &roundKeys[0]);

	for(int i=1; i<=9; i++){
		SubBytes(state);
		ShiftRows(state);
		MixColumns(state);
		AddRoundKey(state, &roundKeys[4*i]);
	}

	SubBytes(state);
	ShiftRows(state);
	AddRoundKey(state, &roundKeys[40]);

	return 0;
}

void aes_ctr(uint8_t state_num, uint8_t state[16*state_num], uint32_t key[4*state_num],uint64_t nonce_num, uint64_t nonce[nonce_num]){
	for(uint64_t nn=0; nn<nonce_num; nn++){
		uint64_t ctr[2] = {};
		ctr[1] = nonce[nn];

		for(int sn=0; sn<state_num; sn++){
			//			printf("\n[%02d]===================================================\n", sn);
			//			print_state(&state[sn]);
			//			print_ctr(ctr);

			aes((uint8_t*)ctr, &key[4*nn]);

			//			print_ctr(ctr);

			for(uint8_t j=0; j<16; j++){
				state[16*sn + j] ^= ((uint8_t*)ctr)[j];
			}

			//			print_state(&state[sn]);

			ctr[0] = sn+1; ctr[1] = nonce[nn];
		}
	}
}

int main(void){
	uint64_t nonce_num = 1;
	uint64_t nonce[nonce_num];
	nonce[0] = 0x123456789abcdef;

	uint32_t key[4*nonce_num];
	//memcpy(key, "0123456789123456", 16);
	for(uint32_t i=0;i<(4*nonce_num);i++) key[i]=i;

	uint8_t block_num = 10;
	uint8_t state[16*block_num];
	//memcpy(state, "AES  encryption!", 16);
	//scanf("%s", (char *)state);
	for(uint8_t i=0;i<(16*block_num);i++) state[i]=i;

	printf("--- PLAINTEXT ---\n");
	print_state_n(state, block_num); printf("\n");
	printf("--- KEY       ---\n");
	print_key_n(key, nonce_num);     printf("\n");

	printf("--- ENCRYPT   ---\n");
	aes_ctr(block_num, state, key, nonce_num, nonce);
	print_state_n(state, block_num); printf("\n");

	printf("--- DECRYPT   ---\n");
	aes_ctr(block_num, state, key, nonce_num, nonce);
	print_state_n(state, block_num); printf("\n");

	return 0;
}
