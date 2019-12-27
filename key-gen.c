#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define _NONCE "ABCDEFGH"
#define _KEY "0123456789abcdef"

int main (void) {
	uint8_t buffer1[8] = {};
	memcpy(buffer1, _NONCE, 8);
	int let = write(buffer1, 8, "NONCE");
	if(let != 0) return let;

	uint8_t buffer2[16] = {};
	memcpy(buffer2, _KEY, 16);
	let = write(buffer2, 16, "KEY");
	if(let != 0) return let;

	return 0;
}

