// Copyright (c) 2016-2017 The Funcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HUNTCOIN_WALLET_RPCWALLET_H
#define HUNTCOIN_WALLET_RPCWALLET_H

#include <string>

class CRPCTable;
class CWallet;
class JSONRPCRequest;
class UniValue;

void RegisterWalletRPCCommands(CRPCTable &t);

/**
 * Figures out what wallet, if any, to use for a JSONRPCRequest.
 *
 * @param[in] request JSONRPCRequest that wishes to access a wallet
 * @return nullptr if no wallet should be used, or a pointer to the CWallet
 */
CWallet *GetWalletForJSONRPCRequest(const JSONRPCRequest& request);

std::string HelpRequiringPassphrase(CWallet *);
void EnsureWalletIsUnlocked(CWallet *);
bool EnsureWalletIsAvailable(CWallet *, bool avoidException);

UniValue getaddressinfo(const JSONRPCRequest& request);
UniValue signrawtransactionwithwallet(const JSONRPCRequest& request);
#endif //HUNTCOIN_WALLET_RPCWALLET_H
