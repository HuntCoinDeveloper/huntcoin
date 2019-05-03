// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2018 The Globaltoken Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <masternode-helper.h>

#include <activemasternode.h>
#include <init.h>
#include <instantx.h>
#include <masternode-payments.h>
#include <masternode-sync.h>
#include <masternodeman.h>
#include <netfulfilledman.h>

void ThreadCheckMasternodes(CConnman& connman)
{
    if(fLiteMode) return; // disable all Globaltoken specific functionality

    static bool fOneThread;
    if(fOneThread) return;
    fOneThread = true;

    // Make this thread recognisable as the MasternodeCheck thread
    RenameThread("huntcoin-mncheck");

    unsigned int nTick = 0;

    while (true)
    {
        MilliSleep(1000);

        // try to sync from all available nodes, one step at a time
        masternodeSync.ProcessTick(connman);

        if(masternodeSync.IsBlockchainSynced() && !ShutdownRequested()) {

            nTick++;

            // make sure to check all masternodes first
            mnodeman.Check();

            mnodeman.ProcessPendingMnbRequests(connman);
            mnodeman.ProcessPendingMnvRequests(connman);

            // check if we should activate or ping every few minutes,
            // slightly postpone first run to give net thread a chance to connect to some peers
            if(nTick % MASTERNODE_MIN_MNP_SECONDS == 15)
                activeMasternode.ManageState(connman);

            if(nTick % 60 == 0) {
                netfulfilledman.CheckAndRemove();
                mnodeman.ProcessMasternodeConnections(connman);
                mnodeman.CheckAndRemove(connman);
                mnodeman.WarnMasternodeDaemonUpdates();
                mnpayments.CheckAndRemove();
                instantsend.CheckAndRemove();
            }
            if(fMasternodeMode && (nTick % (60 * 5) == 0)) {
                mnodeman.DoFullVerificationStep(connman);
            }
        }
    }
}