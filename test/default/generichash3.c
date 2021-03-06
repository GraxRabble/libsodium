
#define TEST_NAME "generichash3"
#include "cmptest.h"

int main(void)
{
#define MAXLEN 64
    crypto_generichash_blake2b_state st;
    unsigned char salt[crypto_generichash_blake2b_SALTBYTES]
        = { '5', 'b', '6', 'b', '4', '1', 'e', 'd',
            '9', 'b', '3', '4', '3', 'f', 'e', '0' };
    unsigned char personal[crypto_generichash_blake2b_PERSONALBYTES]
        = { '5', '1', '2', '6', 'f', 'b', '2', 'a',
            '3', '7', '4', '0', '0', 'd', '2', 'a' };
    unsigned char in[MAXLEN], out[crypto_generichash_blake2b_BYTES_MAX],
        k[crypto_generichash_blake2b_KEYBYTES_MAX];
    size_t h, i, j;

    for (h = 0; h < crypto_generichash_blake2b_KEYBYTES_MAX; ++h)
        k[h] = h;

    for (i = 0; i < MAXLEN; ++i) {
        in[i] = i;
        crypto_generichash_blake2b_init_salt_personal(
            &st, k, 1 + i % crypto_generichash_blake2b_KEYBYTES_MAX,
            1 + i % crypto_generichash_blake2b_BYTES_MAX, salt, personal);
        crypto_generichash_blake2b_update(&st, in, i);
        crypto_generichash_blake2b_final(
            &st, out, 1 + i % crypto_generichash_blake2b_BYTES_MAX);
        for (j = 0; j < 1 + i % crypto_generichash_blake2b_BYTES_MAX; ++j) {
            printf("%02x", (unsigned int)out[j]);
        }
        printf("\n");
    }
    assert(crypto_generichash_blake2b_init_salt_personal(&st, k, sizeof k, 0U,
                                                         salt, personal) == -1);
    assert(crypto_generichash_blake2b_init_salt_personal(&st, k, sizeof k,
                                                         crypto_generichash_BYTES_MAX + 1U,
                                                         salt, personal) == -1);
    assert(crypto_generichash_blake2b_init_salt_personal(&st, k,
                                                         crypto_generichash_KEYBYTES_MAX + 1U,
                                                         sizeof out, salt, personal) == -1);
    return 0;
}
