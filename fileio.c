#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

uint8_t* read(uint64_t* length, char* input_file_name){
	uint8_t* buffer;
	FILE *fp;

	fp = fopen(input_file_name, "rb");

	if (fp == NULL) {
		return NULL; //file open error
	}

	if (fseek(fp, 0, SEEK_END) != 0) {
		return NULL; //fseek error
	}
	*length = ftell(fp);

	if (fseek(fp, 0L, SEEK_SET) != 0) {
		return NULL; //fseek error
	}

	buffer = (uint8_t*) malloc(*length);
	if (buffer == NULL) {
		return NULL; //memory alocating error
	}

	for(int i=0; ((uint64_t)i)<*length; i++){
		buffer[i] = 0;
	}

	if (fread(buffer, 1, *length, fp) < *length) {
		return NULL; //file read error
	}

	fclose(fp);
	return buffer;
}

int write(uint8_t* buffer, uint64_t length, char* output_file_name){
	FILE *fp;

	fp = fopen(output_file_name, "wb");

	if (fp == NULL){
		return 1;
	}

	for(int i=0; ((uint64_t)i)<length; i++) {
//		printf("%c", (char)buffer[i]);
		fwrite(buffer+i, 1, 1, fp);
	}

	//fwrite(buffer, length, 4, fp);

	fclose(fp);

	return 0;
}

/*
int main (void) {
	uint8_t *buffer = NULL;
	uint64_t length = 0;

	buffer = read(&length);
	if(buffer == NULL) return 1;

//	for(int i=0; ((uint64_t)i)<length; i++) printf("%c", (char)buffer[i]);

	int let = write(buffer, length);
	if(let != 0) return let;

	free(buffer);

	return 0;
}
*/
