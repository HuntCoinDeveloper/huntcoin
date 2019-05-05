// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The DigiByte developers
// Copyright (c) 2009-2015 The Bittcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2016-2018 The CryptoCoderz Team / Espers
// Copyright (c) 2017-2018 The AmsterdamCoin developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2014-2017 The Mun Core developers
// Copyright (c) 2018 The Huntcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MULTIHASH_H
#define MULTIHASH_H

#include <arith_uint256.h>
#include <uint256.h>
#include <crypto/algos/hashlib/sph_blake.h>
#include <crypto/algos/hashlib/sph_bmw.h>
#include <crypto/algos/hashlib/sph_groestl.h>
#include <crypto/algos/hashlib/sph_jh.h>
#include <crypto/algos/hashlib/sph_keccak.h>
#include <crypto/algos/hashlib/sph_skein.h>
#include <crypto/algos/hashlib/sph_luffa.h>
#include <crypto/algos/hashlib/sph_cubehash.h>
#include <crypto/algos/hashlib/sph_shavite.h>
#include <crypto/algos/hashlib/sph_simd.h>
#include <crypto/algos/hashlib/sph_echo.h>
#include <crypto/algos/hashlib/sph_hamsi.h>
#include <crypto/algos/hashlib/sph_fugue.h>
#include <crypto/algos/hashlib/sph_shabal.h>
#include <crypto/algos/hashlib/sph_whirlpool.h>
#include <crypto/algos/hashlib/sph_sha2.h>
#include <crypto/algos/hashlib/sph_haval.h>
#include <crypto/algos/hashlib/sph_gost.h>
#include <crypto/algos/blake/blake2.h>
#include <openssl/sha.h>

#ifdef GLOBALDEFINED
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL sph_blake512_context     z_blake;
GLOBAL sph_bmw512_context       z_bmw;
GLOBAL sph_groestl512_context   z_groestl;
GLOBAL sph_jh512_context        z_jh;
GLOBAL sph_keccak512_context    z_keccak;
GLOBAL sph_skein512_context     z_skein;
GLOBAL sph_luffa512_context     z_luffa;
GLOBAL sph_cubehash512_context  z_cubehash;
GLOBAL sph_shavite512_context   z_shavite;
GLOBAL sph_simd512_context      z_simd;
GLOBAL sph_echo512_context      z_echo;
GLOBAL sph_hamsi512_context     z_hamsi;
GLOBAL sph_fugue512_context     z_fugue;
GLOBAL sph_shabal512_context    z_shabal;
GLOBAL sph_whirlpool_context    z_whirlpool;
GLOBAL sph_sha512_context       z_sha2;
GLOBAL sph_haval256_5_context   z_haval;

#define fillz() do { \
    sph_blake512_init(&z_blake); \
    sph_bmw512_init(&z_bmw); \
    sph_groestl512_init(&z_groestl); \
    sph_jh512_init(&z_jh); \
    sph_keccak512_init(&z_keccak); \
    sph_skein512_init(&z_skein); \
    sph_luffa512_init(&z_luffa); \
    sph_cubehash512_init(&z_cubehash); \
    sph_shavite512_init(&z_shavite); \
    sph_simd512_init(&z_simd); \
    sph_echo512_init(&z_echo); \
    sph_hamsi512_init(&z_hamsi); \
    sph_fugue512_init(&z_fugue); \
    sph_shabal512_init(&z_shabal); \
    sph_whirlpool_init(&z_whirlpool); \
    sph_sha512_init(&z_sha2); \
    sph_haval256_5_init(&z_haval); \
    sph_gost512_init(&z_gost); \
    } while (0) 

#define ZBLAKE (memcpy(&ctx_blake, &z_blake, sizeof(z_blake)))
#define ZBMW (memcpy(&ctx_bmw, &z_bmw, sizeof(z_bmw)))
#define ZGROESTL (memcpy(&ctx_groestl, &z_groestl, sizeof(z_groestl)))
#define ZJH (memcpy(&ctx_jh, &z_jh, sizeof(z_jh)))
#define ZKECCAK (memcpy(&ctx_keccak, &z_keccak, sizeof(z_keccak)))
#define ZSKEIN (memcpy(&ctx_skein, &z_skein, sizeof(z_skein)))
#define ZWHIRLPOOL (memcpy(&ctx_whirlpool, &z_whirlpool, sizeof(z_whirlpool)))
#define ZFUGUE (memcpy(&ctx_fugue, &z_fugue, sizeof(z_fugue)))
#define ZHAMSI (memcpy(&ctx_hamsi, &z_hamsi, sizeof(z_hamsi)))
#define ZSHABAL (memcpy(&ctx_shabal, &z_shabal, sizeof(z_shabal))
#define ZSHA2 (memcpy(&ctx_sha2, &z_sha2, sizeof(z_sha2)))
#define ZHAVAL (memcpy(&ctx_haval, &z_haval, sizeof(z_haval)))
#define ZGOST (memcpy(&ctx_gost, &z_gost, sizeof(z_gost)))


#define HASH_FUNC_BASE_TIMESTAMP 1492973331  // BitCore: Genesis Timestamp
#define HASH_FUNC_COUNT 10                   // BitCore: HASH_FUNC_COUNT of 11
#define HASH_FUNC_COUNT_PERMUTATIONS 40320   // BitCore: HASH_FUNC_COUNT!

inline int GetHashSelection(const uint256 PrevBlockHash, int index) 
{
    assert(index >= 0);
    assert(index < 16);

    #define START_OF_LAST_16_NIBBLES_OF_HASH 48
    int hashSelection = PrevBlockHash.GetNibble(START_OF_LAST_16_NIBBLES_OF_HASH + index);
    return(hashSelection);
}

template<typename T1>
inline uint256 HashKeccak(const T1 pbegin, const T1 pend)
{
    sph_keccak256_context ctx_keccak;
    static unsigned char pblank[1];
    uint256 hash;

    sph_keccak256_init(&ctx_keccak);
    sph_keccak256 (&ctx_keccak, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_keccak256_close(&ctx_keccak, static_cast<void*>(&hash));

    return hash;
}

template<typename T1>
inline uint256 HashX16R(const T1 pbegin, const T1 pend, const uint256 PrevBlockHash)
{
//	static std::chrono::duration<double>[16];
    int hashSelection;

    sph_blake512_context     ctx_blake;      //0
    sph_bmw512_context       ctx_bmw;        //1
    sph_groestl512_context   ctx_groestl;    //2
    sph_jh512_context        ctx_jh;         //3
    sph_keccak512_context    ctx_keccak;     //4
    sph_skein512_context     ctx_skein;      //5
    sph_luffa512_context     ctx_luffa;      //6
    sph_cubehash512_context  ctx_cubehash;   //7
    sph_shavite512_context   ctx_shavite;    //8
    sph_simd512_context      ctx_simd;       //9
    sph_echo512_context      ctx_echo;       //A
    sph_hamsi512_context     ctx_hamsi;      //B
    sph_fugue512_context     ctx_fugue;      //C
    sph_shabal512_context    ctx_shabal;     //D
    sph_whirlpool_context    ctx_whirlpool;  //E
    sph_sha512_context       ctx_sha512;     //F

    static unsigned char pblank[1];

    uint512 hash[16];

    for (int i=0;i<16;i++) 
    {
        const void *toHash;
        int lenToHash;
        if (i == 0) {
            toHash = (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0]));
            lenToHash = (pend - pbegin) * sizeof(pbegin[0]);
        } else {
            toHash = static_cast<const void*>(&hash[i-1]);
            lenToHash = 64;
        }

        hashSelection = GetHashSelection(PrevBlockHash, i);

        switch(hashSelection) {
            case 0:
                sph_blake512_init(&ctx_blake);
                sph_blake512 (&ctx_blake, toHash, lenToHash);
                sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[i]));
                break;
            case 1:
                sph_bmw512_init(&ctx_bmw);
                sph_bmw512 (&ctx_bmw, toHash, lenToHash);
                sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[i]));
                break;
            case 2:
                sph_groestl512_init(&ctx_groestl);
                sph_groestl512 (&ctx_groestl, toHash, lenToHash);
                sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[i]));
                break;
            case 3:
                sph_jh512_init(&ctx_jh);
                sph_jh512 (&ctx_jh, toHash, lenToHash);
                sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[i]));
                break;
            case 4:
                sph_keccak512_init(&ctx_keccak);
                sph_keccak512 (&ctx_keccak, toHash, lenToHash);
                sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[i]));
                break;
            case 5:
                sph_skein512_init(&ctx_skein);
                sph_skein512 (&ctx_skein, toHash, lenToHash);
                sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[i]));
                break;
            case 6:
                sph_luffa512_init(&ctx_luffa);
                sph_luffa512 (&ctx_luffa, toHash, lenToHash);
                sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[i]));
                break;
            case 7:
                sph_cubehash512_init(&ctx_cubehash);
                sph_cubehash512 (&ctx_cubehash, toHash, lenToHash);
                sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[i]));
                break;
            case 8:
                sph_shavite512_init(&ctx_shavite);
                sph_shavite512(&ctx_shavite, toHash, lenToHash);
                sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[i]));
                break;
            case 9:
                sph_simd512_init(&ctx_simd);
                sph_simd512 (&ctx_simd, toHash, lenToHash);
                sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[i]));
                break;
            case 10:
                sph_echo512_init(&ctx_echo);
                sph_echo512 (&ctx_echo, toHash, lenToHash);
                sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[i]));
                break;
           case 11:
                sph_hamsi512_init(&ctx_hamsi);
                sph_hamsi512 (&ctx_hamsi, toHash, lenToHash);
                sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[i]));
                break;
           case 12:
                sph_fugue512_init(&ctx_fugue);
                sph_fugue512 (&ctx_fugue, toHash, lenToHash);
                sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[i]));
                break;
           case 13:
                sph_shabal512_init(&ctx_shabal);
                sph_shabal512 (&ctx_shabal, toHash, lenToHash);
                sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[i]));
                break;
           case 14:
                sph_whirlpool_init(&ctx_whirlpool);
                sph_whirlpool(&ctx_whirlpool, toHash, lenToHash);
                sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[i]));
                break;
           case 15:
                sph_sha512_init(&ctx_sha512);
                sph_sha512 (&ctx_sha512, toHash, lenToHash);
                sph_sha512_close(&ctx_sha512, static_cast<void*>(&hash[i]));
                break;
        }
    }

    return hash[15].trim256();
}

template<typename T1>
inline uint256 QUARK(const T1 pbegin, const T1 pend)
{
    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_skein512_context     ctx_skein;
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
//std::string strhash;
//strhash = "";
#endif

    arith_uint512 mask = arith_uint512(8);
    arith_uint512 zero = arith_uint512(0);

    uint512 hash[9];

    sph_blake512_init(&ctx_blake);
    // ZBLAKE;
    sph_blake512 (&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[0]));

    sph_bmw512_init(&ctx_bmw);
    // ZBMW;
    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[0]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[1]));

    if ((UintToArith512(hash[1]) & mask) != zero)
    {
        sph_groestl512_init(&ctx_groestl);
        // ZGROESTL;
        sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[1]), 64);
        sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[2]));
    }
    else
    {
        sph_skein512_init(&ctx_skein);
        // ZSKEIN;
        sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[1]), 64);
        sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[2]));
    }

    sph_groestl512_init(&ctx_groestl);
    // ZGROESTL;
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[2]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[3]));

    sph_jh512_init(&ctx_jh);
    // ZJH;
    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[3]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[4]));

    if ((UintToArith512(hash[4]) & mask) != zero)
    {
        sph_blake512_init(&ctx_blake);
        // ZBLAKE;
        sph_blake512 (&ctx_blake, static_cast<const void*>(&hash[4]), 64);
        sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[5]));
    }
    else
    {
        sph_bmw512_init(&ctx_bmw);
        // ZBMW;
        sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[4]), 64);
        sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[5]));
    }

    sph_keccak512_init(&ctx_keccak);
    // ZKECCAK;
    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[5]), 64);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[6]));

    sph_skein512_init(&ctx_skein);
    // SKEIN;
    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[6]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[7]));

    if ((UintToArith512(hash[7]) & mask) != zero)
    {
        sph_keccak512_init(&ctx_keccak);
        // ZKECCAK;
        sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[7]), 64);
        sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[8]));
    }
    else
    {
        sph_jh512_init(&ctx_jh);
        // ZJH;
        sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[7]), 64);
        sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[8]));
    }

    return hash[8].trim256();
}

template<typename T1>
inline uint256 SkunkHash5(const T1 pbegin, const T1 pend)
{
    sph_skein512_context       ctx_skein;
    sph_cubehash512_context    ctx_cubehash;
    sph_fugue512_context       ctx_fugue;
    sph_gost512_context        ctx_gost;
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif
    
    uint512 hash[4];

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[0]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[0]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[1]));
        
    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[1]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[2]));

    sph_gost512_init(&ctx_gost);
    sph_gost512 (&ctx_gost, static_cast<const void*>(&hash[2]), 64);
    sph_gost512_close(&ctx_gost, static_cast<void*>(&hash[3]));

    return hash[3].trim256();
}

template<typename T1>
inline uint256 HashQubit(const T1 pbegin, const T1 pend)
{
    sph_luffa512_context	 ctx_luffa;
    sph_cubehash512_context  ctx_cubehash;
    sph_shavite512_context	 ctx_shavite;
    sph_simd512_context		 ctx_simd;
    sph_echo512_context		 ctx_echo;
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
//std::string strhash;
//strhash = "";
#endif


    uint512 hash[5];

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[0]));

    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[0]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[1]));

    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[1]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[2]));

    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[2]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[3]));

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[3]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[4]));

    return hash[4].trim256();
}

template<typename T1>
inline uint256 HashGroestl(const T1 pbegin, const T1 pend)
{
    sph_groestl512_context ctx_groestl;
    static unsigned char pblank[1];

    uint512 hash1;
    uint256 hash2;

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512(&ctx_groestl, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash1));

    SHA256((unsigned char*)&hash1, 64, (unsigned char*)&hash2);

    return hash2;
}

template<typename T1>
inline uint256 HashSkein(const T1 pbegin, const T1 pend)
{
    sph_skein512_context ctx_skein;
    static unsigned char pblank[1];

    uint512 hash1;
    uint256 hash2;

    sph_skein512_init(&ctx_skein);
    sph_skein512(&ctx_skein, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash1));

    SHA256((unsigned char*)&hash1, 64, (unsigned char*)&hash2);

    return hash2;
}

template<typename T1>
inline uint256 HashTimeTravel(const T1 pbegin, const T1 pend, uint32_t timestamp)
{
    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_skein512_context     ctx_skein;
    sph_luffa512_context     ctx_luffa;
    sph_cubehash512_context  ctx_cubehash;
    sph_shavite512_context   ctx_shavite;
    sph_simd512_context      ctx_simd;
    sph_echo512_context      ctx_echo;
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif

    uint512 hash[HASH_FUNC_COUNT];

    // We want to permute algorithms. To get started we
    // initialize an array with a sorted sequence of unique
    // integers where every integer represents its own algorithm.
    uint32_t permutation[HASH_FUNC_COUNT];
    for (uint32_t i=0; i < HASH_FUNC_COUNT; i++) {
        permutation[i]=i;
    }

    // Compute the next permuation
    uint32_t steps = (timestamp - HASH_FUNC_BASE_TIMESTAMP)%HASH_FUNC_COUNT_PERMUTATIONS;
    for (uint32_t i=0; i < steps; i++) {
        std::next_permutation(permutation, permutation + HASH_FUNC_COUNT);
    }

    for (uint32_t i=0; i < HASH_FUNC_COUNT; i++) {
	    switch(permutation[i]) {
            case 0:
                sph_blake512_init(&ctx_blake);
                if (i == 0)
                    sph_blake512 (&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
                else
                    sph_blake512 (&ctx_blake, static_cast<const void*>(&hash[i-1]), 64);                
                sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[i]));
            break;
            case 1:
                sph_bmw512_init(&ctx_bmw);
                if (i == 0)
                    sph_bmw512 (&ctx_bmw, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
                else
                    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[i-1]), 64);
                sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[i]));
            break;
            case 2:
                sph_groestl512_init(&ctx_groestl);
                if (i == 0)
                    sph_groestl512 (&ctx_groestl, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
                else
                    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[i-1]), 64);
                sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[i]));
            break;
            case 3:
                sph_skein512_init(&ctx_skein);
                if (i == 0)
                    sph_skein512 (&ctx_skein, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
                else
                    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[i-1]), 64);
                sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[i]));
            break;
            case 4:
                sph_jh512_init(&ctx_jh);
                if (i == 0)
                    sph_jh512 (&ctx_jh, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
                else
                    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[i-1]), 64);
                sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[i]));
            break;
            case 5:
                sph_keccak512_init(&ctx_keccak);
                if (i == 0)
                    sph_keccak512 (&ctx_keccak, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
                else
                    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[i-1]), 64);
                sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[i]));
            break;
            case 6:
                sph_luffa512_init(&ctx_luffa);
                if (i == 0)
                    sph_luffa512 (&ctx_luffa, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
                else
                    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[i-1]), 64);
                sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[i]));
            break;
            case 7:
                sph_cubehash512_init(&ctx_cubehash);
                if (i == 0)
                    sph_cubehash512 (&ctx_cubehash, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
                else
                    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[i-1]), 64);
                sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[i]));
            break;
            case 8:
                sph_shavite512_init(&ctx_shavite);
                if (i == 0)
                    sph_shavite512 (&ctx_shavite, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
                else
                    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[i-1]), 64);
                sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[i]));
            break;
            case 9:
                sph_simd512_init(&ctx_simd);
                if (i == 0)
                    sph_simd512 (&ctx_simd, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
                else
                    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[i-1]), 64);
                sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[i]));
            break;
            case 10:
                sph_echo512_init(&ctx_echo);
                if (i == 0)
                    sph_echo512 (&ctx_echo, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
                else
                    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[i-1]), 64);
                sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[i]));
            break;
	    }
    }

    return hash[HASH_FUNC_COUNT-1].trim256();
}

template<typename T1>
inline uint256 HMQ1725(const T1 pbegin, const T1 pend)
{
    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_skein512_context     ctx_skein;
    sph_luffa512_context      ctx_luffa;
    sph_cubehash512_context   ctx_cubehash;
    sph_shavite512_context    ctx_shavite;
    sph_simd512_context       ctx_simd;
    sph_echo512_context       ctx_echo;
    sph_hamsi512_context      ctx_hamsi;
    sph_fugue512_context      ctx_fugue;
    sph_shabal512_context     ctx_shabal;
    sph_whirlpool_context     ctx_whirlpool;
    sph_sha512_context        ctx_sha2;
    sph_haval256_5_context    ctx_haval;

    static unsigned char pblank[1];
    arith_uint512 mask = arith_uint512(24);
    arith_uint512 zero = arith_uint512(0);
    
    uint512 hash[25];

    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[0]));

    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[0]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[1]));

    if ((UintToArith512(hash[1]) & mask) != zero)
    {
        sph_groestl512_init(&ctx_groestl);
        sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[1]), 64);
        sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[2]));
    }
    else
    {
        sph_skein512_init(&ctx_skein);
        sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[1]), 64);
        sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[2]));
    }


    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[2]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[3]));

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[3]), 64);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[4]));

    if ((UintToArith512(hash[4]) & mask) != zero)
    {
        sph_blake512_init(&ctx_blake);
        sph_blake512 (&ctx_blake, static_cast<const void*>(&hash[4]), 64);
        sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[5]));
    }
    else
    {
        sph_bmw512_init(&ctx_bmw);
        sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[4]), 64);
        sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[5]));
    }

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[5]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[6]));

    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[6]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[7]));

    if ((UintToArith512(hash[7]) & mask) != zero)
    {
        sph_keccak512_init(&ctx_keccak);
        sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[7]), 64);
        sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[8]));
    }
    else
    {
        sph_jh512_init(&ctx_jh);
        sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[7]), 64);
        sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[8]));
    }

    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[8]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[9]));
        
    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[9]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[10]));

    if ((UintToArith512(hash[10]) & mask) != zero)
    {
        sph_whirlpool_init(&ctx_whirlpool);
        sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[10]), 64);
        sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[11]));
    }
    else
    {
        sph_haval256_5_init(&ctx_haval);
        sph_haval256_5 (&ctx_haval, static_cast<const void*>(&hash[10]), 64);
        sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[11]));
    }

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[11]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[12]));

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, static_cast<const void*>(&hash[12]), 64);
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[13]));

    if ((UintToArith512(hash[13]) & mask) != zero)
    {
        sph_shavite512_init(&ctx_shavite);
        sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[13]), 64);
        sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[14]));
    }
    else
    {
        sph_luffa512_init(&ctx_luffa);
        sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[13]), 64);
        sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[14]));
    }

    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512 (&ctx_hamsi, static_cast<const void*>(&hash[14]), 64);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[15]));

    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[15]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[16]));

    if ((UintToArith512(hash[16]) & mask) != zero)
    {
        sph_echo512_init(&ctx_echo);
        sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[16]), 64);
        sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[17]));
    }
    else
    {
        sph_simd512_init(&ctx_simd);
        sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[16]), 64);
        sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[17]));
    }

    sph_shabal512_init(&ctx_shabal);
    sph_shabal512 (&ctx_shabal, static_cast<const void*>(&hash[17]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[18]));

    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[18]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[19]));

    if ((UintToArith512(hash[19]) & mask) != zero)
    {
        sph_fugue512_init(&ctx_fugue);
        sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[19]), 64);
        sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[20]));
    }
    else
    {
        sph_sha512_init(&ctx_sha2);
        sph_sha512 (&ctx_sha2, static_cast<const void*>(&hash[19]), 64);
        sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[20]));
    }

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[20]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[21]));

    sph_sha512_init(&ctx_sha2);
    sph_sha512 (&ctx_sha2, static_cast<const void*>(&hash[21]), 64);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[22]));

    if ((UintToArith512(hash[22]) & mask) != zero)
    {
        sph_haval256_5_init(&ctx_haval);
        sph_haval256_5 (&ctx_haval, static_cast<const void*>(&hash[22]), 64);
        sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[23]));
    }
    else
    {
        sph_whirlpool_init(&ctx_whirlpool);
        sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[22]), 64);
        sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[23]));
    }

    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[23]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[24]));

    return hash[24].trim256();
}

template<typename T1>
inline uint256 HashX11(const T1 pbegin, const T1 pend)
{
    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_skein512_context     ctx_skein;
    sph_luffa512_context     ctx_luffa;
    sph_cubehash512_context  ctx_cubehash;
    sph_shavite512_context   ctx_shavite;
    sph_simd512_context      ctx_simd;
    sph_echo512_context      ctx_echo;
    static unsigned char pblank[1];

    uint512 hash[11];

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[0]));

    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[0]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[1]));

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[1]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[2]));

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[2]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[3]));

    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[3]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[4]));

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[4]), 64);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[5]));

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[5]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[6]));

    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[6]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[7]));

    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[7]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[8]));

    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[8]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[9]));

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[9]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[10]));

    return hash[10].trim256();
}

template<typename T1>
inline uint256 HashX13(const T1 pbegin, const T1 pend)

{
    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_skein512_context     ctx_skein;
    sph_luffa512_context     ctx_luffa;
    sph_cubehash512_context  ctx_cubehash;
    sph_shavite512_context   ctx_shavite;
    sph_simd512_context      ctx_simd;
    sph_echo512_context      ctx_echo;
    sph_hamsi512_context     ctx_hamsi;
    sph_fugue512_context     ctx_fugue;
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif
    
    uint512 hash[17];

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[0]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[0]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[1]));

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[1]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[2]));

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[2]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[3]));
    
    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[3]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[4]));
    
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[4]), 64);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[5]));

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[5]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[6]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[6]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[7]));
    
    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[7]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[8]));
        
    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[8]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[9]));

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[9]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[10]));

    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512 (&ctx_hamsi, static_cast<const void*>(&hash[10]), 64);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[11]));

    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[11]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[12]));

    return hash[12].trim256();
}

template<typename T1>
inline uint256 HashX14(const T1 pbegin, const T1 pend)

{
    sph_blake512_context      ctx_blake;
    sph_bmw512_context        ctx_bmw;
    sph_groestl512_context    ctx_groestl;
    sph_jh512_context         ctx_jh;
    sph_keccak512_context     ctx_keccak;
    sph_skein512_context      ctx_skein;
    sph_luffa512_context      ctx_luffa;
    sph_cubehash512_context   ctx_cubehash;
    sph_shavite512_context    ctx_shavite;
    sph_simd512_context       ctx_simd;
    sph_echo512_context       ctx_echo;
    sph_hamsi512_context      ctx_hamsi;
    sph_fugue512_context      ctx_fugue;
    sph_shabal512_context     ctx_shabal;
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif
    
    uint512 hash[14];

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[0]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[0]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[1]));

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[1]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[2]));

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[2]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[3]));
    
    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[3]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[4]));
    
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[4]), 64);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[5]));

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[5]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[6]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[6]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[7]));
    
    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[7]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[8]));
        
    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[8]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[9]));

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[9]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[10]));

    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512 (&ctx_hamsi, static_cast<const void*>(&hash[10]), 64);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[11]));

    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[11]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[12]));

    sph_shabal512_init(&ctx_shabal);
    sph_shabal512 (&ctx_shabal, static_cast<const void*>(&hash[12]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[13]));

    return hash[13].trim256();
}

template<typename T1>
inline uint256 HashX15(const T1 pbegin, const T1 pend)

{
    sph_blake512_context      ctx_blake;
    sph_bmw512_context        ctx_bmw;
    sph_groestl512_context    ctx_groestl;
    sph_jh512_context         ctx_jh;
    sph_keccak512_context     ctx_keccak;
    sph_skein512_context      ctx_skein;
    sph_luffa512_context      ctx_luffa;
    sph_cubehash512_context   ctx_cubehash;
    sph_shavite512_context    ctx_shavite;
    sph_simd512_context       ctx_simd;
    sph_echo512_context       ctx_echo;
    sph_hamsi512_context      ctx_hamsi;
    sph_fugue512_context      ctx_fugue;
    sph_shabal512_context     ctx_shabal;
    sph_whirlpool_context     ctx_whirlpool;
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif
    
    uint512 hash[15];

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[0]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[0]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[1]));

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[1]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[2]));

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[2]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[3]));
    
    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[3]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[4]));
    
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[4]), 64);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[5]));

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[5]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[6]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[6]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[7]));
    
    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[7]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[8]));
        
    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[8]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[9]));

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[9]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[10]));

    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512 (&ctx_hamsi, static_cast<const void*>(&hash[10]), 64);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[11]));

    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[11]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[12]));

    sph_shabal512_init(&ctx_shabal);
    sph_shabal512 (&ctx_shabal, static_cast<const void*>(&hash[12]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[13]));

    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[13]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[14]));

    return hash[14].trim256();
}

template<typename T1>
inline uint256 HashX17(const T1 pbegin, const T1 pend)
{
    sph_blake512_context      ctx_blake;
    sph_bmw512_context        ctx_bmw;
    sph_groestl512_context    ctx_groestl;
    sph_jh512_context         ctx_jh;
    sph_keccak512_context     ctx_keccak;
    sph_skein512_context      ctx_skein;
    sph_luffa512_context      ctx_luffa;
    sph_cubehash512_context   ctx_cubehash;
    sph_shavite512_context    ctx_shavite;
    sph_simd512_context       ctx_simd;
    sph_echo512_context       ctx_echo;
    sph_hamsi512_context      ctx_hamsi;
    sph_fugue512_context      ctx_fugue;
    sph_shabal512_context     ctx_shabal;
    sph_whirlpool_context     ctx_whirlpool;
    sph_sha512_context        ctx_sha2;
    sph_haval256_5_context    ctx_haval;
static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif
    
    uint512 hash[17];

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[0]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[0]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[1]));

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[1]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[2]));

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[2]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[3]));
    
    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[3]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[4]));
    
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[4]), 64);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[5]));

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[5]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[6]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[6]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[7]));
    
    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[7]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[8]));
        
    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[8]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[9]));

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[9]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[10]));

    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512 (&ctx_hamsi, static_cast<const void*>(&hash[10]), 64);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[11]));

    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[11]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[12]));

    sph_shabal512_init(&ctx_shabal);
    sph_shabal512 (&ctx_shabal, static_cast<const void*>(&hash[12]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[13]));

    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[13]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[14]));

    sph_sha512_init(&ctx_sha2);
    sph_sha512 (&ctx_sha2, static_cast<const void*>(&hash[14]), 64);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[15]));

    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5 (&ctx_haval, static_cast<const void*>(&hash[15]), 64);
    sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[16]));


    return hash[16].trim256();
}

template<typename T1>
inline uint256 XEVAN(const T1 pbegin, const T1 pend)
{
    sph_blake512_context      ctx_blake;
    sph_bmw512_context        ctx_bmw;
    sph_groestl512_context    ctx_groestl;
    sph_jh512_context         ctx_jh;
    sph_keccak512_context     ctx_keccak;
    sph_skein512_context      ctx_skein;
    sph_luffa512_context      ctx_luffa;
    sph_cubehash512_context   ctx_cubehash;
    sph_shavite512_context    ctx_shavite;
    sph_simd512_context       ctx_simd;
    sph_echo512_context       ctx_echo;
    sph_hamsi512_context      ctx_hamsi;
    sph_fugue512_context      ctx_fugue;
    sph_shabal512_context     ctx_shabal;
    sph_whirlpool_context     ctx_whirlpool;
    sph_sha512_context        ctx_sha2;
    sph_haval256_5_context    ctx_haval;
    static unsigned char pblank[1];

    int worknumber =128;
    uint512 hash[34];

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[0]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[0]), worknumber);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[1]));

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[1]), worknumber);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[2]));

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[2]), worknumber);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[3]));
    
    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[3]), worknumber);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[4]));
    
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[4]), worknumber);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[5]));

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[5]), worknumber);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[6]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[6]), worknumber);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[7]));
    
    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[7]), worknumber);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[8]));
        
    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[8]), worknumber);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[9]));

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[9]), worknumber);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[10]));

    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512 (&ctx_hamsi, static_cast<const void*>(&hash[10]), worknumber);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[11]));

    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[11]), worknumber);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[12]));

    sph_shabal512_init(&ctx_shabal);
    sph_shabal512 (&ctx_shabal, static_cast<const void*>(&hash[12]), worknumber);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[13]));

    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[13]), worknumber);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[14]));

    sph_sha512_init(&ctx_sha2);
    sph_sha512 (&ctx_sha2, static_cast<const void*>(&hash[14]), worknumber);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[15]));

    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5 (&ctx_haval, static_cast<const void*>(&hash[15]), worknumber);
    sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[16]));
	
    ///  Part2
    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, static_cast<const void*>(&hash[16]), worknumber);
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[17]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[17]), worknumber);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[18]));

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[18]), worknumber);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[19]));

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[19]), worknumber);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[20]));
    
    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[20]), worknumber);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[21]));
    
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[21]), worknumber);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[22]));

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[22]), worknumber);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[23]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[23]), worknumber);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[24]));
    
    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[24]), worknumber);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[25]));
        
    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[25]), worknumber);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[26]));

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[26]), worknumber);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[27]));

    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512 (&ctx_hamsi, static_cast<const void*>(&hash[27]), worknumber);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[28]));

    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[28]), worknumber);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[29]));

    sph_shabal512_init(&ctx_shabal);
    sph_shabal512 (&ctx_shabal, static_cast<const void*>(&hash[29]), worknumber);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[30]));

    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[30]), worknumber);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[31]));

    sph_sha512_init(&ctx_sha2);
    sph_sha512 (&ctx_sha2, static_cast<const void*>(&hash[31]), worknumber);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[32]));

    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5 (&ctx_haval, static_cast<const void*>(&hash[32]), worknumber);
    sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[33]));

    return hash[33].trim256();
}

template<typename T1>
inline uint256 NIST5(const T1 pbegin, const T1 pend)
{
    sph_blake512_context     ctx_blake;
    sph_groestl512_context   ctx_groestl;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_skein512_context     ctx_skein;

    static unsigned char pblank[1];
    uint512 hash[5];

    sph_blake512_init(&ctx_blake);
    sph_blake512(&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[0]));

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512(&ctx_groestl, static_cast<const void*>(&hash[0]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[1]));

    sph_jh512_init(&ctx_jh);
    sph_jh512(&ctx_jh, static_cast<const void*>(&hash[1]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[2]));

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512(&ctx_keccak, static_cast<const void*>(&hash[2]), 64);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[3]));

    sph_skein512_init(&ctx_skein);
    sph_skein512(&ctx_skein, static_cast<const void*>(&hash[3]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[4]));

    return hash[4].trim256();
}

template<typename T1>
inline uint256 PawelHash(const T1 pbegin, const T1 pend)
{
    /* HUNT Pawels Algo. (PawelHash) */
    
    sph_fugue512_context     ctx_fugue;
    sph_sha512_context       ctx_sha2;
    sph_skein512_context     ctx_skein;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_luffa512_context     ctx_luffa;
    sph_whirlpool_context    ctx_whirlpool;
    sph_shabal512_context    ctx_shabal;
    sph_echo512_context      ctx_echo;
    sph_groestl512_context   ctx_groestl;
    sph_haval256_5_context   ctx_haval;
    sph_bmw512_context       ctx_bmw;
    sph_gost512_context      ctx_gost;

    static unsigned char pblank[1];
    uint512 hash[19];

    sph_fugue512_init(&ctx_fugue);
    sph_fugue512(&ctx_fugue, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[0]));

    sph_sha512_init(&ctx_sha2);
    sph_sha512(&ctx_sha2, static_cast<const void*>(&hash[0]), 64);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[1]));
    
    sph_skein512_init(&ctx_skein);
    sph_skein512(&ctx_skein, static_cast<const void*>(&hash[1]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[2]));

    sph_jh512_init(&ctx_jh);
    sph_jh512(&ctx_jh, static_cast<const void*>(&hash[2]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[3]));

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512(&ctx_keccak, static_cast<const void*>(&hash[3]), 64);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[4]));
    
    sph_luffa512_init(&ctx_luffa);
    sph_luffa512(&ctx_luffa, static_cast<const void*>(&hash[4]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[5]));
    
    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool(&ctx_whirlpool, static_cast<const void*>(&hash[5]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[6]));
    
    sph_shabal512_init(&ctx_shabal);
    sph_shabal512(&ctx_shabal, static_cast<const void*>(&hash[6]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[7]));
    
    sph_echo512_init(&ctx_echo);
    sph_echo512(&ctx_echo, static_cast<const void*>(&hash[7]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[8]));
    
    sph_groestl512_init(&ctx_groestl);
    sph_groestl512(&ctx_groestl, static_cast<const void*>(&hash[8]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[9]));
    
    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5(&ctx_haval, static_cast<const void*>(&hash[9]), 64);
    sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[10]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512(&ctx_bmw, static_cast<const void*>(&hash[10]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[11]));
    
    // PawelHash Part 2: Mix some algorithms.
    
    sph_echo512_init(&ctx_echo);
    sph_echo512(&ctx_echo, static_cast<const void*>(&hash[11]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[12]));
    
    sph_fugue512_init(&ctx_fugue);
    sph_fugue512(&ctx_fugue, static_cast<const void*>(&hash[12]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[13]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512(&ctx_bmw, static_cast<const void*>(&hash[13]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[14]));

    sph_gost512_init(&ctx_gost);
    sph_gost512(&ctx_gost, static_cast<const void*>(&hash[14]), 64);
    sph_gost512_close(&ctx_gost, static_cast<void*>(&hash[15]));
    
    sph_shabal512_init(&ctx_shabal);
    sph_shabal512(&ctx_shabal, static_cast<const void*>(&hash[15]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[16]));
    
    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool(&ctx_whirlpool, static_cast<const void*>(&hash[16]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[17]));
    
    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[17]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[18]));

    return hash[18].trim256();
}

template<typename T1>
inline uint256 AstralHash(const T1 pbegin, const T1 pend)
{
    /* HUNT Astrali's Algo. (AstralHash) */
    
    sph_luffa512_context     ctx_luffa;
    sph_skein512_context     ctx_skein;
    sph_echo512_context      ctx_echo;
    sph_whirlpool_context    ctx_whirlpool;
    sph_bmw512_context       ctx_bmw; 
    sph_blake512_context     ctx_blake;
    sph_shavite512_context   ctx_shavite;
    sph_fugue512_context     ctx_fugue;
    sph_hamsi512_context     ctx_hamsi;
    sph_haval256_5_context   ctx_haval;
    sph_sha512_context       ctx_sha2;

    static unsigned char pblank[1];
    uint512 hash[13];

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512(&ctx_luffa, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[0]));

    sph_skein512_init(&ctx_skein);
    sph_skein512(&ctx_skein, static_cast<const void*>(&hash[0]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[1]));
    
    sph_echo512_init(&ctx_echo);
    sph_echo512(&ctx_echo, static_cast<const void*>(&hash[1]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[2]));
    
    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool(&ctx_whirlpool, static_cast<const void*>(&hash[2]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[3]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512(&ctx_bmw, static_cast<const void*>(&hash[3]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[4]));
    
    sph_blake512_init(&ctx_blake);
    sph_blake512(&ctx_blake, static_cast<const void*>(&hash[4]), 64);
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[5]));
    
    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[5]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[6]));
    
    sph_skein512_init(&ctx_skein);
    sph_skein512(&ctx_skein, static_cast<const void*>(&hash[6]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[7]));
    
    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool(&ctx_whirlpool, static_cast<const void*>(&hash[7]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[8]));
    
    sph_fugue512_init(&ctx_fugue);
    sph_fugue512(&ctx_fugue, static_cast<const void*>(&hash[8]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[9]));
    
    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512(&ctx_hamsi, static_cast<const void*>(&hash[9]), 64);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[10]));
    
    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5(&ctx_haval, static_cast<const void*>(&hash[10]), 64);
    sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[11]));
    
    sph_sha512_init(&ctx_sha2);
    sph_sha512(&ctx_sha2, static_cast<const void*>(&hash[11]), 64);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[12]));

    return hash[12].trim256();
}

template<typename T1>
inline uint256 PadiHash(const T1 pbegin, const T1 pend)
{
    /* HUNT Padis Algo. (PadiHash) */
    
    sph_sha512_context       ctx_sha2;
    sph_jh512_context        ctx_jh;
    sph_luffa512_context     ctx_luffa;
    sph_echo512_context      ctx_echo;
    sph_bmw512_context       ctx_bmw; 
    sph_haval256_5_context   ctx_haval;
    sph_cubehash512_context  ctx_cubehash;
    sph_shabal512_context    ctx_shabal;

    static unsigned char pblank[1];
    uint512 hash[26];

    sph_sha512_init(&ctx_sha2);
    sph_sha512(&ctx_sha2, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[0]));

    sph_jh512_init(&ctx_jh);
    sph_jh512(&ctx_jh, static_cast<const void*>(&hash[0]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[1]));
    
    sph_luffa512_init(&ctx_luffa);
    sph_luffa512(&ctx_luffa, static_cast<const void*>(&hash[1]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[2]));
    
    sph_echo512_init(&ctx_echo);
    sph_echo512(&ctx_echo, static_cast<const void*>(&hash[2]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[3]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512(&ctx_bmw, static_cast<const void*>(&hash[3]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[4]));
    
    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5(&ctx_haval, static_cast<const void*>(&hash[4]), 64);
    sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[5]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512(&ctx_cubehash, static_cast<const void*>(&hash[5]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[6]));
    
    sph_shabal512_init(&ctx_shabal);
    sph_shabal512(&ctx_shabal, static_cast<const void*>(&hash[6]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[7]));
    
    // PadiHash Part 2: Hash the same again.
    
    sph_sha512_init(&ctx_sha2);
    sph_sha512(&ctx_sha2, static_cast<const void*>(&hash[7]), 64);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[8]));

    sph_jh512_init(&ctx_jh);
    sph_jh512(&ctx_jh, static_cast<const void*>(&hash[8]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[9]));
    
    sph_luffa512_init(&ctx_luffa);
    sph_luffa512(&ctx_luffa, static_cast<const void*>(&hash[9]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[10]));
    
    sph_echo512_init(&ctx_echo);
    sph_echo512(&ctx_echo, static_cast<const void*>(&hash[10]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[11]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512(&ctx_bmw, static_cast<const void*>(&hash[11]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[12]));
    
    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5(&ctx_haval, static_cast<const void*>(&hash[12]), 64);
    sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[13]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512(&ctx_cubehash, static_cast<const void*>(&hash[13]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[14]));
    
    sph_shabal512_init(&ctx_shabal);
    sph_shabal512(&ctx_shabal, static_cast<const void*>(&hash[14]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[15]));
    
    // PadiHash Part 3: Hash the last part in reverse order.
    
    sph_shabal512_init(&ctx_shabal);
    sph_shabal512(&ctx_shabal, static_cast<const void*>(&hash[15]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[16]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512(&ctx_cubehash, static_cast<const void*>(&hash[16]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[17]));
    
    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5(&ctx_haval, static_cast<const void*>(&hash[17]), 64);
    sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[18]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512(&ctx_bmw, static_cast<const void*>(&hash[18]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[19]));
    
    sph_echo512_init(&ctx_echo);
    sph_echo512(&ctx_echo, static_cast<const void*>(&hash[19]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[20]));
    
    sph_luffa512_init(&ctx_luffa);
    sph_luffa512(&ctx_luffa, static_cast<const void*>(&hash[20]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[21]));
    
    sph_jh512_init(&ctx_jh);
    sph_jh512(&ctx_jh, static_cast<const void*>(&hash[21]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[22]));
    
    sph_sha512_init(&ctx_sha2);
    sph_sha512(&ctx_sha2, static_cast<const void*>(&hash[22]), 64);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[23]));
    
    // Finalize this hash.
    
    sph_jh512_init(&ctx_jh);
    sph_jh512(&ctx_jh, static_cast<const void*>(&hash[23]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[24]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512(&ctx_bmw, static_cast<const void*>(&hash[24]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[25]));

    return hash[25].trim256();
}

template<typename T1>
inline uint256 JeongHash(const T1 pbegin, const T1 pend)
{
    /* HUNT Jeong's Algo. (JeongHash) */
    
    sph_simd512_context      ctx_simd;
    sph_hamsi512_context     ctx_hamsi;
    sph_shabal512_context    ctx_shabal;
    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_sha512_context       ctx_sha2;
    sph_whirlpool_context    ctx_whirlpool;
    sph_skein512_context     ctx_skein;

    static unsigned char pblank[1];
    uint512 hash[24];

    sph_simd512_init(&ctx_simd);
    sph_simd512(&ctx_simd, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[0]));

    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512(&ctx_hamsi, static_cast<const void*>(&hash[0]), 64);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[1]));
    
    sph_shabal512_init(&ctx_shabal);
    sph_shabal512(&ctx_shabal, static_cast<const void*>(&hash[1]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[2]));
    
    sph_blake512_init(&ctx_blake);
    sph_blake512(&ctx_blake, static_cast<const void*>(&hash[2]), 64);
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[3]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512(&ctx_bmw, static_cast<const void*>(&hash[3]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[4]));
    
    sph_sha512_init(&ctx_sha2);
    sph_sha512(&ctx_sha2, static_cast<const void*>(&hash[4]), 64);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[5]));
    
    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool(&ctx_whirlpool, static_cast<const void*>(&hash[5]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[6]));
    
    sph_skein512_init(&ctx_skein);
    sph_skein512(&ctx_skein, static_cast<const void*>(&hash[6]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[7]));
    
    // JeongHash Part 2: Hash in reverse order
    
    sph_skein512_init(&ctx_skein);
    sph_skein512(&ctx_skein, static_cast<const void*>(&hash[7]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[8]));
    
    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool(&ctx_whirlpool, static_cast<const void*>(&hash[8]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[9]));
    
    sph_sha512_init(&ctx_sha2);
    sph_sha512(&ctx_sha2, static_cast<const void*>(&hash[9]), 64);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[10]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512(&ctx_bmw, static_cast<const void*>(&hash[10]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[11]));
    
    sph_blake512_init(&ctx_blake);
    sph_blake512(&ctx_blake, static_cast<const void*>(&hash[11]), 64);
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[12]));
    
    sph_shabal512_init(&ctx_shabal);
    sph_shabal512(&ctx_shabal, static_cast<const void*>(&hash[12]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[13]));
    
    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512(&ctx_hamsi, static_cast<const void*>(&hash[13]), 64);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[14]));
    
    sph_simd512_init(&ctx_simd);
    sph_simd512(&ctx_simd, static_cast<const void*>(&hash[14]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[15]));
    
    // Hash again
    
    sph_simd512_init(&ctx_simd);
    sph_simd512(&ctx_simd, static_cast<const void*>(&hash[15]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[16]));

    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512(&ctx_hamsi, static_cast<const void*>(&hash[16]), 64);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[17]));
    
    sph_shabal512_init(&ctx_shabal);
    sph_shabal512(&ctx_shabal, static_cast<const void*>(&hash[17]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[18]));
    
    sph_blake512_init(&ctx_blake);
    sph_blake512(&ctx_blake, static_cast<const void*>(&hash[18]), 64);
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[19]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512(&ctx_bmw, static_cast<const void*>(&hash[19]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[20]));
    
    sph_sha512_init(&ctx_sha2);
    sph_sha512(&ctx_sha2, static_cast<const void*>(&hash[20]), 64);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[21]));
    
    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool(&ctx_whirlpool, static_cast<const void*>(&hash[21]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[22]));
    
    sph_skein512_init(&ctx_skein);
    sph_skein512(&ctx_skein, static_cast<const void*>(&hash[22]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[23]));

    return hash[23].trim256();
}

template<typename T1>
inline uint256 GlobalHash(const T1 pbegin, const T1 pend)
{
    sph_gost512_context      ctx_gost;
    sph_blake512_context     ctx_blake;
    blake2b_state            ctx_blake2b[1];
    blake2s_state            ctx_blake2s[1];
    
    static unsigned char pblank[1];

    uint512 hash[3];
    uint256 finalhash;
    
    sph_gost512_init(&ctx_gost);
    sph_gost512 (&ctx_gost, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0])); 
    sph_gost512_close(&ctx_gost, static_cast<void*>(&hash[0]));
    
    sph_blake512_init(&ctx_blake);
    sph_blake512(&ctx_blake, static_cast<const void*>(&hash[0]), 64);
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[1]));
    
    blake2b_init( ctx_blake2b, BLAKE2B_OUTBYTES );
    blake2b_update( ctx_blake2b, static_cast<const void*>(&hash[1]), 64 );
    blake2b_final( ctx_blake2b, static_cast<void*>(&hash[2]), BLAKE2B_OUTBYTES );
    
    blake2s_init( ctx_blake2s, BLAKE2S_OUTBYTES );
    blake2s_update( ctx_blake2s, static_cast<const void*>(&hash[2]), 64);
    blake2s_final( ctx_blake2s, static_cast<void*>(&finalhash), BLAKE2S_OUTBYTES );
    
    return finalhash;
}
#endif // MULTIHASH_H
