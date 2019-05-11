// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin Core developers
// Copyright (c) 2019 The Huntcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HASH_BLAKE_H
#define HASH_BLAKE_H

#include "blake2.h"
#include <uint256.h>

template<typename T1>
inline uint256 HashBlake2S(const T1 pbegin, const T1 pend)
{
    static unsigned char pblank[1];
    uint256 hash1;
    blake2s_state S[1];
    blake2s_init( S, BLAKE2S_OUTBYTES );
    blake2s_update( S, (pbegin == pend ? pblank : (unsigned char*)&pbegin[0]), (pend - pbegin) * sizeof(pbegin[0]) );
    blake2s_final( S, (unsigned char*)&hash1, BLAKE2S_OUTBYTES );
    return hash1;
}

template<typename T1>
inline uint256 HashBlake2B(const T1 pbegin, const T1 pend)
{
    static unsigned char pblank[1];
    uint512 hash1;
    blake2b_state S[1];
    blake2b_init( S, BLAKE2B_OUTBYTES );
    blake2b_update( S, (pbegin == pend ? pblank : (unsigned char*)&pbegin[0]), (pend - pbegin) * sizeof(pbegin[0]) );
    blake2b_final( S, (unsigned char*)&hash1, BLAKE2B_OUTBYTES );
    return hash1.trim256();
}

#endif // HASH_BLAKE_H