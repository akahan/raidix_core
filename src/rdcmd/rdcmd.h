#ifndef RDCMD_H
#define RDCMD_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <syslog.h>

#include <IPC>
#include <Daemon>

#define RDCMD_HOST "127.0.0.1"
#define RDCMD_PORT "43333"

namespace Raidix {

using namespace boost::asio;
using ip::tcp;

class rdcmd : public Daemon {
    const ip::address_v4 addr = ip::address_v4::from_string(RDCMD_HOST);
    const unsigned int port = std::atoi(RDCMD_PORT);

    public:
        rdcmd( io_service& io_service );

    private:
        void sigint_handler();
        void sighup_handler();

        io_service& io_service_;
        IPC_Server ipc_;
        signal_set hup_signals_;
        signal_set stop_signals_;
};

};

#endif // RDCMD_H
