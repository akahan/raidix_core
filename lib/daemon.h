#ifndef DAEMON_H
#define DAEMON_H

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace Raidix {

using namespace boost::asio;

template <class T> struct DoWork { /* ... */ };

typedef boost::function<void()> callback;

class Daemon {
    public:
        Daemon( io_service& io_service );

        bool daemonize();

        void fork_call(Raidix::callback& fn, Raidix::callback& cb);

    private:
        io_service& io_service_;
};

}

#endif // DAEMON_H
