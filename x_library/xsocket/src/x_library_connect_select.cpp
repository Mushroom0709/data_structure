#include "x_library_connect_select.h"

namespace xM
{
    namespace x_socket
    {

        bool ConnectSelectCore::process_error(int _fd, int _res)
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

            return false;
        }
        bool ConnectSelectCore::process_receive(int _fd)
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

        bool ConnectSelectCore::Init(PtrIConnectEvent _event, int _conn_fd)
        {
            if (_event == nullptr || _conn_fd == X_FD_INVALID)
                return false;

            event_ = _event;
            conn_fd_ = _conn_fd;

            return true;
        }
        void ConnectSelectCore::Work()
        {
            timeval timeout;
            timeout.tv_sec = X_SOCKET_DEFUALT_TIMEOUT / 1000;
            timeout.tv_usec = (X_SOCKET_DEFUALT_TIMEOUT - (timeout.tv_sec * 1000)) * 1000;

            int slt_res = 0;
            fd_set read_fd;

            run_flag_ = true;
            while (run_flag_)
            {
                FD_ZERO(&read_fd);
                FD_SET(conn_fd_, &read_fd);

                slt_res = ::select(conn_fd_ + 1, &read_fd, NULL, NULL, &timeout);
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
                    if (FD_ISSET(conn_fd_, &read_fd) == 1)
                    {
                        if (false == process_receive(conn_fd_))
                            run_flag_ = false;
                    }
                }
            }

            Destroy();
        }
        void ConnectSelectCore::Destroy()
        {
            //
        }

        ConnectSelectCore::ConnectSelectCore()
        {
            //
        }
        ConnectSelectCore::~ConnectSelectCore()
        {
            Destroy();
        }
    }
}

