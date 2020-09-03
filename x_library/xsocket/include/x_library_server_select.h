#ifndef _X_LIBRARY_SERVER_SELECT_H_
#define _X_LIBRARY_SERVER_SELECT_H_

#include "x_library_socket_base.h"

#include <sys/select.h>

namespace xM
{
    namespace x_socket
    {
		class TcpSelectCore:
			public IServerCore
		{
        private:
            int recv_len_;
            uint8_t recv_buf_[X_SOCKET_MAX_BUF_SIZE];
        private:
            bool process_error(int _fd, int _res = -1);
            bool process_receive(int _fd);
            bool process_accept();
        public:
            // ��ʼ����ر���
            bool Init(PtrIServerEvent _event, int _max_conn = FD_SETSIZE);

            // �������socket
            bool SetConnect(int _fd, bool _is_listener = false);

            // ִ���߼�
            void Work();

            // �����Ĵ���
            void Destroy();
        public:
            TcpSelectCore();
            ~TcpSelectCore();
		};
    }
}

#endif // !_X_LIBRARY_SERVER_SELECT_H_