// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2019 The Huntcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <huntnotificationinterface.h>
#include <instantx.h>
#include <masternodeman.h>
#include <masternode-payments.h>
#include <masternode-sync.h>

void CHUNTNotificationInterface::InitializeCurrentBlockTip()
{
    LOCK(cs_main);
    UpdatedBlockTip(chainActive.Tip(), nullptr, IsInitialBlockDownload());
}

void CHUNTNotificationInterface::AcceptedBlockHeader(const CBlockIndex *pindexNew)
{
    masternodeSync.AcceptedBlockHeader(pindexNew);
}

void CHUNTNotificationInterface::NotifyHeaderTip(const CBlockIndex *pindexNew, bool fInitialDownload)
{
    masternodeSync.NotifyHeaderTip(pindexNew, fInitialDownload, connman);
}

void CHUNTNotificationInterface::UpdatedBlockTip(const CBlockIndex *pindexNew, const CBlockIndex *pindexFork, bool fInitialDownload)
{
    if (pindexNew == pindexFork) // blocks were disconnected without any new ones
        return;

    masternodeSync.UpdatedBlockTip(pindexNew, fInitialDownload, connman);

    if (fInitialDownload)
        return;

    if (fLiteMode)
        return;

    mnodeman.UpdatedBlockTip(pindexNew);
    instantsend.UpdatedBlockTip(pindexNew);
    mnpayments.UpdatedBlockTip(pindexNew, connman);
}

void CHUNTNotificationInterface::TransactionAddedToMempool(const CTransactionRef& ptx)
{
    instantsend.SyncTransaction(ptx);
}

void CHUNTNotificationInterface::BlockConnected(const std::shared_ptr<const CBlock>& pblock, const CBlockIndex *pindex, const std::vector<CTransactionRef>& vtxConflicted)
{
    for (const CTransactionRef& ptx : vtxConflicted) {
        instantsend.SyncTransaction(ptx);
    }
    for (size_t i = 0; i < pblock->vtx.size(); i++) {
        instantsend.SyncTransaction(pblock->vtx[i], pindex, i);
    }
}

void CHUNTNotificationInterface::BlockDisconnected(const std::shared_ptr<const CBlock>& pblock) {
    for (const CTransactionRef& ptx : pblock->vtx) {
        instantsend.SyncTransaction(ptx);
    }
}