#include "hash.h"

unsigned char* SSHA(const unsigned char* msg, size_t length) {
    unsigned char A, B, C, D, E; //Initial Seed Value
    A = 56;
    B = 99;
    C = 102;
    D = 67;
    E = 76;

    for (int i = 0; i < length; i++) {
        for (int round = 0; round < 8; round++) {
            unsigned char g = (B & C) | (C & D);
            unsigned char old_A = A;
            unsigned char old_B = B;
            A = E;
            B = old_A;
            C = (old_A >> 2) + E;
            D = (old_A >> 2) ^ (old_B >> 1);
            E = g + msg[i] + (old_B >> 1);
        }
    }

    unsigned char* digest = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
    return digest;
}

/*
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#define SSHA2_DIGEST_SIZE 20   /* 5 words x 4 bytes */

// Returns a malloc'd 20-byte digest (caller must free), or NULL on failure. 
unsigned char *ssha2(const unsigned char *msg, size_t length)
{
    // Initial state (SHA-1 constants; swap in your own if the assignment specifies them) 
    uint32_t A = 0x67452301;
    uint32_t B = 0xEFCDAB89;
    uint32_t C = 0x98BADCFE;
    uint32_t D = 0x10325476;
    uint32_t E = 0xC3D2E1F0;

    unsigned char *digest;
    size_t i;
    int w;

    if (msg == NULL && length > 0)
        return NULL;

    digest = (unsigned char *)malloc(SSHA2_DIGEST_SIZE);
    if (digest == NULL)
        return NULL;

    for (i = 0; i < length; i++) {
        uint32_t newA = E;
        uint32_t newB = A;
        uint32_t newC = (A >> 2) + E;
        uint32_t newD = (A >> 2) ^ (B >> 1);
        uint32_t newE = (B >> 1) + ((B & C) | (D & C)) + (uint32_t)msg[i];

        A = newA;
        B = newB;
        C = newC;
        D = newD;
        E = newE;
    }

    // Write A..E out as big-endian bytes 
    {
        uint32_t state[5];
        state[0] = A; state[1] = B; state[2] = C; state[3] = D; state[4] = E;
        for (w = 0; w < 5; w++) {
            digest[w * 4 + 0] = (unsigned char)(state[w] >> 24);
            digest[w * 4 + 1] = (unsigned char)(state[w] >> 16);
            digest[w * 4 + 2] = (unsigned char)(state[w] >> 8);
            digest[w * 4 + 3] = (unsigned char)(state[w]);
        }
    }

    return digest;
}
*/
    
int digest_equal(struct Digest digest1, struct Digest digest2) {
    return ((digest1.hash0 == digest2.hash0) &&
        (digest1.hash1 == digest2.hash1) &&
        (digest1.hash2 == digest2.hash2) &&
        (digest1.hash3 == digest2.hash3) &&
        (digest1.hash4 == digest2.hash4));
}

void printDigest(struct Digest digest) {
    printf("%d %d %d %d %d\n", digest.hash0, digest.hash1, digest.hash2, digest.hash3, digest.hash4);
}
