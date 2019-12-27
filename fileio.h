#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

uint8_t* read(uint64_t* length, char* input_file_name);

int write(uint8_t* buffer, uint64_t length, char* output_file_name);

#endif
