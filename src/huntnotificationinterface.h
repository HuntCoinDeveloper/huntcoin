// Copyright (c) 2015 The Funcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HUNTCOIN_HUNTNOTIFICATIONINTERFACE_H
#define HUNTCOIN_HUNTNOTIFICATIONINTERFACE_H

#include <validationinterface.h>

class CHUNTNotificationInterface : public CValidationInterface
{
public:
    CHUNTNotificationInterface(CConnman& connmanIn): connman(connmanIn) {}
    virtual ~CHUNTNotificationInterface() = default;

    // a small helper to initialize current block height in sub-modules on startup
    void InitializeCurrentBlockTip();

protected:
    // CValidationInterface
    void AcceptedBlockHeader(const CBlockIndex *pindexNew) override;
    void NotifyHeaderTip(const CBlockIndex *pindexNew, bool fInitialDownload) override;
    void UpdatedBlockTip(const CBlockIndex *pindexNew, const CBlockIndex *pindexFork, bool fInitialDownload) override;
    void TransactionAddedToMempool(const CTransactionRef& tx) override;
    void BlockConnected(const std::shared_ptr<const CBlock>& pblock, const CBlockIndex *pindex, const std::vector<CTransactionRef>& vtxConflicted) override;
    void BlockDisconnected(const std::shared_ptr<const CBlock>& pblock) override;

private:
    CConnman& connman;
};

#endif // HUNTCOIN_HUNTNOTIFICATIONINTERFACE_H
