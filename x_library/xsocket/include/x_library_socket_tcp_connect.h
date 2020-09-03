#ifndef _X_LIBRARY_SOCKET_TCP_CONNECT_H_
#define _X_LIBRARY_SOCKET_TCP_CONNECT_H_

#include "x_library_socket_base.h"
//#include "x_library_connect_select.h"
#include <thread>

namespace xM
{
    namespace x_socket
    {
        template<class _ConnectCore = IConnectCore>
		class TcpConnect:
			public IConnect
		{
        private:
            _ConnectCore core_;
            std::thread work_thread_;
        private:
            void Receive(int _fd, uint8_t* _data, size_t _size)
            {
                if (event_ != nullptr)
                    event_->Receive(_fd, _data, _size);
            }
		private:
			bool init_net(int _port,const char* _ip)
			{
                struct sockaddr_in addr;
                memset(&addr, 0, sizeof(sockaddr_in));
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = inet_addr(_ip);
                addr.sin_port = htons(_port);

                conn_fd_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
                if (conn_fd_ == -1)
                {
                    xErrorPrintln("[socket:%d-%s]", errno, strerror(errno));
                    return false;
                }

                if (-1 == ::connect(conn_fd_, (struct sockaddr*)&addr, sizeof(struct sockaddr)))
                {
                    xErrorPrintln("[connect:%d-%s]", errno, strerror(errno));
                    return false;
                }

                return true;
			}
            void close_net()
            {
                if (conn_fd_ != X_FD_INVALID)
                {
                    ::close(conn_fd_);
                    conn_fd_ = X_FD_INVALID;
                }
            }
        public:
            bool Connect(PtrIConnectEvent _ev, int _port, const char* _ip)
            {
                if (conn_fd_ != X_FD_INVALID)
                    return false;

                event_ = _ev;

                if (false == init_net(_port, _ip))
                    return false;

                if (false == core_.Init(this, conn_fd_))
                    return false;

                work_thread_ = std::move(std::thread(&_ConnectCore::Work, &core_));
                return true;
            }
            void Disconnect()
            {
                core_.Stop();

                close_net();

                if (work_thread_.joinable())
                    work_thread_.join();

                core_.Destroy();
            }
        public:
            TcpConnect() :
                IConnect()
            {

            }
            ~TcpConnect()
            {

            }
		};
    }
}

#endif //!_X_LIBRARY_SOCKET_TCP_CONNECT_H_