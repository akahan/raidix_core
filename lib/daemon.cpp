#include <syslog.h>

#include "daemon.h"

using namespace Raidix;

Daemon::Daemon( io_service& io_service ) :
io_service_( io_service ) {
}

bool Daemon::daemonize() {
    // Inform the io_service that we are about to become a daemon. The
    // io_service cleans up any internal resources, such as threads, that may
    // interfere with forking.
    io_service_.notify_fork( io_service::fork_prepare );

    // Fork the process and have the parent exit. If the process was started
    // from a shell, this returns control to the user. Forking a new process is
    // also a prerequisite for the subsequent call to setsid().
    if ( pid_t pid = fork() ) {
        if ( pid > 0 ) {
            // We're in the parent process and need to exit.
            //
            // When the exit() function is used, the program terminates without
            // invoking local variables' destructors. Only global variables are
            // destroyed. As the io_service object is a local variable, this means
            // we do not have to call:
            //
            //   io_service.notify_fork(boost::asio::io_service::fork_parent);
            //
            // However, this line should be added before each call to exit() if
            // using a global io_service object. An additional call:
            //
            //   io_service.notify_fork(boost::asio::io_service::fork_prepare);
            //
            // should also precede the second fork().
            exit( 0 );
        }
        else {
            syslog( LOG_ERR | LOG_USER, "First fork failed: %m" );
            return false;
        }
    }

    // Make the process a new session leader. This detaches it from the
    // terminal.
    setsid();

    // A process inherits its working directory from its parent. This could be
    // on a mounted filesystem, which means that the running daemon would
    // prevent this filesystem from being unmounted. Changing to the root
    // directory avoids this problem.
    chdir( "/" );

    // The file mode creation mask is also inherited from the parent process.
    // We don't want to restrict the permissions on files created by the
    // daemon, so the mask is cleared.
    umask( 0 );

    // A second fork ensures the process cannot acquire a controlling terminal.
    if ( pid_t pid = fork() ) {
        if ( pid > 0 ) {
            exit( 0 );
        }
        else {
            syslog( LOG_ERR | LOG_USER, "Second fork failed: %m" );
            return false;
        }
    }

    // Close the standard streams. This decouples the daemon from the terminal
    // that started it.
    close( 0 );
    close( 1 );
    close( 2 );

    // We don't want the daemon to have any standard input.
    if ( open( "/dev/null", O_RDONLY ) < 0 ) {
        syslog( LOG_ERR | LOG_USER, "Unable to open /dev/null: %m" );
        return false;
    }

    // Send standard output to a log file.
    const char* output = "/tmp/asio.daemon.out";
    const int flags    = O_WRONLY | O_CREAT | O_APPEND;
    const mode_t mode  = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    if ( open( output, flags, mode ) < 0 ) {
        syslog( LOG_ERR | LOG_USER, "Unable to open output file %s: %m", output );
        return false;
    }

    // Also send standard error to the same log file.
    if ( dup( 1 ) < 0 ) {
        syslog( LOG_ERR | LOG_USER, "Unable to dup output descriptor: %m" );
        return false;
    }

    // Inform the io_service that we have finished becoming a daemon. The
    // io_service uses this opportunity to create any internal file descriptors
    // that need to be private to the new process.
    io_service_.notify_fork( io_service::fork_child );

    // The io_service can now be used normally.
    syslog( LOG_INFO | LOG_USER, "Daemon started" );

    return true;
}

void Daemon::fork_call(Raidix::callback& fn, Raidix::callback& cb) {
    // Inform the io_service that we are about to fork. The io_service cleans
    // up any internal resources, such as threads, that may interfere with
    // forking.
    io_service_.notify_fork( boost::asio::io_service::fork_prepare );

    if ( fork() == 0 ) {
        // Inform the io_service that the fork is finished and that this is the
        // child process. The io_service uses this opportunity to create any
        // internal file descriptors that must be private to the new process.
        io_service_.notify_fork( boost::asio::io_service::fork_child );

        // The child won't be accepting new connections, so we can close the
        // acceptor. It remains open in the parent.
//         acceptor_.close();

        // The child process is not interested in processing the SIGCHLD signal.
//         signal_.cancel();

//         start_read();
//         auto result = fn();
//         cb(result);

//         auto f = boost::bind(fn, _3, _2, "woah", _2);
//
//         DoWork<decltype(Raidix::callback)> work_on_it(f);

    }
    else {
        // Inform the io_service that the fork is finished (or failed) and that
        // this is the parent process. The io_service uses this opportunity to
        // recreate any internal resources that were cleaned up during
        // preparation for the fork.
        io_service_.notify_fork( boost::asio::io_service::fork_parent );

//         socket_.close();
    }
}
