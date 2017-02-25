
// #include <cstdlib>
#include <iostream>
// #include <memory>
// #include <utility>
// #include <ctime>
#include <syslog.h>
// #include <unistd.h>

#include <boost/asio.hpp>
// #include <boost/enable_shared_from_this.hpp>
#include <boost/asio/io_service.hpp>
// #include <boost/asio/ip/udp.hpp>
#include <boost/asio/signal_set.hpp>
// #include <boost/array.hpp>
#include <boost/bind.hpp>

#include <IPC>
#include "rdcmd.h"

int main( /*int argc, char* argv[]*/ ) {
    try {
//         if ( argc != 2 ) {
//             std::cerr << "Usage: async_tcp_echo_server <port>\n";
//             return 1;
//         }

        boost::asio::io_service io_service;

        Raidix::rdcmd app(io_service);

        if (app.daemonize())
            io_service.run();
    }
    catch( std::exception& e ) {
        syslog( LOG_ERR | LOG_USER, "Exception: %s", e.what() );
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
