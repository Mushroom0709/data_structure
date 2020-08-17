#include "x_library_socket_epoll.h"

namespace xM
{
    namespace x_socket
    {
        bool TcpEpollCore::process_error(int _fd, int _res)
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

            bool res = true;

            lock_mtx_.lock();

            if (-1 == epoll_ctl(ep_fd_, EPOLL_CTL_DEL, _fd, NULL))
            {
                xErrorPrintln("[epoll_ctl:%d-%s]", errno, strerror(errno));
                res = false;
            }

            conns_.erase(_fd);

            lock_mtx_.unlock();

            close(_fd);

            return res;
        }
        bool TcpEpollCore::process_receive(int _fd)
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
        bool TcpEpollCore::process_accept()
        {
            struct sockaddr_in remote_addr = { 0 };
            socklen_t remote_addr_len = sizeof(struct sockaddr);

            int new_sock = ::accept(listener_fd_, (struct sockaddr*)&remote_addr, &remote_addr_len);
            if (new_sock == -1)
            {
                xErrorPrintln("[accept:%d-%s]", errno, strerror(errno));
                return false;
            }

            //struct epoll_event evt = { 0 };
            //evt.events = EPOLLIN;
            //evt.data.fd = new_sock;

            //lock_mtx_.lock();

            //if (-1 == ::epoll_ctl(ep_fd_, EPOLL_CTL_ADD, new_sock, &evt))
            //{
            //    xErrorPrintln("[epoll_ctl:%d-%s]", errno, strerror(errno));
            //    close(new_sock);
            //    lock_mtx_.unlock();
            //    return false;
            //}

            //conns_.insert(new_sock);

            //lock_mtx_.unlock();

            if (event_ != nullptr)
                event_->Connected(new_sock);

            return true;
        }

        // 初始化相关变量
        bool TcpEpollCore::Init(PtrIEventBase _event, int _max_conn)
        {
            if (_event == nullptr)
                return false;

            if (_max_conn <= 0)
                return false;

            event_ = _event;
            max_conn_ = _max_conn;
            listener_fd_ = X_FD_INVALID;

            ep_fd_ = ::epoll_create(max_conn_);
            if (X_FD_INVALID == ep_fd_)
                return false;

            return true;
        }

        // 加入监听socket
        bool TcpEpollCore::SetConnect(int _fd, bool _is_listener)
        {
            if (X_FD_INVALID == _fd)
                return false;

            if (ConnectSize() > max_conn_)
                return false;

            if (_is_listener == true)
            {
                listener_fd_ = _fd;
            }

            struct epoll_event evt = { 0 };
            evt.events = EPOLLIN;
            evt.data.fd = _fd;

            lock_mtx_.lock();

            if (-1 == ::epoll_ctl(ep_fd_, EPOLL_CTL_ADD, _fd, &evt))
            {
                xErrorPrintln("[epoll_ctl:%d-%s]", errno, strerror(errno));
                close(_fd);
                lock_mtx_.unlock();
                return false;
            }

            conns_.insert(_fd);

            lock_mtx_.unlock();

            return true;
        }

        // 执行逻辑
        void TcpEpollCore::Work()
        {
            int cur = 0;
            int ev_cnt = 0;

            struct epoll_event ep_events_[1024];

            if (event_ != nullptr)
                event_->Started(id_);

            run_flag_ = true;
            while (run_flag_)
            {
                lock_mtx_.lock();
                ev_cnt = ::epoll_wait(ep_fd_, ep_events_, 1024, X_SOCKET_DEFUALT_TIMEOUT);
                lock_mtx_.unlock();

                if (ev_cnt == 0)
                {
                    //time out
                }
                else if (ev_cnt == -1)
                {
                    //error-type:
                    //EBADF
                    //EFAULT
                    //EINTR
                    //EINVAL

                    xErrorPrintln("[epoll_wait:%d-%s]", errno, strerror(errno));
                    run_flag_ = false;
                }
                else
                {
                    for (cur = 0; cur < ev_cnt; ++cur)
                    {
                        if ((ep_events_[cur].events & EPOLLERR) == EPOLLERR ||
                            (ep_events_[cur].events & EPOLLHUP) == EPOLLHUP)
                        {
                            xErrorPrintln("[EPOLLERR / EPOLLERR]");
                            process_error(ep_events_[cur].data.fd);
                        }
                        else if (ep_events_[cur].events & EPOLLIN == EPOLLIN)
                        {
                            if (ep_events_[cur].data.fd == listener_fd_)
                            {
                                if (false == process_accept())
                                    run_flag_ = false;
                            }
                            else
                            {
                                if (false == process_receive(ep_events_[cur].data.fd))
                                    run_flag_ = false;
                            }
                        }
                        else
                        {
                            xWaringPrintln("[Other events]");
                        }
                    }
                }
            }

            Distroy();

            if (event_ != nullptr)
                event_->Stopped(id_);
        }
        // 结束的处理
        void TcpEpollCore::Distroy()
        {
            run_flag_ = false;

            if (ep_fd_ != X_FD_INVALID)
            {
                close(ep_fd_);
                ep_fd_ = X_FD_INVALID;

                for (auto item : conns_)
                {
                    close(item);
                }

                conns_.clear();
            }
        }

        TcpEpollCore::TcpEpollCore() :
            IServerCore()
        {
            ep_fd_ = X_FD_INVALID;
        }
        TcpEpollCore::~TcpEpollCore()
        {
            Distroy();
        }

    }
}
