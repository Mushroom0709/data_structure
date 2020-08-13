#ifndef _X_LIBRARY_SOCKET_EPOLL_H_
#define _X_LIBRARY_SOCKET_EPOLL_H_

#include "x_library_socket_base.h"

#include <sys/epoll.h>

namespace xM
{
    namespace x_socket
    {
        class TcpEpollCore :
            public TcpCoreBase
        {
        private:
            int ep_fd_;
            struct epoll_event ep_events_[XS_MAX_CREATE];
            int fd_cache_[XS_MAX_CREATE];

            int recv_len_;
            uint8_t recv_buf_[XS_MAX_BUFFER];
        private:
            bool process_socket_error(int _fd);
            bool process_accept();
            bool process_receive(int _fd);
        public:
            bool make();
            void work();
            void destroy();
        public:
            TcpEpollCore();
            ~TcpEpollCore();
        };
    }
}

#endif // !_X_LIBRARY_SOCKET_EPOLL_H_