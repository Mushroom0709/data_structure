#ifndef _X_LIBRARY_SOCKET_SERVER_H_
#define _X_LIBRARY_SOCKET_SERVER_H_

#include "x_library_socket_base.h"

#include <thread>

namespace xM
{
    namespace x_socket
    {
        template<class _Core = TcpCoreBase>
        class TcpServer:
            public TcpServerBase
        {
#define MAX_LISTEN 128
        private:
            _Core core_;
            std::thread work_thread_;
        private:
            bool init_net(int _port,const char* _ip)
            {
                struct sockaddr_in addr;
                memset(&addr, 0, sizeof(sockaddr_in));
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = inet_addr(_ip);
                addr.sin_port = htons(_port);

                core_.listen_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
                if (core_.listen_ == -1)
                {
                    xErrorPrintln("[socket:%d-%s]", errno, strerror(errno));
                    return false;
                }

                if (-1 == ::bind(core_.listen_, (struct sockaddr*)&addr, sizeof(struct sockaddr)))
                {
                    xErrorPrintln("[bind:%d-%s]", errno, strerror(errno));
                    return false;
                }

                if (-1 == ::listen(core_.listen_, MAX_LISTEN))
                {
                    xErrorPrintln("[listen:%d-%s]", errno, strerror(errno));
                    return false;
                }

                return true;
            }
            void close_net()
            {
                if (core_.listen_ != -1)
                {
                    ::close(core_.listen_);
                    core_.listen_ = -1;
                }
            }
        public:
            bool Start(EventBase* _ev, int _port, const char* _ip = "0.0.0.0")
            {
                if (core_.run_flag_ == true)
                    return false;

                core_.event_ = _ev;

                if (false == init_net(_port, _ip))
                    return false;

                if (false == core_.make())
                    return false;

                core_.run_flag_ = true;
                work_thread_ = std::move(std::thread(&_Core::work,&core_));
                return true;
            }
            void Stop()
            {
                core_.run_flag_ = false;

                close_net();

                if (work_thread_.joinable())
                    work_thread_.join();

                core_.destroy();
                close_net();
            }
        public:
            int Send(int _fd, uint8_t* _data, size_t _size)
            {
                if (core_.run_flag_ == false)
                    return false;

                size_t result = 0;
                size_t current = 0;
                while (current < _size)
                {
                    result = send(_fd, _data + current, _size - current, 0);
                    if (result < 0)
                        return false;

                    current += result;
                }
                return true;
            }
        public:
            TcpServer():
                TcpServerBase()
            {
                //
            }
            ~TcpServer()
            {
                Stop();
            }
        };
    }
}

#endif // !_X_LIBRARY_SOCKET_SERVER_H_