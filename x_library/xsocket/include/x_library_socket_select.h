#ifndef _X_LIBRARY_SOCKET_SELECT_H_
#define _X_LIBRARY_SOCKET_SELECT_H_

#include "x_library_socket_base.h"

#include <sys/select.h>

namespace xM
{
    namespace x_socket
    {
		class TcpSelectCore:
			public TcpCoreBase
		{
		private:
			fd_set read_fd_;
			int fd_cache_[FD_SETSIZE];

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
			TcpSelectCore();
			~TcpSelectCore();
		};
    }
}

#endif // !_X_LIBRARY_SOCKET_SELECT_H_