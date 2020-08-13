#include "x_library_socket_epoll.h"

namespace xM
{
    namespace x_socket
    {
        bool TcpEpollCore::process_socket_error(int _fd)
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

            bool res = true;
            if (-1 == epoll_ctl(ep_fd_, EPOLL_CTL_DEL, _fd, NULL))
            {
                xErrorPrintln("[epoll_ctl:%d-%s]", errno, strerror(errno));
                res = false;
            }

            for (size_t i = 0; i < XS_MAX_CREATE; i++)
            {
                if (fd_cache_[i] == _fd)
                    fd_cache_[i] = -1;
            }

            close(_fd);

            return res;
        }
        bool  TcpEpollCore::process_accept()
        {
            struct sockaddr_in remote_addr = { 0 };
            socklen_t remote_addr_len = sizeof(struct sockaddr);

            int new_sock = ::accept(listen_, (struct sockaddr*)&remote_addr, &remote_addr_len);
            if (new_sock == -1)
            {
                xErrorPrintln("[accept:%d-%s]", errno, strerror(errno));
                return false;
            }

            struct epoll_event evt = { 0 };
            evt.events = EPOLLIN;
            evt.data.fd = new_sock;

            if (-1 == ::epoll_ctl(ep_fd_, EPOLL_CTL_ADD, new_sock, &evt))
            {
                xErrorPrintln("[epoll_ctl:%d-%s]", errno, strerror(errno));
                close(new_sock);
                return false;
            }

            for (size_t i = 0; i < XS_MAX_CREATE; i++)
            {
                if (fd_cache_[i] == -1)
                    fd_cache_[i] = new_sock;
            }

            if (event_ != nullptr)
                event_->Connected(new_sock);
            return true;
        }
        bool  TcpEpollCore::process_receive(int _fd)
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

        bool  TcpEpollCore::make()
        {
            ep_fd_ = ::epoll_create(XS_MAX_CREATE);
            if (-1 == ep_fd_)
                return false;

            struct epoll_event listener_event;
            listener_event.events = EPOLLIN;
            listener_event.data.fd = listen_;
            if (-1 == ::epoll_ctl(ep_fd_, EPOLL_CTL_ADD, listen_, &listener_event))
            {
                return false;
            }

            return true;
        }
        void TcpEpollCore::work()
        {
            int cur = 0;
            int ev_cnt = 0;

            if (event_ != nullptr)
                event_->Started();

            while (run_flag_)
            {
                ev_cnt = ::epoll_wait(ep_fd_, ep_events_, XS_MAX_CREATE, XS_TIME_WAIT);
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
                            process_socket_error(ep_events_[cur].data.fd);
                        }
                        else if (ep_events_[cur].events & EPOLLIN == EPOLLIN)
                        {
                            if (ep_events_[cur].data.fd == listen_)
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

            destroy();

            if (event_ != nullptr)
                event_->Stopped();
        }
        void TcpEpollCore::destroy()
        {
            if (ep_fd_ != -1)
            {
                ::close(ep_fd_);
                ep_fd_ = -1;

                for (size_t i = 0; i < XS_MAX_CREATE; i++)
                {
                    if (fd_cache_[i] != -1)
                    {
                        epoll_ctl(ep_fd_, EPOLL_CTL_DEL, fd_cache_[i], NULL);
                        close(fd_cache_[i]);
                        fd_cache_[i] = -1;
                    }
                }
            }
        }

        TcpEpollCore::TcpEpollCore():
            TcpCoreBase()
        {
            for (size_t i = 0; i < XS_MAX_CREATE; i++)
            {
                fd_cache_[i] = -1;
            }
        }
        TcpEpollCore::~TcpEpollCore()
        {
            destroy();
        }
    }
}