#ifndef IPC_H
#define IPC_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>
#include <boost/signals2.hpp>

using boost::asio::ip::tcp;

class IPC_Session : public boost::enable_shared_from_this<IPC_Session> {
    public:
        IPC_Session( tcp::socket socket )
        : socket_( std::move( socket ) ) {}

        void start() { do_read(); }

    private:
        void do_read();
        void do_write( std::size_t /*length*/ );

        tcp::socket socket_;
        enum { max_length = 1024 };
        boost::array<char, max_length> data_;
};

class IPC_Server {
    public:
        IPC_Server( boost::asio::io_service& io_service, boost::asio::ip::address_v4 addr, short port )
        : acceptor_( io_service, tcp::endpoint( addr, port ) ), socket_( io_service ) {
            do_accept();
        }

        boost::signals2::signal<void()> on_accept;

    private:
        void do_accept() {
            acceptor_.async_accept( socket_,
                [this]( boost::system::error_code ec ) {
                    if ( !ec ) {
                        std::make_shared<IPC_Session>( std::move( socket_ ) )->start();
                    }

                    do_accept();
                } );
        }

        tcp::acceptor acceptor_;
        tcp::socket socket_;
};

#endif // IPC_H
