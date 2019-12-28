#include "print.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

void print_state(uint8_t* state){
	unsigned char output_data[17] = {};
	memcpy(output_data, state, 16);
	printf("state : ");
	for(int i=0; i<16; i+=4){
		for(int j=0; j<4; j++){
			printf("%02x ", output_data[i+j]);
			//printf("%c ", (char)output_data[i+j]);
		}
		//printf("\n");
	}
	printf("\n");
}

void print_state_n(uint8_t* state, uint64_t n){
	for(uint64_t i=0; i<n; i++){
		printf("[%03ld]", i); print_state(&state[16*i]);
	}
}

void print_key(uint32_t* key){
	printf("key   : ");
	for(int i=0; i<4; i++){
		printf("%08x ", key[i]);
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

void print_nonce(uint32_t* nonce){
	printf("nonce : ");
	for(int i=0; i<2; i++){
		printf("%08x ", nonce[i]);
	}
	printf("\n");
}

void print_ctr(uint64_t* ctr){
	printf("ctr   : %016lx %016lx \n", ctr[1], ctr[0]);
}
