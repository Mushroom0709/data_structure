#include "x_library_socket_select.h"

namespace xM
{
	namespace x_socket
	{
			bool TcpSelectCore::process_socket_error(int _fd)
			{
				int error = 0;
				socklen_t errlen = sizeof(error);
				if (::getsockopt(_fd, SOL_SOCKET, SO_ERROR, (void*)&error, &errlen) == 0)
				{
					if (error != 0)
						xErrorPrintln("[Socket %d:%d-%s]", _fd, error, strerror(error));
				}
				else
					xErrorPrintln("[Socket %d]", _fd);

				if (event_ != nullptr)
					event_->DisConnect(_fd);

				for (size_t i = 0; i < FD_SETSIZE; i++)
				{
					if (fd_cache_[i] == _fd)
						fd_cache_[i] = -1;
				}

				close(_fd);

				return true;
			}
			bool TcpSelectCore::process_accept()
			{
				struct sockaddr_in remote_addr = { 0 };
				socklen_t remote_addr_len = sizeof(struct sockaddr);

				int new_sock = ::accept(listen_, (struct sockaddr*)&remote_addr, &remote_addr_len);
				if (new_sock == -1)
				{
					xErrorPrintln("[accept:%d-%s]", errno, strerror(errno));
					return false;
				}

				for (size_t i = 0; i < FD_SETSIZE; i++)
				{
					if (fd_cache_[i] == -1)
						fd_cache_[i] = new_sock;
				}

				if (event_ != nullptr)
					event_->Connected(new_sock);
				return true;
			}
			bool TcpSelectCore::process_receive(int _fd)
			{
				recv_len_ = ::recv(_fd, recv_buf_, XS_MAX_BUFFER, 0x00);
				if (recv_len_ <= 0)
				{
					return process_socket_error(_fd);
				}

				if (event_ != nullptr)
					event_->Receive(_fd, recv_buf_, recv_len_);

				return true;
			}

			bool TcpSelectCore::make()
			{
				return true;
			}
			void TcpSelectCore::work()
			{
				timeval timeout;
				timeout.tv_sec = XS_TIME_WAIT / 1000;
				timeout.tv_usec = (XS_TIME_WAIT - (timeout.tv_sec * 1000)) * 1000;

				int slt_res = 0;

				if (event_ != nullptr)
					event_->Started();

				while (run_flag_)
				{
					FD_ZERO(&read_fd_);
					FD_SET(listen_, &read_fd_);

					for (size_t i = 0; i < FD_SETSIZE; i++)
					{
						if (fd_cache_[i] != -1)
						{
							FD_SET(fd_cache_[i], &read_fd_);
						}
					}

					slt_res = ::select(FD_SETSIZE + 1, &read_fd_, NULL, NULL, &timeout);
					if (slt_res == 0)
					{
						//timeout
					}
					else if (slt_res == -1)
					{
						xErrorPrintln("[epoll_wait:%d-%s]", errno, strerror(errno));
						run_flag_ = false;
					}
					else
					{
						if (FD_ISSET(listen_, &read_fd_) == 1)
						{
							if (false == process_accept())
								run_flag_ = false;
						}

						for (size_t i = 0; i < FD_SETSIZE; i++)
						{
							if (-1 != fd_cache_[i] && (FD_ISSET(fd_cache_[i], &read_fd_) == 1))
							{
								if (false == process_receive(fd_cache_[i]))
									run_flag_ = false;
							}
						}
					}
				}

				destroy();

				if (event_ != nullptr)
					event_->Stopped();
			}
			void TcpSelectCore::destroy()
			{
				for (size_t i = 0; i < FD_SETSIZE; i++)
				{
					if (fd_cache_[i] != -1)
					{
						close(fd_cache_[i]);
						fd_cache_[i] = -1;
					}
				}
			}

			TcpSelectCore::TcpSelectCore() :
				TcpCoreBase()
			{
				for (size_t i = 0; i < FD_SETSIZE; i++)
				{
					fd_cache_[i] = -1;
				}
			}
			TcpSelectCore::~TcpSelectCore()
			{
				destroy();
			}

	}
}