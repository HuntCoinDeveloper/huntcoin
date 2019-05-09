Huntcoin Core
=============

Setup
---------------------
Huntcoin Core is the original Huntcoin client and it builds the backbone of the network. It downloads and, by default, stores the entire history of Huntcoin transactions (which is currently more than 100 GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download Huntcoin Core, visit [huntcoin.africa](https://huntcoin.africa/#downloads).

Running
---------------------
The following are some helpful notes on how to run Huntcoin on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/huntcoin-qt` (GUI) or
- `bin/huntcoind` (headless)

### Windows

Unpack the files into a directory, and then run huntcoin-qt.exe.

### OS X

Drag Huntcoin-Core to your applications folder, and then run Huntcoin-Core.

### Need Help?

* See the documentation at the [Huntcoin Wiki](https://en.huntcoin.it/wiki/Main_Page)
for help and more information.
* Ask for help on [#huntcoin](http://webchat.freenode.net?channels=huntcoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=huntcoin).
* Ask for help on the [HuntcoinTalk](https://huntcointalk.org/) forums, in the [Technical Support board](https://huntcointalk.org/index.php?board=4.0).

Building
---------------------
The following are developer notes on how to build Huntcoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Huntcoin repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/huntcoin/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Travis CI](travis-ci.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [HuntcoinTalk](https://huntcointalk.org/) forums, in the [Development & Technical Discussion board](https://huntcointalk.org/index.php?board=6.0).
* Discuss project-specific development on #huntcoin-core-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=huntcoin-core-dev).
* Discuss general Huntcoin development on #huntcoin-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=huntcoin-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
