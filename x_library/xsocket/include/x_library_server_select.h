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
            // 初始化相关变量
            bool Init(PtrIServerEvent _event, int _max_conn = FD_SETSIZE);

            // 加入监听socket
            bool SetConnect(int _fd, bool _is_listener = false);

            // 执行逻辑
            void Work();

            // 结束的处理
            void Destroy();
        public:
            TcpSelectCore();
            ~TcpSelectCore();
		};
    }
}

#endif // !_X_LIBRARY_SERVER_SELECT_H_