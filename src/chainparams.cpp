// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2009-2017 The DigiByte Core developers
// Copyright (c) 2016-2017 The Zcash developers
// Copyright (c) 2018 The Bitcoin Private developers
// Copyright (c) 2017-2018 The Bitcoin Gold developers
// Copyright (c) 2019 The Huntcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <base58.h> // For CTxDestination
#include <chainparams.h>
#include <consensus/merkle.h>
#include <primitives/mining_block.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

// For equihash_parameters_acceptable.
#include <crypto/algos/equihash/equihash.h>
#include <net.h>
#include <validation.h>
#define equihash_parameters_acceptable(N, K) \
    ((CEquihashBlockHeader::HEADER_SIZE + equihash_solution_size(N, K))*MAX_HEADERS_RESULTS < \
     MAX_PROTOCOL_MESSAGE_LENGTH-1000)

#include <assert.h>

#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Friday, May 17, 2019 17:06:19 GMT+02:00 Huntcoin established in Africa";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMasternodeColleteralPaymentAmount = 10000;
        consensus.nMasternodePayeeReward = 25;
        consensus.nInstantSendConfirmationsRequired = 6;
        consensus.nInstantSendKeepLock = 24;
        consensus.nTreasuryAddressChange = 133920;
        consensus.nTreasuryAddressChangeStart = 500000;
        consensus.nTreasuryAmount = 15;
        consensus.BIP16Height = 100000;
        consensus.BIP34Height = 299999;
        consensus.BIP34Hash = uint256S("0x0000000000000181717c02ef5cebbfb3568887de4e6cb30525ac7b6f5a0b998c");
        consensus.BIP65Height = 380000; // not hashed yet ...
        consensus.BIP66Height = 360000; // not hashed yet ...
        consensus.HardforkHeight = 327036;
        consensus.HardforkTime = 1537617600;
        consensus.HardforkHash = uint256S("0xfa2a1f17edbb39496a4d1c9ee643797bc2b0d72dd9038e3646872c0fd7d3fd56");	
        consensus.powLimit_SHA256 = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_SCRYPT = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X11 = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.powLimit_NEOSCRYPT = uint256S("00001fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_EQUIHASH = uint256S("0007ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_YESCRYPT = uint256S("0003ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_HMQ1725 = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_XEVAN = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_NIST5 = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_TIMETRAVEL10 = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_PAWELHASH = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X13 = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X14 = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X15 = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X17 = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_LYRA2RE = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_BLAKE2S = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_BLAKE2B = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_ASTRALHASH = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_PADIHASH = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_JEONGHASH = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_ZHASH = uint256S("0007ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_KECCAK = uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_GLOBALHASH = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_QUBIT = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_SKEIN = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_GROESTL = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_SKUNKHASH = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_QUARK = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X16R = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nTargetSpacing = 60; // 1 minute
        consensus.nTargetTimespan =  60; // 5 minutes
        consensus.nPowTargetTimespan = 10 * 60; // ten minutes
        consensus.nPowTargetSpacing = 60;
        consensus.nPowTargetSpacingV2 = 60 * NUM_ALGOS; // NUM_ALGOS * 60
        consensus.nInterval = consensus.nTargetTimespan / consensus.nTargetSpacing;
        consensus.nAveragingInterval = 5; // 5 blocks
        consensus.nAveragingTargetTimespan = consensus.nAveragingInterval * consensus.nPowTargetSpacingV2;
        consensus.nMaxAdjustDown = 16; // 16% adjustment down
        consensus.nMaxAdjustUp = 8; // 8% adjustment up
        consensus.nMinActualTimespan = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUp) / 100;
        consensus.nMaxActualTimespan = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDown) / 100;
        consensus.nLocalTargetAdjustment = 4; //difficulty adjustment per algo
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 8; // 95% of 2016 // Changed to 8 because 9.5 is up to ten.
        consensus.nMinerConfirmationWindow = 10; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1506729600; // Sat, 30 Sep 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1509494400; // Wed, 01 Nov 2017

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1509494400; // Wed, 01 Nov 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1519862400; // Thu, 01 Mar 2018.

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000006ca5a7a5a45e8f8b9c");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000000000000014cf4dc216dcc925bf0c6d7096aa6ab82e1af64e946d876df7d"); //200000
        
        consensus.nAuxpowChainId = 0x003c; 
        consensus.fStrictChainId = false;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xc7;
        pchMessageStart[1] = 0x08;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0x2d;
        nDefaultPort = 7377;
        nPruneAfterHeight = 750000;
        const size_t N = 200, K = 9;
        const size_t ZN = 144, ZK = 5;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(ZN, ZK));
        nEquihashN = N;
        nEquihashK = K;
        nZhashN = ZN;
        nZhashK = ZK;

        genesis = CreateGenesisBlock(1558105579, 2864352084, 0x1d00ffff, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000000fe3e3e93344a6b73888137397413eb11f601b4231b5196390d24d3b6"));
        assert(genesis.hashMerkleRoot == uint256S("0xe217ce769444458c180ca6a5944cbbc22828f377cfd0e1790158034299827ffc"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
        vSeeds.emplace_back("160.119.100.89"); // Huntcoin base node
        //vSeeds.emplace_back("huntcoin.africa"); // HuntCoin base node II
        //vSeeds.emplace_back("explorer.huntcoin.africa"); // HuntCoin base node III
        //vSeeds.emplace_back("lameserver.de"); // HuntCoin Node by Astrali
        //vSeeds.emplace_back("pool.cryptopowered.club"); // HuntCoin Cryptopowered node
        //vSeeds.emplace_back("bit2pool.com"); // HuntCoin Bit2Pool node
        // Hardfork Seednodes
        //vSeeds.emplace_back("185.206.144.200"); // HuntCoin Hardfork node: 01/18
        //vSeeds.emplace_back("185.206.145.201"); // HuntCoin Hardfork node: 02/18
        //vSeeds.emplace_back("185.206.146.200"); // HuntCoin Hardfork node: 03/18
        //vSeeds.emplace_back("185.206.147.203"); // HuntCoin Hardfork node: 04/18
        //vSeeds.emplace_back("185.205.209.67");  // HuntCoin Hardfork node: 05/18
        //vSeeds.emplace_back("185.206.147.202"); // HuntCoin Hardfork node: 06/18
        //vSeeds.emplace_back("185.205.209.137"); // HuntCoin Hardfork node: 07/18
        //vSeeds.emplace_back("185.203.119.194"); // HuntCoin Hardfork node: 08/18
        //vSeeds.emplace_back("185.203.119.195"); // HuntCoin Hardfork node: 09/18
        //vSeeds.emplace_back("185.206.144.201"); // HuntCoin Hardfork node: 10/18
        //vSeeds.emplace_back("185.141.62.86");   // HuntCoin Hardfork node: 11/18
        //vSeeds.emplace_back("185.141.62.87");   // HuntCoin Hardfork node: 12/18
        //vSeeds.emplace_back("185.141.62.88");   // HuntCoin Hardfork node: 13/18
        //vSeeds.emplace_back("185.141.62.89");   // HuntCoin Hardfork node: 14/18
        //vSeeds.emplace_back("185.141.62.90");   // HuntCoin Hardfork node: 15/18
        //vSeeds.emplace_back("185.141.62.91");   // HuntCoin Hardfork node: 16/18
        //vSeeds.emplace_back("185.141.62.92");   // HuntCoin Hardfork node: 17/18
        //vSeeds.emplace_back("185.203.118.117"); // HuntCoin Hardfork node: 18/18

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,38);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,166);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "gt";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fAllowMultiplePorts = false;
        
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        
        strSporkAddress = "GP4r6YBda72vWgmK7m9z8JGkq3smhipTYb";

        checkpointData = {
            {
                {     0, uint256S("0x00000000fe3e3e93344a6b73888137397413eb11f601b4231b5196390d24d3b6")},
                {   253, uint256S("0x000000000001a9597538194df736eda73c35c17d78ec14ac99b9d392d0892ce3")},
                { 44446, uint256S("0x000000000004ddd47d2e6033af4d034e63171d61e4eaca2702f9e8b9a8ffdb5a")},
                { 87757, uint256S("0x000000000001356d0e351660b8356f8f6a12a5b029b2c10a5b47d753b8cd8f29")},
                {174987, uint256S("0x0000000000004a80520dfce6d2017d6f403a9def13fe99629d31f6b7a90b7c31")},
                {214590, uint256S("0x00000000000003886a3080ff818eb6027a98f1ac33c532b730fbe4c0fde704ca")},
                {282595, uint256S("0x00000000000000e335a60ca393eee3445f551d5bf6987e47d3a70e043b8dff5b")},
                {300000, uint256S("0x00000000000000c22e9be2faab7b2f05b0e834f434b0a82b0a12b55351b9d3c4")},
                {327035, uint256S("0x0000000000000072f4e5960b252d812991c4c13810b2324d623f824572cb5251")}, // last old chain height
                {327036, uint256S("0xfa2a1f17edbb39496a4d1c9ee643797bc2b0d72dd9038e3646872c0fd7d3fd56")}, // firt hardfork chain block
                {328101, uint256S("0x320c067ac8c5cdebbd12df990556b1237f0b41c7dac54a232906f4ce7a180655")},
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 320c067ac8c5cdebbd12df990556b1237f0b41c7dac54a232906f4ce7a180655 (height 328101).
            1537709820, // * UNIX timestamp of last known number of transactions
            393073,     // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.0022863   // * estimated number of transactions per second after that timestamp
        };
        
        // Founders reward script expects a vector of 4-of-6 multisig addresses
        vFoundersRewardAddress = {
            //"38yCbLtxZiWybYjJB8msaASL8a9DqSGH9e", /* main-index: 0*/
            //"3LCZiCbkiyAH1saEXEnMC6XFVanVX6gftc", /* main-index: 1*/
            //"3E99o64BavBxN855kFqbVcaiTmu3jBtnqp", /* main-index: 2*/
            //"34KAMoFSwzKppWBg3u3XFMg1b6z3Xza9X6", /* main-index: 3*/
            //"37Yy1xuVTWgPjUi6spagvkDqHZS6e3e6a6", /* main-index: 4*/
            //"35NRzPB3NebkDgWu2w8vPNtDxVUixWpWTN", /* main-index: 5*/
            //"3ARcDbReyavaETa42ZRQivARWp6Mh5jDSX", /* main-index: 6*/
            //"3PFZ1oudGLkWg7kkV9qgosseuYsrhJd6ou", /* main-index: 7*/
            //"34EBnTUYk3kzhwn6oNni1eyQ83vap4iVxZ", /* main-index: 8*/
            //"37hNzkCuYGiVxP2AuMEmrBWQem4NQVUcJD", /* main-index: 9*/
            //"35eZ5UFfdb5687GTdAK29hthEyzuXNcbcv", /* main-index: 10*/
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMasternodeColleteralPaymentAmount = 12500;
        consensus.nMasternodePayeeReward = 32;
        consensus.nInstantSendConfirmationsRequired = 2;
        consensus.nInstantSendKeepLock = 6;
        consensus.nTreasuryAddressChange = 600000;
        consensus.nTreasuryAddressChangeStart = 100000;
        consensus.nTreasuryAmount = 18;
        consensus.BIP16Height = 1;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("00000000238f0fdbc6d992a183ecf735ce0009f5ae2088ce8014370fcaaec7e8");
        consensus.BIP65Height = 100; // not hashed yet.
        consensus.BIP66Height = 10; // not hashed yet.
        consensus.HardforkHeight = 2153; // not final
        consensus.HardforkTime = 1537185600;
        consensus.HardforkHash = uint256S("0x944140d0c734a7a94ca0b306cd3ad8c9bfe70889c927ca6c4852e5644b621733");
        consensus.powLimit_SHA256 = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_SCRYPT = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X11 = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.powLimit_NEOSCRYPT = uint256S("00001fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_EQUIHASH = uint256S("07ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_YESCRYPT = uint256S("0003ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_HMQ1725 = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_XEVAN = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_NIST5 = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_TIMETRAVEL10 = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_PAWELHASH = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X13 = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X14 = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X15 = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X17 = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_LYRA2RE = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_BLAKE2S = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_BLAKE2B = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_ASTRALHASH = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_PADIHASH = uint256S("00007fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_JEONGHASH = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_ZHASH = uint256S("07ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_KECCAK = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_GLOBALHASH = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_QUBIT = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_SKEIN = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_GROESTL = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_SKUNKHASH = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_QUARK = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X16R = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nTargetSpacing = 60; // 1 minute
        consensus.nTargetTimespan =  60; // 5 minutes
        consensus.nPowTargetTimespan = 10 * 60; // ten minutes
        consensus.nPowTargetSpacing = 60;
        consensus.nPowTargetSpacingV2 = 60 * NUM_ALGOS; // NUM_ALGOS * 60
        consensus.nInterval = consensus.nTargetTimespan / consensus.nTargetSpacing;
        consensus.nAveragingInterval = 5; // 5 blocks
        consensus.nAveragingTargetTimespan = consensus.nAveragingInterval * consensus.nPowTargetSpacingV2;
        consensus.nMaxAdjustDown = 16; // 16% adjustment down
        consensus.nMaxAdjustUp = 8; // 8% adjustment up
        consensus.nMinActualTimespan = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUp) / 100;
        consensus.nMaxActualTimespan = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDown) / 100;
        consensus.nLocalTargetAdjustment = 4; //difficulty adjustment per algo
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 8; // 75% for testchains
        consensus.nMinerConfirmationWindow = 10; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1506729600; // Sat, 30 Sep 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1509494400; // Wed, 01 Nov 2017

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1509494400; // Wed, 01 Nov 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1519862400; // Thu, 01 Mar 2018.

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000100010001");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00000000fe3e3e93344a6b73888137397413eb11f601b4231b5196390d24d3b6"); //0
        
        consensus.nAuxpowChainId = 0x0078; 
        consensus.fStrictChainId = false;

        pchMessageStart[0] = 0x3a;
        pchMessageStart[1] = 0x6f;
        pchMessageStart[2] = 0x37;
        pchMessageStart[3] = 0x5b;
        nDefaultPort = 17377;
        nPruneAfterHeight = 1000;
        const size_t N = 200, K = 9;  // Same as mainchain.
        const size_t ZN = 144, ZK = 5;  // Same as mainchain.
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(ZN, ZK));
        nEquihashN = N;
        nEquihashK = K;
        nZhashN = ZN;
        nZhashK = ZK;

        genesis = CreateGenesisBlock(1558105579, 2864352084, 0x1d00ffff, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000000fe3e3e93344a6b73888137397413eb11f601b4231b5196390d24d3b6"));
        assert(genesis.hashMerkleRoot == uint256S("0xe217ce769444458c180ca6a5944cbbc22828f377cfd0e1790158034299827ffc"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top

        vSeeds.emplace_back("160.119.100.89");
        vSeeds.emplace_back("lameserver.de"); // HuntCoin Node
        // Hardfork Seednodes
        //vSeeds.emplace_back("185.206.144.200"); // HuntCoin Hardfork node: 01/18
        //vSeeds.emplace_back("185.206.145.201"); // HuntCoin Hardfork node: 02/18
        //vSeeds.emplace_back("185.206.146.200"); // HuntCoin Hardfork node: 03/18
        //vSeeds.emplace_back("185.206.147.203"); // HuntCoin Hardfork node: 04/18
        //vSeeds.emplace_back("185.205.209.67");  // HuntCoin Hardfork node: 05/18
        //vSeeds.emplace_back("185.206.147.202"); // HuntCoin Hardfork node: 06/18
        //vSeeds.emplace_back("185.205.209.137"); // HuntCoin Hardfork node: 07/18
        //vSeeds.emplace_back("185.203.119.194"); // HuntCoin Hardfork node: 08/18
        //vSeeds.emplace_back("185.203.119.195"); // HuntCoin Hardfork node: 09/18
        //vSeeds.emplace_back("185.206.144.201"); // HuntCoin Hardfork node: 10/18
        //vSeeds.emplace_back("185.141.62.86");   // HuntCoin Hardfork node: 11/18
        //vSeeds.emplace_back("185.141.62.87");   // HuntCoin Hardfork node: 12/18
        //vSeeds.emplace_back("185.141.62.88");   // HuntCoin Hardfork node: 13/18
        //vSeeds.emplace_back("185.141.62.89");   // HuntCoin Hardfork node: 14/18
        //vSeeds.emplace_back("185.141.62.90");   // HuntCoin Hardfork node: 15/18
        //vSeeds.emplace_back("185.141.62.91");   // HuntCoin Hardfork node: 16/18
        //vSeeds.emplace_back("185.141.62.92");   // HuntCoin Hardfork node: 17/18
        //vSeeds.emplace_back("185.203.118.117"); // HuntCoin Hardfork node: 18/18

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tg";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fAllowMultiplePorts = false;
        
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        
        strSporkAddress = "mnGzwQeK4FkhQfYGMYKfuXHq29DJN1MVzd";


        checkpointData = {
            {
                {0, uint256S("00000000fe3e3e93344a6b73888137397413eb11f601b4231b5196390d24d3b6")},
                {1000, uint256S("00000000001f423e19a5ce9d10a1263dfbd83654da9183c25f7fcfd7fc25e458")},
                {2152, uint256S("000000002439acbc366328335e435f25e78ff1f884fabd00f359a66c7865a1f2")},
                {2153, uint256S("944140d0c734a7a94ca0b306cd3ad8c9bfe70889c927ca6c4852e5644b621733")},
                {2155, uint256S("41b4196ea0d0b0c3651e3129d5757f0336f7f016f75a5e14e37988d5f1e35173")},
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 41b4196ea0d0b0c3651e3129d5757f0336f7f016f75a5e14e37988d5f1e35173 (height 2155)
            1537710402,
            2215,
            0.0005422
        };
        
        vFoundersRewardAddress = {
            //"2N6nSQHMMF3NQnFvxoogeDjpmENQjF9nog9", /* main-index: 0*/
            //"2N1CchGDNvDtPjKwyvm34L3gPhMzLNip4eA", /* main-index: 1*/
            //"2NDSp2itA9Xv9BZ9yFnFqDDRyCtKog7Ug1y", /* main-index: 2*/
            //"2Mv7i5QAKiaMNcCDTC2BGKsdB7h1XYRorAv", /* main-index: 3*/
            //"2N7na2VR3W8AdUcyYub7budhpAgQegj4Ebs", /* main-index: 4*/
            //"2Mt2cQk7siP82Vwymve4uyv2mNwdaKGCXsv", /* main-index: 5*/
            //"2NAu9pYUgFPZFCXqbSKDGiiqjG5X99RkiMh", /* main-index: 6*/
            //"2N4qQ8zhcCQzJuPnfUeiqx6ExnMFk5G9Aq3", /* main-index: 7*/
            //"2NFHSiw1Hrhihn5zX9cGPfr3bRJAqTN5DNo", /* main-index: 8*/
            //"2N9kiEtFxEkxec1DjUkG2tjzaUEATJ57ygm", /* main-index: 9*/
            //"2N3PkBx66qK6qi8L9PvPss9rWUiYJWtaELp", /* main-index: 10*/
        };

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMasternodeColleteralPaymentAmount = 7500;
        consensus.nMasternodePayeeReward = 30;
        consensus.nInstantSendConfirmationsRequired = 2;
        consensus.nInstantSendKeepLock = 6;
        consensus.nTreasuryAddressChange = 350;
        consensus.nTreasuryAddressChangeStart = 500;
        consensus.nTreasuryAmount = 10;
        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on regtest
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.HardforkHeight = 100000000; // activate hardfork here by the given timestamp.
        consensus.HardforkTime = 1537048800;
        consensus.HardforkHash = uint256(); // there is no hardfork hash for regtest, it will be just activated with the timestamp.
        consensus.powLimit_SHA256 = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_SCRYPT = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X11 = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_NEOSCRYPT = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_EQUIHASH = uint256S("0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f");
        consensus.powLimit_YESCRYPT = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_HMQ1725 = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_XEVAN = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_NIST5 = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_TIMETRAVEL10 = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_PAWELHASH = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X13 = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X14 = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X15 = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X17 = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_LYRA2RE = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_BLAKE2S = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_BLAKE2B = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_ASTRALHASH = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_PADIHASH = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_JEONGHASH = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_ZHASH = uint256S("0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f");
        consensus.powLimit_KECCAK = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_GLOBALHASH = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_QUBIT = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_SKEIN = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_GROESTL = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_SKUNKHASH = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_QUARK = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit_X16R = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 10 * 60; // ten minutes
        consensus.nPowTargetSpacing = 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");
        
        consensus.nAuxpowChainId = 0x00b4; 
        consensus.fStrictChainId = false;

        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x69;
        pchMessageStart[3] = 0xd6;
        nDefaultPort = 27702;
        nPruneAfterHeight = 1000;
        const size_t N = 48, K = 5;
        const size_t ZN = 96, ZK = 5;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(ZN, ZK));
        nEquihashN = N;
        nEquihashK = K;
        nZhashN = ZN;
        nZhashK = ZK;

        genesis = CreateGenesisBlock(1558105579, 2, 0x207fffff, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x1ba3490ecf1653fbe7a53d1e0fb7e051c2a1c506d84f4dd3b01522544cd1fc6f"));
        assert(genesis.hashMerkleRoot == uint256S("0xe217ce769444458c180ca6a5944cbbc22828f377cfd0e1790158034299827ffc"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fAllowMultiplePorts = true;
        
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        
        strSporkAddress = "mqakdpV7YNSnfobctsdSt6GmDzmQTEMois";

        checkpointData = {
            {
                {0, uint256S("1ba3490ecf1653fbe7a53d1e0fb7e051c2a1c506d84f4dd3b01522544cd1fc6f")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };
        
        vFoundersRewardAddress = {
            "2N17UdNZBM2U4FXNjecYVV1mPUwQWtg1XzH", /* main-index: 0*/
            "2MwtUKWUjmVsLWtaj51fbJEtrd2DNbYqDK2", /* main-index: 1*/
            "2N8nwjXu9AdmbCwGQJu9aKhmiXWykTEhRkS", /* main-index: 2*/
            "2Mv5eVh9SsnMfsy1N5QYduPCGDRNp6Kj39S", /* main-index: 3*/
            "2N3RfcjrKAsDsGwFFN5JsfgPxodQk1HxLzn", /* main-index: 4*/
            "2NGJCAL9hFtWj6acfU6C91jFaLxBsWyHaaP", /* main-index: 5*/
            "2N7FsHXu67uPbttMAgwSgAcpYsrFFAyCGYB", /* main-index: 6*/
            "2MwQVBDcKm7CjdZ67S8dEEQiwbeeQLuT4rF", /* main-index: 7*/
            "2Msn8SaEduyQevmWWTTrZRKVZGJibbLdzvw", /* main-index: 8*/
            "2N8kP8VkASJuhUDHxpdN95VqPCyEnFCi3N4", /* main-index: 9*/
            "2MtAsa9V4ertX7DGfjgvdNwr8GNXqUw7rZz", /* main-index: 10*/
            "2N6hnmzHtBzRu2RYFsLYmcuNceFXmq4jBfV", /* main-index: 11*/
            "2MvzC4tWxYUgT6Fc2iWzmGeRs3U3LVEkaw3", /* main-index: 12*/
            "2NEDz28G1HEEwK1vdEHiy2oYSokuFZvvRr2", /* main-index: 13*/
            "2MsVB2LFLQPA7tXZLZXNvPJX5yhtZtueMs1", /* main-index: 14*/
            "2MwFsPHTQQ1xFDxMar4b4YNn7bWo7VHL4RU", /* main-index: 15*/
            "2MxMEUUgk8EQN3Lxofb5V4sDUdFAgq9rfaQ", /* main-index: 16*/
            "2NCJGRv3geiQAQwvXpHiSHUi6hjUvhSvq7e", /* main-index: 17*/
            "2MvqZnzar7WsHLZnUDbVum2YJVy61fttQoS", /* main-index: 18*/
            "2NF4cakN8q11foekqPhhfoHVaexCuqpf1qx", /* main-index: 19*/
            "2NCU5MZmr1tJBK3pPAwKuefukas5KdyDPfH", /* main-index: 20*/
            "2NAjMvhCRLkyzJTUmTKJr1BLyTe24yKw6af", /* main-index: 21*/
            "2N4pqGNhQyny4tvWzMV9NxrLyWq4XGF7dri", /* main-index: 22*/
            "2N9Heh7Y8goSKDLkJU7Wxp3MnJZbT7Njcyx", /* main-index: 23*/
            "2NC85tMoGP4aiturXZq17wemK1WrVNESDUy", /* main-index: 24*/
            "2MxHFHaG6CbdnHtsERXaYZW1gSFrpPnE3BD", /* main-index: 25*/
            "2MyVx85jgwYAQxfnVxHXF2Km4Ci3BoLvrvn", /* main-index: 26*/
            "2N1y5MZVcyXTc1yF9wcvQAe8jRiYTUHwnTY", /* main-index: 27*/
            "2N39MVuvLwHqpjjYzN4dAZSucoSArYSBzCz", /* main-index: 28*/
            "2MvUnTMcdgtBsqvvEFBBtRqZW51Bu1AVkMf", /* main-index: 29*/
            "2MtJLiYsBWgRqdu7EzDzKbUKaR7HkbUopYC", /* main-index: 30*/
            "2MzwnoxWYmTFLP4tfZPWxy6jfCV2mwigjG6", /* main-index: 31*/
            "2Mu6Km35fTzX16XMj4XjGGXfNgdLBZHdMVt", /* main-index: 32*/
            "2MxRJu8qJw3YCDr6m1Eb6v7k4SazjSiWRm2", /* main-index: 33*/
            "2NG2YBMkapGWLf8S3cgF2T2DAQErVjaCa2F", /* main-index: 34*/
            "2NEqCUpURCeFjvWqTiruWifco2vq6T99eHy", /* main-index: 35*/
            "2N5SjT4ssUVipJBnexjy5brcJXCbbU19xyZ", /* main-index: 36*/
            "2N2zwsEj9Y3K2G8ESL1JmgwoyHPq7HS8Aya", /* main-index: 37*/
            "2MvQ73eibyiJtWWTbcZ1chwFZLw3wWC2y38", /* main-index: 38*/
            "2N7zud9cBS7RLNLonrfvgRrSbyA7Mpcj4Av", /* main-index: 39*/
            "2MzisRthqhMivhb8JrjgdCXAm8LjGNxgpmM", /* main-index: 40*/
            "2N8M417a48dZQUXckopWfx1ABirajsKUHA5", /* main-index: 41*/
            "2NGJi8qrVfmVhKofENj1DLmfW4VrEM8tydz", /* main-index: 42*/
            "2MyxLP15DzNt5ofCBS7KVNBE8t5ZNNZ7on5", /* main-index: 43*/
            "2MsFjrA3fhVdjmGnRARKa852ZLVfkAts49G", /* main-index: 44*/
            "2MvgG8ta4dQNvZNjWghq3g2Qz25ACYoXGXT", /* main-index: 45*/
            "2MwD3BJRaWLQXLASKijdG76s37BeaT9Dos1", /* main-index: 46*/
            "2MsvKX5UcFoGLusryTkgeFe74qzA2nJUbag", /* main-index: 47*/
            "2MskMaN6CaDgqNGQLzHd2Jc9tFaEckqLNKg", /* main-index: 48*/
            "2N34AfY2b5iAX8e1Dj6FRWFxanHteU61yD9", /* main-index: 49*/
            "2MuvtJVs3DLEjsquAkfZt6nETbuaUqh8U7B", /* main-index: 50*/
            "2NDTRVJCjdGuQWJzxMty9MERnyHc3zZ7yEH", /* main-index: 51*/
            "2N2urPffKZix5g1kKBqkubshQHrQQrtVNjR", /* main-index: 52*/
            "2MzwN1n4DEVN1j1QFDVsfHBqNKCKVgpH38y", /* main-index: 53*/
            "2MzayuRCNqUKH2SEgM1XQPP4PdDjEbGv77z", /* main-index: 54*/
            "2N6UgEsqQN7ncSw2sSJ6yMGC6WZLRcuG4Sp", /* main-index: 55*/
            "2ND8AJw4ihAcUQzxjiDBMmb7JFJF3t8jnVn", /* main-index: 56*/
            "2NCQaffpEniR5zxkZNk1dwDb5MDP1dEU6VQ", /* main-index: 57*/
            "2NEmZo5PtTRtDzMj82goB8XVJcfZ3y4csrV", /* main-index: 58*/
            "2N7AuNJuvmgGQEo8Lbrhx1TQoypK4YieCBq", /* main-index: 59*/
            "2NAAs8FiJ2ZdKY7az6vdcWpCADRCN7vMX1v", /* main-index: 60*/
            "2N5FrQJwqWJ95yRhuuwK9wx7PkC9F9NsjnA", /* main-index: 61*/
            "2N9Wkci3xfcg9e83nGVfrbeNkGfJ3ody83V", /* main-index: 62*/
            "2NBkA7Eo8kPRi8RmNWHBPfaTTkRdFJFbhvq", /* main-index: 63*/
            "2NDzuCENr8cSoUG1v4ZRJKxfo9cYfFnN78X", /* main-index: 64*/
            "2N25xuGmQ4NJBxudqnQ1Z9PCXkWhPNnXZVZ", /* main-index: 65*/
            "2NF9UBsMsCUvmMaPTpn24YtNmi26vx3ydcZ", /* main-index: 66*/
            "2MxzuED1zYgAiFHcWkG4JVHVy8YcDxa1Mk6", /* main-index: 67*/
            "2MwPVtH6WPhzHVg8fUDXWSCgUp1HG3sniW1", /* main-index: 68*/
            "2N873Sk7Cfv2g8wYZdPAWFmv8MeSA5CAvd8", /* main-index: 69*/
            "2N7fezW9sBGJwrdBfdutZc5cWTxTwGaBqMx", /* main-index: 70*/
            "2N98bmMiV38t4iCHUqrGkePE2xFzuC4nQGF", /* main-index: 71*/
            "2N3aWFwXpwEsDVV6fSbatqrCmt8veisKPdq", /* main-index: 72*/
            "2MvqujCxXwgxGV3tdnRUuPAdAaQNM6nLcpS", /* main-index: 73*/
            "2MuPHLSdLCgo4MbjtPUoZ1ZryzFSfgw4e4N", /* main-index: 74*/
            "2Mz4a1KPbz7cDuwLbLogdkiCJxHtC1F3HUS", /* main-index: 75*/
            "2NBPzn4y2koGNE6kfxnLsbmyqor3ZbKKaig", /* main-index: 76*/
            "2NENzoxQhZ6oD2UHu8vrxFbivDXzCLULCZg", /* main-index: 77*/
            "2MxV8CpUv8QeaHReE1NcfsaJuBshAT6b46C", /* main-index: 78*/
            "2MtEQSnuA917X9Fww3381PbKyPxYr2ga3Ws", /* main-index: 79*/
            "2NGZXVc5jhS1buJPgJx8GqN2vpeceu5G75C", /* main-index: 80*/
            "2NAtEAtkVykwGyh44NNxSdKfN1TT3PkF3Vu", /* main-index: 81*/
            "2Msykr4wyRoi2SNE3MBWrubP9RP2GGNL22w", /* main-index: 82*/
            "2N6ooCwEKzUc2qmLiPyt646sZRZXB8Aq8MH", /* main-index: 83*/
            "2NA6yFACsgDRvDqGfF92p2TCGsTYRS693Se", /* main-index: 84*/
            "2NCrpVrXcP4ADWkE6pHGN9kdHq69QS3hfje", /* main-index: 85*/
            "2MtevGQ48XnX3KcV2WDf9KCK8hb24Nv9Yk9", /* main-index: 86*/
            "2NFhsXYCEuJzZP7QeVqTmV4Prj9x5TpRWHM", /* main-index: 87*/
            "2N4P1novB5uDNoDx3jw4McURP6B7bPssdCx", /* main-index: 88*/
            "2N8c21LoqQCM1vawYtCL8MJw6xZynfJcprU", /* main-index: 89*/
            "2N68fZBqddJPDLEzpGYhtk8zEahKXw1y9Vy", /* main-index: 90*/
            "2N3S9fRgSCTbtrRpPn55pKw3HxEM2jcJGvh", /* main-index: 91*/
            "2NFeu9hRw37dsKDTKvX7kXgx8uVPS7vYW5z", /* main-index: 92*/
            "2N2NG5mn4Ec4Za4eL3nwGtM6mvuxmngJ3ax", /* main-index: 93*/
            "2MtYXDC39QJs9cc8uMupwPguugHtKPwchr1", /* main-index: 94*/
            "2N7NUWz7k5YBq6NTnLZz4BBdi1gUVHePT6b", /* main-index: 95*/
            "2MyJBaXMPFTCY5zdXJoyscuy1kv2T9WS4Z7", /* main-index: 96*/
            "2MsdBsSuCe1FiMmQQ2SHXCzGhJwmcHRqzdb", /* main-index: 97*/
            "2NBGauWNzKmnT6T1WW6UCf6bUSAP3ENn72B", /* main-index: 98*/
            "2MxwQztxFVFfrxR7eNdJHomZN4LJuv3o6pJ", /* main-index: 99*/
            "2MxegXJJbp3jDqiSGki1jNuxUY3r21CWAiW", /* main-index: 100*/
            "2NBKQt8qrLJ8G2cHwY3rJY6CSY2fosXP2D6", /* main-index: 101*/
            "2N6GNYR9ppTrmNZitfE2i3vX9B8qwMoaype", /* main-index: 102*/
            "2MwJbzPCutqp4LDXEr3wVFiyJaMNFVhke9P", /* main-index: 103*/
            "2MvEuLWWzu6gyjomm6TwE6kRyydnSz5JQYM", /* main-index: 104*/
            "2N9HBtrmap9f4k93aYg5C8KF6oaYiD4v2j7", /* main-index: 105*/
            "2NBaHWZh59gMs6Tw9nFAZCVLD4cQVvzHEey", /* main-index: 106*/
            "2N2QjTu9k9nV6pCywy62Vd61P2upoHmjqcY", /* main-index: 107*/
            "2NE6fNsmaqbAD4XTSa7zQdRsDAttThjeVDj", /* main-index: 108*/
            "2N4N7gWmWBmT5U4GqAc6eRqPYKUjX3UP7eT", /* main-index: 109*/
            "2MtnCGmDFytgM5TchmFxhDKu7ErtohXEjcP", /* main-index: 110*/
            "2NAPLquNpBFbTFUbk8Y5En14FPWXhjRgafz", /* main-index: 111*/
            "2N8DbCRm8juJResyRjmyd1oH42oGKsAYVxt", /* main-index: 112*/
            "2N3A5cRw65gkYXjgvNAofWsmN5Jy9QWCmWB", /* main-index: 113*/
            "2MzuT97EeYD5HgFWLmmNayNSaEEVHBC6BYi", /* main-index: 114*/
            "2N5HwgatefXaowGCNuQAPgkDA9RWivzgkw9", /* main-index: 115*/
            "2N2b3rHBivaGDXV2rQpXXoexBs5DFBEWwYh", /* main-index: 116*/
            "2N76RSYNAgJ7ByWBmaojyy32Pzt89qSSRrj", /* main-index: 117*/
            "2NA69XUrFmJMGjfmNuk4ZPU9SSvFv22Z2gJ", /* main-index: 118*/
            "2NBJgphahNZUC8byd8N8jiLYjvY4hEAPTFo", /* main-index: 119*/
            "2N62aZkjhDgqw5nXgH23L2EtcpMSY4poZP3", /* main-index: 120*/
            "2Mzts3Rjsm9GojPo1JrkSfQmXfJ8ZjSKz2p", /* main-index: 121*/
            "2NFFc5RCVZah2oBMUw62or1HvkCJAvcgdeE", /* main-index: 122*/
            "2N56EZD718NHXxLFA3qKLgLvyoqTwAFDHCV", /* main-index: 123*/
            "2MwDb7EPW2kCPy1zh6h8Jcq2FVPHEQNFKoP", /* main-index: 124*/
            "2NCsZE27c3Jq25pjbnUWCJcVwZ4mBW4eQkh", /* main-index: 125*/
            "2N4YuzB3qqaLJFjGRaiGrCtwG3cNcSzZFgt", /* main-index: 126*/
            "2NC1KWiaUrwfFHCYJttkfuuUn49eSuZTUcX", /* main-index: 127*/
            "2NDFzoV3pCgz9b83BMM6UwdcuzqkgM6ZCbh", /* main-index: 128*/
            "2NEGnqWDCXceEwNZqFLj1pZUYPpwMJioGZp", /* main-index: 129*/
            "2N7DuRB5E3Mgse9ymBRF6HtvYhFfJaMFFCL", /* main-index: 130*/
            "2N7gU2HVAJf2xm7WHZpZLZ8KzyVBrGTQfMf", /* main-index: 131*/
            "2N5dKRDjfrRH9xUqwqPcD1iDAjwLBCnXo3d", /* main-index: 132*/
            "2NCxBGq3Tms9azkNLPLdKtmciuU1C8pXG8e", /* main-index: 133*/
            "2MsH5Fo92hj9XofFXSNPEuNoEwqLNKn8Da4", /* main-index: 134*/
            "2Mv2EHyfsE4zjB2KFYRcQtE942kcfxDXGcN", /* main-index: 135*/
            "2NADwQoFUDhWmzF65wLkEf5kZiDWKTzAH61", /* main-index: 136*/
            "2N4F1uyESwLKNs9mJ8RiVrDoGZBse7pdqPr", /* main-index: 137*/
            "2N9AXUa5KvWdNywVDrCSmG142duEkmnPKii", /* main-index: 138*/
            "2MyVwbm7rUjFur6dBev6cWcwcNjBLNP4Yqb", /* main-index: 139*/
            "2N4PKAnSievyBW4Gsysbu7YH5AqjpV44xgw", /* main-index: 140*/
            "2N1FfmSuk4vTbM7Pbf8fNv87N1qYdE5SNnW", /* main-index: 141*/
            "2MsZtedPuJNADreK3wpm41zrmQNzwbX68KU", /* main-index: 142*/
            "2N8TKbkHn8YmJGymo1ZHChLMGnVkSaVF5kD", /* main-index: 143*/
            "2N2onhjJBAW8jxuUwPVcgdYxsKhs3s5teQP", /* main-index: 144*/
            "2N8Gj25tg9ceV2qGhkZQCTtE54Q5qPYb4SF", /* main-index: 145*/
            "2N6nc7QGHqZzeukKbHcMnwhYm2HYdrKZ8tk", /* main-index: 146*/
            "2NBJL1kBsb9whxZPBKkGAbkfkLm1cEevwsL", /* main-index: 147*/
            "2N6mVVzGqSE9CTJud12Pw38eWNBpY2fvb2Q", /* main-index: 148*/
            "2NEFJu85Fc5REAzHU6ASuUj4YcHaqxD3KSE", /* main-index: 149*/
            "2NA94Ld3xnBRmDtS5tcEEZBrSXm9trJbEAK", /* main-index: 150*/
            "2NEpHiupJJGtXf6XCSw7KRDCD9SaCcuTj67", /* main-index: 151*/
            "2N7xXBy4NV5do5DGEGAJuTPfAENzHZy6YBr", /* main-index: 152*/
            "2N3rEH1U2UyfvhYbVw5uvyxWtmQ5vHfp8p3", /* main-index: 153*/
            "2MwG2PoMv9cTHHd3QdhWVNK5z2MfTJNFHjR", /* main-index: 154*/
            "2N9EqMr9CpD4fanNopZxuvPtTCH6mkExaYU", /* main-index: 155*/
            "2MzkDeU5r7BwfMTDcHYCRTd7XSrVEpAkjhV", /* main-index: 156*/
            "2MyWvk2Tux7CjLiMN94EF6iPYwKccG5eRfB", /* main-index: 157*/
            "2NG3BjtwBD8zi9dsNKj8z6U2grQB2u62uWW", /* main-index: 158*/
            "2MsyBuJWiWBL27WPbhbPJAXLTxSXYodSSn5", /* main-index: 159*/
            "2N1tTvHPA91q1cUe4aDeawf6SzeXK27a4Kh", /* main-index: 160*/
            "2N53aR9KYQrEbe6Dc986YDYBmdD2WKKBPRj", /* main-index: 161*/
            "2MzNLHFgg3SCUqpPZfT6sJxJj2zUR1j4g3B", /* main-index: 162*/
            "2NFxDiZi7x4L6QQyN8DB3ppcaJGHM8PJTet", /* main-index: 163*/
            "2NDjD5ahEvThhAy2K2efAuznCe1br6dHMQm", /* main-index: 164*/
            "2MzcGuFhzkJTjGNGidaFS78a7uQdsgr2Rot", /* main-index: 165*/
            "2N8XuXHTUjfoWwyKQ3pdgtKvB3vf6wkWw6a", /* main-index: 166*/
            "2N4AaeG9ZExsE5cumci1w2MB8zGsLyMjTy2", /* main-index: 167*/
            "2MuK7B9nHP5mbhhHgYY3i7Mv6JXH4hj67jY", /* main-index: 168*/
            "2Mt8Ee7bxDzXP4vHZjnftjWxpfCmDMk1ghB", /* main-index: 169*/
            "2N1N1bDnCSPLKzZNSUTCuQ6aEg9ZW1kKW3c", /* main-index: 170*/
            "2Muiw7eBKjWWG6WWNQuw9vc7c4ZpRf4djWK", /* main-index: 171*/
            "2MydEMCZaZe6vnqDJaNVyemo3AjcnD5hdf7", /* main-index: 172*/
            "2NDgayCxUv5TJZZrdS9R9s3V51ftLEQSsWL", /* main-index: 173*/
            "2N6VAHjN3x3jTzGaS6xLrqgunk5hE9pbmCF", /* main-index: 174*/
            "2ND5FtCcDWxG6KPfq7gS2FzPQnZHV9nEriL", /* main-index: 175*/
            "2N91kZ1B5XYVmE5AaUAbvgYdmgcqECHtezU", /* main-index: 176*/
            "2Mz9evqmNfYij3NTjB5bJAF79wCQ5659fhW", /* main-index: 177*/
            "2NCRUTeJjrxMjaaj9VxyAV8XW8z2o5pmquK", /* main-index: 178*/
            "2N3bSv4784obsidgFd6moZVwuuAFQ88hY3x", /* main-index: 179*/
            "2N6Y9WHNEtY5FPUSt8ooHhvEQ8KfQpZoDoK", /* main-index: 180*/
            "2MzfTDYJuuW1XD8Fu7gffrMnH1K2AdnCPht", /* main-index: 181*/
            "2N3Dmn6osxGVymQwjHriidXsZ5NgJJdBT4c", /* main-index: 182*/
            "2N5nm9n9dy6cc5JSqsWpNJmH8ZrPrVj2EJU", /* main-index: 183*/
            "2N3ivAJiv29AY7GVGsi9fmr7ZmdfEmbbaA4", /* main-index: 184*/
            "2NCfS1D8Y49GJX2HRx9Bv8Zj93zXp5XfH2Y", /* main-index: 185*/
            "2N7wnHBpqh4bUPsQyrcCyF2DnnsyEPhD13j", /* main-index: 186*/
            "2N5dXu4eeeQeTJQPRckHyNVzcVmDFwHyoR1", /* main-index: 187*/
            "2Mx8D3hiEphH1LAWCwYEX1yEAGkT95s2HQx", /* main-index: 188*/
            "2NBBtqg93gciWgh5dpgkc2DzDm7aa4gkUhZ", /* main-index: 189*/
            "2NF2obRuvHXcxyNC6L4voqdyqBRd9pFv8av", /* main-index: 190*/
            "2NBw7bjJ1Xh6A74U1x9HYDEuu1TG56E3FAp", /* main-index: 191*/
            "2N4eJ7bgQQYAMAnMkCizAqGnJgA6E4W8ToG", /* main-index: 192*/
            "2NCRY2WFiajUN162rjGyRaUWzZVYygBG5Rg", /* main-index: 193*/
            "2Mxm9jGSqZHjSFWmxbsfDjBMan9NqmpNTZc", /* main-index: 194*/
            "2MuxQnE1pEYUg9oVY1NEWy3wa7y8iDvw8sF", /* main-index: 195*/
            "2MzKwLr5wCcm2GBihdd3UPF3VWiPHPMNBxz", /* main-index: 196*/
            "2N4hPCKFMkJhXGtmpGVWufM1riSiDc7rDvn", /* main-index: 197*/
            "2MsHbF8H7AS8XgV4uzPjLTZkoj7v4HrUoHz", /* main-index: 198*/
            "2MuJPx2K5hgdim5CGeeRCdGKUCvqTHn9a76", /* main-index: 199*/
            "2NFnJfiKSUpLWN3vQgRpESFcFG6832PD1EF", /* main-index: 200*/
            "2N6oL2W1cPWwb8AEWjEa3yRyxfvCGFeoycD", /* main-index: 201*/
            "2MsQHTyERxcV4Ab8G1ybKL5tgh3pv9KVGoc", /* main-index: 202*/
            "2Mumug6wdBpgoHuzAPLfz4S4igJGK3bMgp2", /* main-index: 203*/
            "2N2G3TWcmw57NdbbhvZXPeghBVGs3dDKDEm", /* main-index: 204*/
            "2N9iYNtj1siEhoWNz1U18GeRw6JUPtmqTwj", /* main-index: 205*/
            "2NGD3x4krZPsFAAXxrePjwBhtt2NVK794c2", /* main-index: 206*/
            "2N5iFw2Cu7wjRRDFjNf4P9bD1dz1czw2NYd", /* main-index: 207*/
            "2N1D3RYEZbRyn1C7sXzpxVBFBHC2fYfaBgJ", /* main-index: 208*/
            "2NFHu6fmdhcFPVny8TqZrZKUrz6ok2px1Bo", /* main-index: 209*/
            "2MvukvexBwPwm2PjrXP7XeRCYNwaYfSq4L3", /* main-index: 210*/
            "2Mz6HdbznobW3zkzqMg8gDUXoyjZPmCqzem", /* main-index: 211*/
            "2N8BzoeCE8yuDNL7kEZciddEBo2TLQQuoR2", /* main-index: 212*/
            "2NE26srmRnRyq2VszabGmtPQRRMXqtDXsNB", /* main-index: 213*/
            "2N5p2L9SvewMQdNuWsnbTWzD189vm974VGv", /* main-index: 214*/
            "2N3QmFKMvoAKDJQfzDQcGykZWNxXekRW8gy", /* main-index: 215*/
            "2Mw7iDXbcWdgf5vzF9LE5E2Br2Wz2HX2sXG", /* main-index: 216*/
            "2NBHBTRsDeBbjJTEbyAj1qjjW5SWrQLhbPQ", /* main-index: 217*/
            "2Myiqm2MoDiePxp8pZzFaJEnyhHnvRbGPWp", /* main-index: 218*/
            "2MtcFk32U3beUjJzpDubQG2fe4LbMWv8wuk", /* main-index: 219*/
            "2MtNEzNvEVb3bXjcqwayKKJSCxhQro3zS1i", /* main-index: 220*/
            "2N7b4VQgzNHUWbvW1JUC57LtdZdicX4r9qT", /* main-index: 221*/
            "2N5vkmoF9tnUezwtq25yEyXkRHY24v5Yatd", /* main-index: 222*/
            "2NBmaVaEeW5vHM8XBuBds5BZJ5swJhvYgSJ", /* main-index: 223*/
            "2Mvq3WwYHEqjnrR7JFqtuuSJWNqBX6zhL5P", /* main-index: 224*/
            "2N8vHqa3f9WXFcKHFerwVzhEUBrAqovTQr9", /* main-index: 225*/
            "2NFDUaZ3MTpLgnV9ftCtTUrYgBzMRbyYhTL", /* main-index: 226*/
            "2NGEaQuFPEsh2mqEdeWxUTug4P5g949uXFp", /* main-index: 227*/
            "2NF1UyTd2ggXTj2yEqaFEp3ZqCtefoKUcg9", /* main-index: 228*/
            "2NAVZU3r3KymLneGCT2YqsVN4yDvtSPmiLm", /* main-index: 229*/
            "2MzAvVDH6YxsrvdimQgurDWoZiAK76zgHfM", /* main-index: 230*/
            "2MsimGjoLeASLpbNpt5LQKRBGZ6SVVg3pan", /* main-index: 231*/
            "2N4zwfsDDzUwYqqeRni82UFCkRNNyucNRXC", /* main-index: 232*/
            "2MsSKjGmbsN6MRcNhm4DAvKTZ2C4VLz8aQt", /* main-index: 233*/
            "2MzNLzeAVcd4j7bsbH22xptkqJYEerTFehW", /* main-index: 234*/
            "2NAjoLjCeQfppEJ1BshVBuNoCMrTc6YStaY", /* main-index: 235*/
            "2NFjbuGWELHQBWFxEaSGL8reptJ7ykgpCgv", /* main-index: 236*/
            "2N1VkEeUF2yEcgxwo4NkgQ5T9CEtjzaAofG", /* main-index: 237*/
            "2MwrwcFTLTK22otrJ749zVcbcMaexekvdQR", /* main-index: 238*/
            "2MzAteF7RK9WDDb4NcjMQYsAKEJUEs6VrnB", /* main-index: 239*/
            "2N1ZjJaohf2WKSvkxzr1NbbHbXjCiA6MePm", /* main-index: 240*/
            "2MypJMrbrcNfQNFjdqrAe6yLaBQpPHNM5Ub", /* main-index: 241*/
            "2N9Xiij6PXunJ73MnN5WNfFr2xZVERT25Lp", /* main-index: 242*/
            "2MwWdVshqsGLwyuKtN7idW2RwHy2JfKzwu3", /* main-index: 243*/
            "2NBPTwoEuAyzbFuxLHuDDa1TD1Nmr46Xvvp", /* main-index: 244*/
            "2MwH8AidxjpbjiWsh1PnFcBZAUDV42G8x44", /* main-index: 245*/
            "2MxpVpdcL7S4W5mjqqnq2eZvVKhvT43jebN", /* main-index: 246*/
            "2Mvi4xMAUP1wHHhu7AXi5jj3qcJi9mZZMui", /* main-index: 247*/
            "2N6hRHM3cAhGd9bPwoSjSPrMo63PtNKTMg9", /* main-index: 248*/
            "2N3caMMyNTmQbw12syN19RNovHaDZruNVCN", /* main-index: 249*/
            "2Mtc3Pw4tYh7yxEEXHHirGHS8ed92kHdW2M", /* main-index: 250*/
            "2MwodghEt1XykbDNmUQCxe8DM2WTPLr4R22", /* main-index: 251*/
            "2N5MR3oAD2p8meLbudV7Zb8kKpQCst2KLBv", /* main-index: 252*/
            "2MvPdEx1Ey3XNRbbeumLCLPqxmdYT3bwJeL", /* main-index: 253*/
            "2MsiFG83vcFL6MUw93JamraS2vpSAirRJRi", /* main-index: 254*/
            "2NBTpWNJ5oxMt4EyMqiXxovcxNCBUWsFnUv", /* main-index: 255*/
            "2NBh4t5qC1RuGeHPqziZwZan9f7yKLZ3ZVw", /* main-index: 256*/
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "gtrt";
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

const CChainParams CreateNetworkParams(const std::string& network) {
    if (network == CBaseChainParams::MAIN)
        return CMainParams();
    else if (network == CBaseChainParams::TESTNET)
        return CTestNetParams();
    else if (network == CBaseChainParams::REGTEST)
        return CRegTestParams();
    throw std::runtime_error(strprintf("%s: Unknown network %s.", __func__, network));
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

// Index variable i ranges from 0 - (vFoundersRewardAddress.size()-1)
std::string CChainParams::GetFoundersRewardAddressAtHeight(int nHeight) const {
    int addressChangeInterval = consensus.nTreasuryAddressChange;
    int addressChangeStartHeight = consensus.nTreasuryAddressChangeStart;
    int i = (nHeight - addressChangeStartHeight) / addressChangeInterval;
    
    if(i <= 0)
        i = 0;
    
    if(i >= 256)
        i = 256;
    
    return GetFoundersRewardAddressAtIndex(i);
}

// The founders reward address is expected to be a multisig (P2SH) address
CScript CChainParams::GetFoundersRewardScriptAtHeight(int nHeight) const {
    CTxDestination address = DecodeDestination(GetFoundersRewardAddressAtHeight(nHeight).c_str());
    assert(IsValidDestination(address));
    assert(boost::get<CScriptID>(&address) != nullptr);
    CScriptID scriptID = boost::get<CScriptID>(address); // address is a boost variant
    CScript script = CScript() << OP_HASH160 << ToByteVector(scriptID) << OP_EQUAL;
    return script;
}

std::string CChainParams::GetFoundersRewardAddressAtIndex(int i) const {
    assert(i >= 0 && i < vFoundersRewardAddress.size());
    return vFoundersRewardAddress[i];
}

CAmount CChainParams::GetTreasuryAmount(CAmount coinAmount) const
{
    return ((coinAmount / 100.0) * consensus.nTreasuryAmount);
}

unsigned int CChainParams::EquihashSolutionWidth(uint8_t nAlgo) const
{
    assert(nAlgo == ALGO_EQUIHASH || nAlgo == ALGO_ZHASH);
    
    if(nAlgo == ALGO_EQUIHASH)
        return EhSolutionWidth(EquihashN(), EquihashK());
    else if(nAlgo == ALGO_ZHASH)
        return EhSolutionWidth(ZhashN(), ZhashK());
    else
        return 0;
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
