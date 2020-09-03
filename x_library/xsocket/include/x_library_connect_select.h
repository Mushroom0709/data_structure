#ifndef _X_LIBRARY_CONNECT_SELECT_H_
#define _X_LIBRARY_CONNECT_SELECT_H_

#include "x_library_socket_base.h"
#include <sys/select.h>

namespace xM
{
    namespace x_socket
    {
        class ConnectSelectCore :
            public IConnectCore
        {
        private:
            int recv_len_;
            uint8_t recv_buf_[X_SOCKET_MAX_BUF_SIZE];
        private:
            bool process_error(int _fd, int _res);
            bool process_receive(int _fd);
        public:
            bool Init(PtrIConnectEvent _event, int _conn_fd);
            void Work();
            void Destroy();
        public:
            ConnectSelectCore();
            ~ConnectSelectCore();
        };
    }
}

#endif //_X_LIBRARY_CONNECT_SELECT_H_