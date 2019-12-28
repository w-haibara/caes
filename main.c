#include "aes.h"
#include "print.h"
#include "fileio.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

int main(void){
	char* plaintext_file_name = "PLAINTEXT";
	char* key_file_name       = "KEY";
	char* nonce_file_name     = "NONCE";
	char* encrypted_file_name = "ENCRYPTED";
	char* decrypted_file_name = "DECRYPT";

	uint64_t  plaintext_length = 0;
	uint8_t*  state = read(&plaintext_length, plaintext_file_name);
	uint64_t  block_num = plaintext_length/16 + 1;

	uint64_t  key_num = 0;
	uint32_t* key = (uint32_t*)read(&key_num, key_file_name);

	uint64_t  nonce_num = 0;
	uint64_t* nonce = (uint64_t*)read(&nonce_num, nonce_file_name);

	printf("--- PLAINTEXT ---\n");
	print_state_n(state, block_num); printf("\n");

	printf("--- KEY       ---\n");
	print_key(key);                  printf("\n");
	
	printf("--- NONCE     ---\n");
	print_nonce((uint32_t*)nonce);   printf("\n");
	
	printf("--- ENCRYPT   ---\n");
	aes_ctr(block_num, state, key, *nonce);
	print_state_n(state, block_num); printf("\n");
	write(state, plaintext_length, encrypted_file_name);
	
	printf("--- DECRYPT   ---\n");
	aes_ctr(block_num, state, key, *nonce);
	print_state_n(state, block_num); printf("\n");
	write(state, plaintext_length, decrypted_file_name);

	free(state);
	free(key);
	free(nonce);

	return 0;
}
