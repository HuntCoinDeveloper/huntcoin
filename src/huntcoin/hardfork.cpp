// Copyright (c) 2018 The Huntcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <huntcoin/hardfork.h>

#include <arith_uint256.h>
#include <chainparams.h>
#include <primitives/block.h>
#include <uint256.h>

#include <sstream>
#include <string>

arith_uint256 GetAlgoPowLimit(uint8_t algo, const Consensus::Params& consensusParams)
{
	if (algo == ALGO_SHA256D)
		return UintToArith256(consensusParams.powLimit_SHA256);
	else if (algo == ALGO_SCRYPT)
		return UintToArith256(consensusParams.powLimit_SCRYPT);
	else if (algo == ALGO_X11)
		return UintToArith256(consensusParams.powLimit_X11);
	else if (algo == ALGO_NEOSCRYPT)
		return UintToArith256(consensusParams.powLimit_NEOSCRYPT);
	else if (algo == ALGO_EQUIHASH)
		return UintToArith256(consensusParams.powLimit_EQUIHASH);
	else if (algo == ALGO_YESCRYPT)
		return UintToArith256(consensusParams.powLimit_YESCRYPT);
	else if (algo == ALGO_HMQ1725)
		return UintToArith256(consensusParams.powLimit_HMQ1725);
	else if (algo == ALGO_XEVAN)
		return UintToArith256(consensusParams.powLimit_XEVAN);
	else if (algo == ALGO_NIST5)
		return UintToArith256(consensusParams.powLimit_NIST5);
    else if (algo == ALGO_TIMETRAVEL10)
		return UintToArith256(consensusParams.powLimit_TIMETRAVEL10);
    else if (algo == ALGO_PAWELHASH)
		return UintToArith256(consensusParams.powLimit_PAWELHASH);
    else if (algo == ALGO_X13)
		return UintToArith256(consensusParams.powLimit_X13);
    else if (algo == ALGO_X14)
		return UintToArith256(consensusParams.powLimit_X14);
    else if (algo == ALGO_X15)
		return UintToArith256(consensusParams.powLimit_X15);
    else if (algo == ALGO_X17)
		return UintToArith256(consensusParams.powLimit_X17);
    else if (algo == ALGO_LYRA2RE)
        return UintToArith256(consensusParams.powLimit_LYRA2RE);
    else if (algo == ALGO_BLAKE2S)
        return UintToArith256(consensusParams.powLimit_BLAKE2S);
    else if (algo == ALGO_BLAKE2B)
        return UintToArith256(consensusParams.powLimit_BLAKE2B);
    else if (algo == ALGO_ASTRALHASH)
        return UintToArith256(consensusParams.powLimit_ASTRALHASH);
    else if (algo == ALGO_PADIHASH)
        return UintToArith256(consensusParams.powLimit_PADIHASH);
    else if (algo == ALGO_JEONGHASH)
        return UintToArith256(consensusParams.powLimit_JEONGHASH);
    else if (algo == ALGO_ZHASH)
        return UintToArith256(consensusParams.powLimit_ZHASH);
    else if (algo == ALGO_KECCAK)
        return UintToArith256(consensusParams.powLimit_KECCAK);
    else if (algo == ALGO_GLOBALHASH)
        return UintToArith256(consensusParams.powLimit_GLOBALHASH);
    else if (algo == ALGO_QUBIT)
        return UintToArith256(consensusParams.powLimit_QUBIT);
    else if (algo == ALGO_SKEIN)
        return UintToArith256(consensusParams.powLimit_SKEIN);
    else if (algo == ALGO_GROESTL)
        return UintToArith256(consensusParams.powLimit_GROESTL);
    else if (algo == ALGO_SKUNKHASH)
        return UintToArith256(consensusParams.powLimit_SKUNKHASH);
    else if (algo == ALGO_QUARK)
        return UintToArith256(consensusParams.powLimit_QUARK);
    else if (algo == ALGO_X16R)
        return UintToArith256(consensusParams.powLimit_X16R);
	else
		return UintToArith256(consensusParams.powLimit_SHA256);
}

arith_uint256 GetAlgoPowLimit(uint8_t algo)
{
	const Consensus::Params& consensusParams = Params().GetConsensus();
	return GetAlgoPowLimit(algo, consensusParams);
}

bool IsHardForkActivated(uint32_t blocktime, const Consensus::Params& consensusParams)
{
	if(blocktime >= consensusParams.HardforkTime)
	{
		return true;
	}
	return false;
}

bool IsHardForkActivated(uint32_t blocktime)
{
	const Consensus::Params& consensusParams = Params().GetConsensus();
	return IsHardForkActivated(blocktime, consensusParams);
}

std::string GetCoinbaseFeeString(int type)
{
    std::stringstream strStream;
    const CChainParams &MainnetParams = CreateNetworkParams(CBaseChainParams::MAIN);
    const CChainParams &TestnetParams = CreateNetworkParams(CBaseChainParams::TESTNET);
    const CChainParams &RegtestParams = CreateNetworkParams(CBaseChainParams::REGTEST);
    if(type == DIVIDEDPAYMENTS_BLOCK_WARNING)
    {
        strStream << "Warning (Divided Coinbase): You tried to mine a block, but did not agreed to pay the coinbase fees..\nIt is required to pay the following fees from the Coinbase:\n\n"
        << "Network: " << MainnetParams.NetworkIDString() << "    | Founders-Reward: " << MainnetParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << MainnetParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - MainnetParams.GetConsensus().nMasternodePayeeReward - MainnetParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "Network: " << TestnetParams.NetworkIDString() << "    | Founders-Reward: " << TestnetParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << TestnetParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - TestnetParams.GetConsensus().nMasternodePayeeReward - TestnetParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "Network: " << RegtestParams.NetworkIDString() << " | Founders-Reward: " << RegtestParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << RegtestParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - RegtestParams.GetConsensus().nMasternodePayeeReward - RegtestParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "\nThe fees will be deducted automatically from your mined block, if you mine directly in your wallet.\n"
        << "\nTo agree, you must start the wallet with the -acceptdividedcoinbase argument or add acceptdividedcoinbase=1 to your huntcoin.conf file.\n";
        return strStream.str();
    }
    else if(type == DIVIDEDPAYMENTS_GENERATE_WARNING)
    {
        strStream << "You are not able to mine new coins right now.\n"
        << "\nSince the hardfork is active, you must pay Founders-Reward and Masternode-Reward\n"
        << "\nCurrently, you did not agreed to pay it, but it is needed to mine new Coins.\n"
        << "\nThe payment amount is displayed underneath, for each network:\n\n"
        << "Network: " << MainnetParams.NetworkIDString() << "    | Founders-Reward: " << MainnetParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << MainnetParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - MainnetParams.GetConsensus().nMasternodePayeeReward - MainnetParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "Network: " << TestnetParams.NetworkIDString() << "    | Founders-Reward: " << TestnetParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << TestnetParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - TestnetParams.GetConsensus().nMasternodePayeeReward - TestnetParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "Network: " << RegtestParams.NetworkIDString() << " | Founders-Reward: " << RegtestParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << RegtestParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - RegtestParams.GetConsensus().nMasternodePayeeReward - RegtestParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "\nDetails:\n\n"
        << "Your found blocks will automatically pay the fees, there are no additional steps for you.\n"
        << "\nAgreement:\n"
        << "You can agree to pay the fees by the following way:\n"
        << "\n- Always start the wallet with the -acceptdividedcoinbase argument\n"
        << "- Add acceptdividedcoinbase=1 to your huntcoin.conf file and restart the wallet.\n"
        << "\nIf you don't agree to pay the fees, you will not be able to mine HuntCoins and your blocks will be rejected.\n";
        return strStream.str();
    }
    else if(type == DIVIDEDPAYMENTS_BLOCKTEMPLATE_WARNING)
    {
        strStream << "You are not able to mine new coins right now.\n"
        << "\nSince the hardfork is active, you must pay Founders-Reward and Masternode-Reward\n"
        << "\nCurrently, you did not agreed to pay it, but it is needed to mine new Coins.\n"
        << "\nThe payment amount is displayed underneath, for each network:\n\n"
        << "Network: " << MainnetParams.NetworkIDString() << "    | Founders-Reward: " << MainnetParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << MainnetParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - MainnetParams.GetConsensus().nMasternodePayeeReward - MainnetParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "Network: " << TestnetParams.NetworkIDString() << "    | Founders-Reward: " << TestnetParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << TestnetParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - TestnetParams.GetConsensus().nMasternodePayeeReward - TestnetParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "Network: " << RegtestParams.NetworkIDString() << " | Founders-Reward: " << RegtestParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << RegtestParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - RegtestParams.GetConsensus().nMasternodePayeeReward - RegtestParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "\nDetails:\n\n"
        << "You need to pay the founders reward, by adding the treasury details to your coinbase transaction.\n"
        << "In the RPC Result of getblocktemplate you will find a JSON-Object called 'treasury'.\n"
        << "You must add the 'address' or 'scriptPubKey' and 'amount' as a receiver of your coinbase transaction.\n"
        << "If you want, you can use the 'hex' value and add it to your coinbase, it is a ready raw transaction output of the founders reward.\n"
        << "Same thing for masternode rewards. Get the 'payee' or 'script' and 'amount' from the 'masternode' JSON-Object, and include them into your coinbase.\n"
        << "Additionally it is important to dedecude the amounts from the raw coinbase reward. (coinbasevalue - treasuryamount - masternodeamount = your block reward)\n"
        << "The amount and addresses will change every block, so always take the current output from getblocktemplate!\n"
        << "\nAgreement:\n\n"
        << "You can agree to pay the fees by the following way:\n"
        << "\n- Always start the wallet with the -acceptdividedcoinbase argument\n"
        << "- Add acceptdividedcoinbase=1 to your huntcoin.conf file and restart the wallet.\n"
        << "\nIf you don't agree to pay the treasury, you will not be able to mine HuntCoins and your blocks will be rejected.\n";
        return strStream.str();
    }
    else if(type == DIVIDEDPAYMENTS_AUXPOW_WARNING)
    {
        strStream << "You are not able to mine new coins right now.\n"
        << "\nSince the hardfork is active, you must pay Founders-Reward and Masternode-Reward\n"
        << "\nCurrently, you did not agreed to pay it, but it is needed to mine new Coins.\n"
        << "\nThe payment amount is displayed underneath, for each network:\n\n"
        << "Network: " << MainnetParams.NetworkIDString() << "    | Founders-Reward: " << MainnetParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << MainnetParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - MainnetParams.GetConsensus().nMasternodePayeeReward - MainnetParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "Network: " << TestnetParams.NetworkIDString() << "    | Founders-Reward: " << TestnetParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << TestnetParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - TestnetParams.GetConsensus().nMasternodePayeeReward - TestnetParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "Network: " << RegtestParams.NetworkIDString() << " | Founders-Reward: " << RegtestParams.GetConsensus().nTreasuryAmount << "% of blockreward. | Masternode-Reward: " << RegtestParams.GetConsensus().nMasternodePayeeReward << "% of blockreward. | Your mining Reward: " << (100 - RegtestParams.GetConsensus().nMasternodePayeeReward - RegtestParams.GetConsensus().nTreasuryAmount) << "% of blockreward.\n"
        << "\nDetails:\n\n"
        << "Your found auxpow blocks will automatically pay the fees, there are no additional steps for you.\n"
        << "\nAgreement:\n"
        << "You can agree to pay the fees by the following way:\n"
        << "\n- Always start the wallet with the -acceptdividedcoinbase argument\n"
        << "- Add acceptdividedcoinbase=1 to your huntcoin.conf file and restart the wallet.\n"
        << "\nIf you don't agree to pay fees, you will not be able to mine HuntCoins and your blocks will be rejected.\n";
        return strStream.str();
    }
    else
    {
        // Should not occur
        strStream << "";
    }
    return strStream.str();
}