s-torrent
=========

A simple torrent-client in C++ using libtorrent-rasterbar

This project is just getting started, so please don't expect a fully feature-complete
torrent client just yet.

###This project uses:
* [boost.asio](http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio.html) for networking
* [libtorrent-rasterbar](http://www.rasterbar.com/products/libtorrent/) for everything torrent related
* [ncurses](https://www.gnu.org/software/ncurses/) for the interface
* [jsoncpp](https://github.com/open-source-parsers/jsoncpp) for JSON-parsing, which is used for network-communication
* The event system code from [2D-engine](https://github.com/firecoders/2D-engine), which is used in the daemon

###Licensing:
* s-torrent is licensed under the MIT License ( LICENSE )
* boost.asio is licensed under the Boost Software License ( licenses/BOOST_LICENSE )
* libtorrent-rasterbar is licensed under the BSD License ( licenses/BSD_LICENSE )
* ncurses is licensed under the X11 License ( licenses/X11_LICENSE )
* jsoncpp is licensed under the MIT License ( licenses/MIT_LICENSE )
* 2D-engine is licensed under the MIT License ( licenses/MIT_LICENSE or at the top of every file )
