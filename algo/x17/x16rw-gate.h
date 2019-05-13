#ifndef X16RW_GATE_H__
#define X16RW_GATE_H__ 1

#include "algo-gate-api.h"
#include "avxdefs.h"
#include <stdint.h>

#if defined(__AVX2__) && defined(__AES__)
  #define X16RW_4WAY
#endif

enum x16rw_Algo {
	SKEIN = 0,
	BMW,
	BLAKE,
	SHA_512,
	SHABAL,
	KECCAK,
	SHAVITE,
	WHIRLPOOL,
	CUBEHASH,
	JH,
	LUFFA,
	ECHO,
	SIMD,
	FUGUE,
	GROESTL,
	HAMSI,
        X16RW_HASH_FUNC_COUNT = 8
};

bool (*x16_rw_s_getAlgoString) ( const char*, char* );
void x16rw_getAlgoString( const char* prevblock, char *output );
void x16rws_getAlgoString( const char* prevblock, char *output );

bool register_x16rw_algo( algo_gate_t* gate );
bool register_x16rws_algo( algo_gate_t* gate );

#if defined(X16RW_4WAY)

void x16rw_4way_hash( void *state, const void *input );

int scanhash_x16rw_4way( int thr_id, struct work *work, uint32_t max_nonce,
                        uint64_t *hashes_done );

void init_x16rw_4way_ctx();

#endif

void x16rw_hash( void *state, const void *input );

int scanhash_x16rw( int thr_id, struct work *work, uint32_t max_nonce,
                   uint64_t *hashes_done );

void init_x16rw_ctx();

#endif

