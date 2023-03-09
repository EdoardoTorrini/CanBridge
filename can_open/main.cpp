#include <lely/ev/loop.hpp>

#include <lely/coapp/slave.hpp>

#include <lely/io2/linux/can.hpp>
#include <lely/io2/posix/poll.hpp>
#include <lely/io2/sys/io.hpp>
#include <lely/io2/sys/timer.hpp>
#include <lely/io2/sys/sigset.hpp>

using namespace lely;

int main()
{
    // Create an I/O context to synchronize I/O services during shutdown.
    io::Context context;

    // Create an platform-specific I/O polling instance to monitor the CAN bus, as
    // well as timers and signals.
    io::Poll poll(context);

    // Create a polling event loop and pass it the platform-independent polling
    // interface. If no tasks are pending, the event loop will poll for I/O
    // events.
    ev::Loop loop(poll.get_poll());

    // I/O devices only need access to the executor interface of the event loop.
    auto exec = loop.get_executor();

    io::Timer timer(poll, exec, CLOCK_MONOTONIC);

    // Create a virtual SocketCAN CAN controller and channel, and do not modify
    // the current CAN bus state or bitrate.
    io::CanController ctrl("vcan0");
    io::CanChannel chan(poll, exec);
    chan.open(ctrl);

    canopen::BasicSlave slave(timer, chan, "cpp-slave.eds", "", 1);

    slave.Reset();

    // Run the event loop until no tasks remain (or the I/O context is shut down).
    loop.run();

    return 0;
}