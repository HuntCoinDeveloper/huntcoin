// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The DigiByte Core developers
// Copyright (c) 2009-2017 The Funcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block_dependencies.h>

void CPureBlockVersion::SetBaseVersion(int32_t nBaseVersion, int32_t nChainId)
{
    //assert(nBaseVersion >= 1 && nBaseVersion < VERSION_AUXPOW);
    assert(!IsAuxpow());
    nVersion = nBaseVersion | (nChainId * VERSION_CHAIN_START);
}

std::string GetAlgoName(uint8_t Algo)
{
    switch (Algo)
    {
        case ALGO_SHA256D:
            return std::string("sha256d");
        case ALGO_SCRYPT:
            return std::string("scrypt");
        case ALGO_X11:
            return std::string("x11");
        case ALGO_NEOSCRYPT:
            return std::string("neoscrypt");
        case ALGO_YESCRYPT:
            return std::string("yescrypt");
        case ALGO_EQUIHASH:
            return std::string("equihash");
        case ALGO_HMQ1725:
            return std::string("hmq1725");
        case ALGO_XEVAN:
            return std::string("xevan");
        case ALGO_NIST5:
            return std::string("nist5");
        case ALGO_TIMETRAVEL10:
            return std::string("timetravel10");
        case ALGO_PAWELHASH:
            return std::string("pawelhash");
        case ALGO_X13:
            return std::string("x13");
        case ALGO_X14:
            return std::string("x14");
        case ALGO_X15:
            return std::string("x15");
        case ALGO_X17:
            return std::string("x17");
        case ALGO_LYRA2RE:
            return std::string("lyra2re");
        case ALGO_BLAKE2S:
            return std::string("blake2s");
        case ALGO_BLAKE2B:
            return std::string("blake2b");
        case ALGO_ASTRALHASH:
            return std::string("astralhash");
        case ALGO_PADIHASH:
            return std::string("padihash");
        case ALGO_JEONGHASH:
            return std::string("jeonghash");
        case ALGO_KECCAK:
            return std::string("keccak");
        case ALGO_ZHASH:
            return std::string("zhash");
        case ALGO_GLOBALHASH:
            return std::string("globalhash");
        case ALGO_SKEIN:
            return std::string("skein");
        case ALGO_GROESTL:
            return std::string("groestl");
        case ALGO_QUBIT:
            return std::string("qubit");
        case ALGO_SKUNKHASH:
            return std::string("skunkhash");
        case ALGO_QUARK:
            return std::string("quark");
        case ALGO_X16R:
            return std::string("x16r");
    }
    return std::string("unknown");       
}