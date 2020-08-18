#ifndef _X_LIBRARY_SOCKET_TCP_SERVER_H_
#define _X_LIBRARY_SOCKET_TCP_SERVER_H_

//#include "x_library_socket_epoll.h"
#include "x_library_socket_base.h"
#include <thread>
namespace xM
{
    namespace x_socket
    {
        template<class _ServerCore = IServerCore>
        class TcpServer :
            public IServer
        {
        private:
            _ServerCore core_;
            std::thread work_thread_;
        private:
            void Connected(int _fd)
            {
                if (true == core_.SetConnect(_fd))
                {
                    if(event_ != nullptr)
                        event_->Connected(_fd);
                }
                else
                {
                    close(_fd);
                    // waring max_connect
                }
            }
            void DisConnect(int _fd)
            {
                if (event_ != nullptr)
                    event_->DisConnect(_fd);
            }
            void Receive(int _fd, uint8_t* _data, size_t _size)
            {
                if (event_ != nullptr)
                    event_->Receive(_fd, _data, _size);
            }
            void Started(int _id)
            {
                //if (event_ != nullptr)
                //    event_->Started(_id);
            }
            void Stopped(int _id)
            {
                //if (event_ != nullptr)
                //    event_->Stopped(_id);
            }
        private:
            bool init_net(int _port, const char* _ip)
            {
                struct sockaddr_in addr;
                memset(&addr, 0, sizeof(sockaddr_in));
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = inet_addr(_ip);
                addr.sin_port = htons(_port);

                listener_fd_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
                if (listener_fd_ == -1)
                {
                    xErrorPrintln("[socket:%d-%s]", errno, strerror(errno));
                    return false;
                }

                if (-1 == ::bind(listener_fd_, (struct sockaddr*)&addr, sizeof(struct sockaddr)))
                {
                    xErrorPrintln("[bind:%d-%s]", errno, strerror(errno));
                    return false;
                }

                if (-1 == ::listen(listener_fd_, X_SOCKET_DEFUALT_LISTEN_CNT))
                {
                    xErrorPrintln("[listen:%d-%s]", errno, strerror(errno));
                    return false;
                }

                return true;
            }
            void close_net()
            {
                if (listener_fd_ != X_FD_INVALID)
                {
                    ::close(listener_fd_);
                    listener_fd_ = X_FD_INVALID;
                }
            }
        public:
            bool Start(IEventBase* _ev, int _port, const char* _ip = "0.0.0.0")
            {
                if (listener_fd_ != X_FD_INVALID)
                    return false;

                event_ = _ev;

                if (false == init_net(_port, _ip))
                    return false;

                if (false == core_.Init(this))
                    return false;

                if (false == core_.SetConnect(listener_fd_, true))
                    return false;

                work_thread_ = std::move(std::thread(&_ServerCore::Work, &core_));
                return true;
            }
            void Stop()
            {
                core_.Stop();

                close_net();

                if (work_thread_.joinable())
                    work_thread_.join();

                core_.Destroy();
            }
        public:
            TcpServer() :
                IServer()
            {

            }
            ~TcpServer()
            {

            }
        };

    }
}

#endif // !_X_LIBRARY_SOCKET_TCP_SERVER_H_