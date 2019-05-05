// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bittcoin Core developers
// Copyright (c) 2009-2017 The DigiByte Core developers
// Copyright (c) 2013-2014 Phoenixcoin Developers
// Copyright (c) 2016-2018 The CryptoCoderz Team / Espers
// Copyright (c) 2017-2018 The AmsterdamCoin developers
// Copyright (c) 2009-2016 The Litecoin Core developers
// Copyright (c) 2014-2017 The Mun Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The HuntCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/mining_block.h>

#include <hash.h>
#include <tinyformat.h>
#include <utilstrencodings.h>
#include <chainparams.h>
#include <crypto/common.h>
#include <crypto/algos/hashlib/multihash.h>
#include <crypto/algos/neoscrypt/neoscrypt.h>
#include <crypto/algos/scrypt/scrypt.h>
#include <crypto/algos/yescrypt/yescrypt.h>
#include <crypto/algos/Lyra2RE/Lyra2RE.h>
#include <crypto/algos/blake/hashblake.h>

uint256 CDefaultBlockHeader::GetHash() const
{
    return SerializeHash(*this);
}

uint256 CEquihashBlockHeader::GetHash() const
{
    return SerializeHash(*this);
}

uint256 CDefaultBlockHeader::GetPoWHash(uint8_t algo) const
{
    switch (algo)
    {
        case ALGO_SHA256D:
            return GetHash();
        case ALGO_SCRYPT:
        {
            uint256 thash;
            scrypt_1024_1_1_256(BEGIN(nVersion), BEGIN(thash));
            return thash;
        }
        case ALGO_X11:
        {
            return HashX11(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_NEOSCRYPT:
        {
            unsigned int profile = 0x0;
            uint256 thash;
            neoscrypt((unsigned char *) &nVersion, (unsigned char *) &thash, profile);				
            return thash;
        }
        case ALGO_EQUIHASH:
            return GetHash();
        case ALGO_YESCRYPT:
        {
            uint256 thash;
            yescrypt_hash(BEGIN(nVersion), BEGIN(thash));
            return thash;
        }
        case ALGO_HMQ1725:
        {
            return HMQ1725(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_XEVAN:
        {
            return XEVAN(BEGIN(nVersion), END(nNonce));	    
        }
        case ALGO_NIST5:
        {
            return NIST5(BEGIN(nVersion), END(nNonce));	    
        }
        case ALGO_TIMETRAVEL10:
        {
            return HashTimeTravel(BEGIN(nVersion), END(nNonce), nTime);	    
        }
        case ALGO_PAWELHASH:
        {
            return PawelHash(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_X13:
        {
            return HashX13(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_X14:
        {
            return HashX14(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_X15:
        {
            return HashX15(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_X17:
        {
            return HashX17(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_LYRA2RE:
        {
            uint256 thash;
            lyra2re2_hash(BEGIN(nVersion), BEGIN(thash));
            return thash;
        }
        case ALGO_BLAKE2S:
        {
            return HashBlake2S(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_BLAKE2B:
        {
            return HashBlake2B(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_ASTRALHASH:
        {
            return AstralHash(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_PADIHASH:
        {
            return PadiHash(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_JEONGHASH:
        {
            return JeongHash(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_KECCAK:
        {
            return HashKeccak(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_ZHASH:
        {
            return GetHash();
        }
        case ALGO_GLOBALHASH:
        {
            return GlobalHash(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_GROESTL:
        {
            return HashGroestl(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_SKEIN:
        {
            return HashSkein(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_QUBIT:
        {
            return HashQubit(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_SKUNKHASH:
        {
            return SkunkHash5(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_QUARK:
        {
            return QUARK(BEGIN(nVersion), END(nNonce));
        }
        case ALGO_X16R:
        {
            return HashX16R(BEGIN(nVersion), END(nNonce), hashPrevBlock);
        }
    }
    return GetHash();
}

std::string CDefaultBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CDefaultBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}

std::string CEquihashBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CEquihashBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%s, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce.GetHex(),
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}