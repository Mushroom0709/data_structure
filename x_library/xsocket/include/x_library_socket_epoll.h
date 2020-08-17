#ifndef _X_LIBRARY_SOCKET_EPOLL_H_
#define _X_LIBRARY_SOCKET_EPOLL_H_

#include "x_library_socket_base.h"

#include <sys/epoll.h>

namespace xM
{
    namespace x_socket
    {
        class TcpEpollCore :
            public IServerCore
        {
        private:
            int ep_fd_;
        private:
            int recv_len_;
            uint8_t recv_buf_[X_SOCKET_MAX_BUF_SIZE];
        private:
            bool process_error(int _fd, int _res = -1);
            bool process_receive(int _fd);
            bool process_accept();
        public:
            // ��ʼ����ر���
            bool Init(PtrIEventBase _event, int _max_conn = X_SOCKET_MAX_CONNECT);

            // �������socket
            bool SetConnect(int _fd, bool _is_listener = false);

            // ִ���߼�
            void Work();
            // �����Ĵ���
            void Distroy();
        public:
            TcpEpollCore();
            ~TcpEpollCore();
        };
    }
}

#endif // !_X_LIBRARY_SOCKET_EPOLL_H_