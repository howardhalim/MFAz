#ifdef MR_CPP
#include "miracl.h"
#else
extern "C"
{
#include "miracl.h"
}
#endif

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include "bloom.h"


big read_secret(int userid) {
    char filename[256];
    sprintf(filename, "secret_seed/secret_seed_%d.txt", userid);
    FILE *file = fopen(filename, "r");
    
    big secret = mirvar(0);
    // cinnum(secret,file);
    cinnum(secret, file);
    return secret;
}

char *hashing(char *str, int strlength, big hash){ /* compute hash function */
    static char h[32];
    int ch;
    sha sh;
    shs256_init(&sh);
    for (int i = 0; i < strlength; i++)
    {
        ch = str[i];
        shs256_process(&sh, ch);
    }

    shs256_hash(&sh, h);
    bytes_to_big(32, h, hash);
    return h;
}

big secret_seed_generator(){
    big random = mirvar(0);
    big q = mirvar(9000); // The range is from 0 to 8999

    // Generate a random number less than 9000
    bigrand(q, random);

    // Add 1000 to the random number to ensure it's 4 digits
    add(random, mirvar(1000), random);

    mirkill(q);
    return random;
}

big secret_seed_generator_big(int userid, big p, big g, big q)
{
    big random = mirvar(1);
    big userid_big = mirvar(1);
    convert(userid, userid_big);
    srand(time(0)); // use current time as seed
    long seed = rand();
    irand(seed);
    bigrand(q, random);

    big temp = mirvar(1);
    add(userid_big, random, temp);
    big result = mirvar(1);
    powmod(g, temp, p, result);

    return result;
}

void secret_generate(){

    srand(time(0));
    long seed = rand();
    irand(seed);
    
    for (int i = 10001; i <= 10015;i++){
        int userid = i;
        big seeds = secret_seed_generator();
        cotnum(seeds, stdout);
        char filename[256];
        sprintf(filename, "secret_seed/secret_seed_%d.txt", userid);
        FILE *file = fopen(filename, "w");

        // Print the big number to the file
        cotnum(seeds, file);

        // Close the file
        fclose(file);
    }
}

// big secret number
// void secret_generate(big p, big q, big g, big u)
// {
//     // generate 15 secret seeds for user 10001-10015
//     for (int i = 10001; i <= 10015; i++)
//     {
//         int userid = i;
//         big seeds = secret_seed_generator_big(userid, p, g, q);

//         cotnum(seeds, stdout);
//         char filename[256];
//         sprintf(filename, "secret_seed/secret_seed_%d.txt", userid);
//         FILE *file = fopen(filename, "w");

//         // Print the big number to the file
//         cotnum(seeds, file);

//         // Close the file
//         fclose(file);
//     }
// }
std::string convert_to_hexadecimal(unsigned char *bit_array, size_t size)
{
    std::string hex_string;
    char buffer[3]; // Buffer to hold two hex digits and a null terminator

    for (size_t i = 0; i < size; ++i)
    {
        snprintf(buffer, sizeof(buffer), "%02x", bit_array[i]);
        hex_string += buffer;
    }

    return hex_string;
}

void convert_from_hexadecimal(struct bloom *bloom, std::string &hex_string)
{
    for (size_t i = 0; i < hex_string.length(); i+=2){
        char buffer[3];
        snprintf(buffer, sizeof(buffer), "%c%c", hex_string[i], hex_string[i+1]);

        int temp = std::stoi(buffer, nullptr, 16);
        bloom->bf[i / 2] = temp;
    }
}
