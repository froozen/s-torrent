#include <boost/asio.hpp>

#include <string>
#include <deque>
#include <memory>

class Client_socket
{
    public:
        Client_socket ( std::string address, std::string service );
        Client_socket ( Client_socket&& ) = default;

        Client_socket& operator= ( Client_socket&& ) = default;
        Client_socket& operator= ( const Client_socket& ) = delete;

        std::string read_line ();
        void send ( std::string message );

        virtual ~Client_socket () = default;

    private:
        std::unique_ptr < boost::asio::io_service > io_service;
        boost::asio::ip::tcp::socket socket;

        std::deque < std::string > next_lines;
        std::string line_rest;
};
