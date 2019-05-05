// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HUNTCOIN_QT_HUNTCOINADDRESSVALIDATOR_H
#define HUNTCOIN_QT_HUNTCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class HuntcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit HuntcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Huntcoin address widget validator, checks for a valid huntcoin address.
 */
class HuntcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit HuntcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // HUNTCOIN_QT_HUNTCOINADDRESSVALIDATOR_H
