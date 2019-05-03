#!/bin/bash

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

HUNTCOIND=${HUNTCOIND:-$BINDIR/huntcoind}
HUNTCOINCLI=${HUNTCOINCLI:-$BINDIR/huntcoin-cli}
HUNTCOINTX=${HUNTCOINTX:-$BINDIR/huntcoin-tx}
HUNTCOINQT=${HUNTCOINQT:-$BINDIR/qt/huntcoin-qt}

[ ! -x $HUNTCOIND ] && echo "$HUNTCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BTCVER=($($HUNTCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for huntcoind if --version-string is not set,
# but has different outcomes for huntcoin-qt and huntcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$HUNTCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $HUNTCOIND $HUNTCOINCLI $HUNTCOINTX $HUNTCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
