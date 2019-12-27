#ifndef PRINT_H
#define PRINT_H

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

void print_state(uint8_t* state);

void print_state_n(uint8_t* state, uint64_t n);

void print_key(uint32_t* key);

void print_round_key(uint32_t* key);

void print_key_n(uint32_t* key, uint64_t n);

void print_ctr(uint64_t* ctr);

void print_nonce(uint32_t* nonce);

#endif
