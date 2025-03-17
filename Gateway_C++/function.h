#pragma once

#include "miracl.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include "bloom.h"

big read_secret(int userid);

char *hashing(char *str, int strlength, big hash);

big secret_seed_generator();

big secret_seed_generator_big(int userid, big p, big g, big q);

void secret_generate();

//big secret
// void secret_generate(big p, big q, big g, big u);

std::string convert_to_hexadecimal(unsigned char *bit_array, size_t size);

void convert_from_hexadecimal(struct bloom *bloom, std::string &hex_string);