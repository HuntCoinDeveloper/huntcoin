// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2019 The Huntcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/test/uritests.h>

#include <qt/guiutil.h>
#include <qt/walletmodel.h>

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?req-dontexist="));
    QVERIFY(!GUIUtil::parseHuntcoinURI(uri, &rv));

    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?dontexist="));
    QVERIFY(GUIUtil::parseHuntcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseHuntcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?amount=0.001"));
    QVERIFY(GUIUtil::parseHuntcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?amount=1.001"));
    QVERIFY(GUIUtil::parseHuntcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?amount=100&label=Wikipedia Example&IS=1"));
    QVERIFY(GUIUtil::parseHuntcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));
    QVERIFY(rv.fUseInstantSend == 1);
    
    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?amount=100&label=Wikipedia Example&IS=Something Invalid"));
    QVERIFY(GUIUtil::parseHuntcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));
    QVERIFY(rv.fUseInstantSend != 1);
    
    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?IS=1"));
    QVERIFY(GUIUtil::parseHuntcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend == 1);
    
    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?IS=0"));
    QVERIFY(GUIUtil::parseHuntcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend != 1);

    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe"));
    QVERIFY(GUIUtil::parseHuntcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend != 1);

    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseHuntcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseHuntcoinURI("huntcoin://GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?message=Wikipedia Example Address", &rv));
    QVERIFY(rv.address == QString("GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?req-message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseHuntcoinURI(uri, &rv));

    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseHuntcoinURI(uri, &rv));

    uri.setUrl(QString("huntcoin:GbMJLn3fyMoZChhTLsUrmWmEQnoKsJAPpe?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseHuntcoinURI(uri, &rv));
}
