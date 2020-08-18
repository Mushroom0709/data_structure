#ifndef _X_LIBRARY_SOCKET_BASE_H_
#define _X_LIBRARY_SOCKET_BASE_H_

#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <atomic>
#include <mutex>
#include <set>

#include "x_library_common.hpp"

namespace xM
{
    namespace x_socket
    {
        class IEventBase
        {
        public:
            virtual void Connected(int _fd) {};
            virtual void DisConnect(int _fd) {};
            virtual void Receive(int _fd, uint8_t* _data, size_t _size) {};
            virtual void Started(int _id) {};
            virtual void Stopped(int _id) {};
        };

        typedef IEventBase* PtrIEventBase;

#define X_SOCKET_MAX_CONNECT INT16_MAX

#define X_SOCKET_MAX_BUF_SIZE 4096

#define X_SOCKET_DEFUALT_TIMEOUT 50

        class IServerCore
        {
        protected:
            int id_;

            std::atomic<bool> run_flag_;
            PtrIEventBase event_;

            int listener_fd_;

            std::mutex lock_mtx_;
            int max_conn_;
            std::set<int> conns_;
        public:
            // ��ʼ����ر���
            virtual bool Init(PtrIEventBase _event, int _max_conn) = 0;

            // �������socket
            virtual bool SetConnect(int _fd,bool _is_listener) = 0;

            // ִ���߼�
            virtual void Work() = 0;

            // �����Ĵ���
            virtual void Destroy() = 0;

            // ִֹͣ���߼�
            virtual void Stop();

            // ������
            virtual std::size_t ConnectSize();

            // ���ú���ID
            virtual bool SetID(int _id);

            // ��ȡ����ID
            int GetID();

            // ȫ������
            bool SendAll(uint8_t* _data, size_t _size,bool err_back = false);
        public:
            IServerCore();
            virtual ~IServerCore();
        };

        class IServer:
            public IEventBase
        {
#define  X_SOCKET_DEFUALT_LISTEN_CNT 256
        protected:
            int listener_fd_;
            PtrIEventBase event_;
        public:
            virtual bool Start(PtrIEventBase _ev, int _port, const char* _ip) = 0;
            virtual void Stop() = 0;
            virtual int Send(int _fd, uint8_t* _data, size_t _size);
        public:
            IServer();
            virtual ~IServer();
        };
    }
}

# endif //!_X_LIBRARY_SOCKET_BASE_H_