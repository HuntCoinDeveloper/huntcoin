// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2019 The Huntcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MASTERNODE_HELPER_H
#define MASTERNODE_HELPER_H

class CConnman;

void ThreadCheckMasternodes(CConnman& connman);

#endif // MASTERNODE_HELPER_H