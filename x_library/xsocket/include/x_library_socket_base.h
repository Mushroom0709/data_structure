#ifndef _X_LIBRARY_SOCKET_BASE_H_
#define _X_LIBRARY_SOCKET_BASE_H_

#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include "x_library_common.hpp"


namespace xM
{
    namespace x_socket
    {
#define XS_MAX_CREATE 256
#define XS_MAX_BUFFER 4096
#define XS_TIME_WAIT 100
        class EventBase
        {
        public:
            virtual void Connected(int _fd) {};
            virtual void DisConnect(int _fd) {};
            virtual void Receive(int _fd, uint8_t* _data, size_t _size) {};
            virtual void Started() {};
            virtual void Stopped() {};
        };

        class TcpCoreBase
        {
        public:
            int listen_;
            EventBase* event_;
            bool run_flag_;
        public:
            virtual bool make() = 0;
            virtual void work() = 0;
            virtual void destroy() = 0;
        public:
            TcpCoreBase();
            virtual ~TcpCoreBase() = 0;
        };

        class TcpServerBase
        {
#define MAX_LISTEN 128
        public:
            virtual bool Start(EventBase* _ev, int _port, const char* _ip) = 0;
            virtual void Stop() = 0;
            virtual int Send(int _fd, uint8_t* _data, size_t _size) = 0;
        public:
            TcpServerBase();
            virtual ~TcpServerBase() = 0;
        };
    }
}

#endif // !_X_LIBRARY_SOCKET_BASE_H_