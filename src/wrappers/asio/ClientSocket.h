#include <boost/asio.hpp>

#include <string>
#include <deque>
#include <memory>

class ClientSocket
{
    public:
        ClientSocket ( ClientSocket&& ) = default;

        ClientSocket& operator= ( ClientSocket&& ) = default;
        ClientSocket& operator= ( const ClientSocket& ) = delete;

        static ClientSocket create ( std::string address, std::string service );
        std::string read_line ();
        void send ( std::string message );

        virtual ~ClientSocket () = default;

    private:
        ClientSocket ( std::string address, std::string service );

        std::unique_ptr < boost::asio::io_service > io_service;
        boost::asio::ip::tcp::socket socket;

        std::deque < std::string > next_lines;
        std::string line_rest;
};
