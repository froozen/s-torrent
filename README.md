s-torrent
=========

![Normaly, this would be a screenshot](https://i.imgur.com/OnbWecS.png)

A simple torrent-daemon in C++ using libtorrent-rasterbar with a ncurses-frontend.

This client is in a state that I would consider usable. That being said, I wouldn't realy recommend using it
( I don't ) because of it still lacking a ton of features like dht, proxies and peer exchange.

There still might be some usefull snippets of code in here, so feel free to look around.

### Usage
**NOTE:**This client will only work on linux because of the socket headers I used.

After compiling the program, first start the server, then the client.
```
./cmake.sh setup
./s-torrent-server&
./s-torrent
```
**NOTE:** If you want to run the server on a server, you will have to change the "server_address" value in config.json

### This project uses:
* [libtorrent-rasterbar](http://www.rasterbar.com/products/libtorrent/) for everything torrent related
* [ncurses](https://www.gnu.org/software/ncurses/) for the interface
* [jsoncpp](https://github.com/open-source-parsers/jsoncpp) for JSON-parsing, which is used for network-communication
* The event system code from [2D-engine](https://github.com/firecoders/2D-engine), which is used in the daemon
* The files from [here](http://www.adp-gmbh.ch/cpp/common/base64.html), for base64 en- and decoding

### Licensing:
* s-torrent is licensed under the MIT License ( LICENSE )
* libtorrent-rasterbar is licensed under the BSD License ( licenses/BSD_LICENSE )
* ncurses is licensed under the X11 License ( licenses/X11_LICENSE )
* jsoncpp is licensed under the MIT License ( licenses/MIT_LICENSE )
* 2D-engine is licensed under the MIT License ( licenses/MIT_LICENSE or at the top of every file )
* The licenses to base64.h and base64.cpp can be found at the top of the files
