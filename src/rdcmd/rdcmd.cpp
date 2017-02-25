#include "rdcmd.h"

#include <iostream>
#include <boost/log/trivial.hpp>

using namespace Raidix;

rdcmd::rdcmd( io_service& io_service )
: Daemon( io_service ), io_service_( io_service ), ipc_( io_service, addr, port ), hup_signals_( io_service_, SIGHUP ), stop_signals_( io_service_, SIGINT, SIGTERM ) {
    hup_signals_.async_wait( boost::bind( &rdcmd::sighup_handler, this ) );
    stop_signals_.async_wait( boost::bind( &rdcmd::sigint_handler, this ) );
}

void rdcmd::sigint_handler() {
    syslog( LOG_ERR | LOG_USER, "SIGINT" );
    syslog( LOG_INFO | LOG_USER, "Daemon stopped" );

    io_service_.stop();
}

void rdcmd::sighup_handler() {
    syslog( LOG_ERR | LOG_USER, "SIGHUP" );

    BOOST_LOG_TRIVIAL(trace) << "The quick brown fox jumps over the lazy dog";

    hup_signals_.async_wait( boost::bind( &rdcmd::sighup_handler, this ) );
}
