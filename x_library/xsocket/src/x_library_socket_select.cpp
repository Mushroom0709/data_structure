#include "x_library_socket_select.h"

namespace xM
{
    namespace x_socket
    {

            bool TcpSelectCore::process_error(int _fd, int _res)
            {
                if (_res != 0)
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
                }
                else
                {
                    xInfoPrintln("[Socket %d:remote shutdown]", _fd);
                }

                if (event_ != nullptr)
                    event_->DisConnect(_fd);

                lock_mtx_.lock();

                conns_.erase(_fd);

                lock_mtx_.unlock();

                close(_fd);

                return true;
            }
            bool TcpSelectCore::process_receive(int _fd)
            {
                recv_len_ = ::recv(_fd, recv_buf_, X_SOCKET_MAX_BUF_SIZE, 0x00);
                if (recv_len_ <= 0)
                {
                    return process_error(_fd, recv_len_);
                }

                if (event_ != nullptr)
                    event_->Receive(_fd, recv_buf_, recv_len_);

                return true;
            }
            bool TcpSelectCore::process_accept()
            {
                struct sockaddr_in remote_addr = { 0 };
                socklen_t remote_addr_len = sizeof(struct sockaddr);

                int new_sock = ::accept(listener_fd_, (struct sockaddr*)&remote_addr, &remote_addr_len);
                if (new_sock == -1)
                {
                    xErrorPrintln("[accept:%d-%s]", errno, strerror(errno));
                    return false;
                }

                if (event_ != nullptr)
                    event_->Connected(new_sock);

                return true;
            }

            // 初始化相关变量
            bool TcpSelectCore::Init(PtrIEventBase _event, int _max_conn)
            {
                if (_event == nullptr)
                    return false;

                if (_max_conn <= 0 || _max_conn > FD_SETSIZE)
                    return false;

                event_ = _event;
                max_conn_ = _max_conn;
                listener_fd_ = X_FD_INVALID;

                return true;
            }

            // 加入监听socket
            bool TcpSelectCore::SetConnect(int _fd, bool _is_listener)
            {
                if (X_FD_INVALID == _fd)
                    return false;

                if (ConnectSize() > max_conn_)
                    return false;

                if (_is_listener == true)
                {
                    listener_fd_ = _fd;
                }
                else
                {
                    lock_mtx_.lock();
                    conns_.insert(_fd);
                    lock_mtx_.unlock();
                }

                return true;
            }

            // 执行逻辑
            void TcpSelectCore::Work()
            {
                timeval timeout;
                timeout.tv_sec = X_SOCKET_DEFUALT_TIMEOUT / 1000;
                timeout.tv_usec = (X_SOCKET_DEFUALT_TIMEOUT - (timeout.tv_sec * 1000)) * 1000;

                int slt_res = 0;
                fd_set read_fd;
                std::set<int> conns_copy;

                if (event_ != nullptr)
                    event_->Started(id_);

                run_flag_ = true;
                while (run_flag_)
                {
                    FD_ZERO(&read_fd);
                    if (listener_fd_ != X_FD_INVALID)
                        FD_SET(listener_fd_, &read_fd);

                    conns_copy.clear();

                    lock_mtx_.lock();
                    conns_copy.insert(conns_.begin(), conns_.end());
                    lock_mtx_.unlock();

                    for (auto item : conns_)
                    {
                        FD_SET(item, &read_fd);
                    }

                    slt_res = ::select(max_conn_ + 1, &read_fd, NULL, NULL, &timeout);
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
                        if ((listener_fd_ != X_FD_INVALID) && (FD_ISSET(listener_fd_, &read_fd) == 1))
                        {
                            if (false == process_accept())
                                run_flag_ = false;
                        }

                        for (auto item : conns_copy)
                        {
                            if (FD_ISSET(item, &read_fd) == 1)
                            {
                                if (false == process_receive(item))
                                    run_flag_ = false;
                            }
                        }
                    }
                }

                Destroy();

                if (event_ != nullptr)
                    event_->Stopped(id_);
            }

            // 结束的处理
            void TcpSelectCore::Destroy()
            {
                run_flag_ = false;

                lock_mtx_.lock();

                for (auto item : conns_)
                {
                    close(item);
                }

                conns_.clear();

                lock_mtx_.unlock();
            }

            TcpSelectCore::TcpSelectCore() :
                IServerCore()
            {
                //
            }
            TcpSelectCore::~TcpSelectCore()
            {
                Destroy();
            }

    }
}
