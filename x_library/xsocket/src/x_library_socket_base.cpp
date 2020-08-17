#include "x_library_socket_base.h"

namespace xM
{
    namespace x_socket
    {
        void IServerCore::Stop()
        {
            run_flag_ = false;
        }
        std::size_t IServerCore::ConnectSize()
        {
            std::lock_guard<std::mutex> auto_lock(lock_mtx_);
            return conns_.size();
        }
        bool IServerCore::SetID(int _id)
        {
            if (run_flag_ == false)
            {
                id_ = _id;
                return true;
            }
            return false;
        }

        int IServerCore::GetID()
        {
            return id_;
        }

        bool IServerCore::SendAll(uint8_t* _data, size_t _size, bool err_back)
        {
            if (run_flag_ == false || _size <= 0)
                return false;

            std::lock_guard<std::mutex> auto_lock(lock_mtx_);

            for (auto item : conns_)
            {
                size_t result = 0;
                size_t current = 0;
                while (current < _size)
                {
                    result = send(item, _data + current, _size - current, 0);
                    if (result < 0)
                    {
                        if (err_back == true)
                            return false;
                        else
                            goto SENDALL_NEXT_CUR;
                    }
                    current += result;
                }
            SENDALL_NEXT_CUR:;
            }

            return true;
        }

        IServerCore::IServerCore()
        {
            run_flag_ = false;
            event_ = nullptr;
            max_conn_ = 0;
            listener_fd_ = X_FD_INVALID;
            id_ = -1;
        }
        IServerCore::~IServerCore()
        {
            //
        }



        int IServer::Send(int _fd, uint8_t* _data, size_t _size)
        {
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

        IServer::IServer()
        {
            listener_fd_ = X_FD_INVALID;
            event_ = nullptr;
        }
        IServer::~IServer()
        {
            //
        }
    }
}