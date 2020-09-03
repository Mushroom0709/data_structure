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
            virtual void Receive(int _fd, uint8_t* _data, size_t _size) {};
        };

        class IServerEvent:
            public IEventBase
        {
        public:
            virtual void Connected(int _fd) {};
            virtual void DisConnect(int _fd) {};
            virtual void Started(int _id) {};
            virtual void Stopped(int _id) {};
        };

        typedef IServerEvent* PtrIServerEvent;

        class IConnectEvent :
            public IEventBase
        {

        };

        typedef IConnectEvent* PtrIConnectEvent;

#define X_SOCKET_MAX_CONNECT INT16_MAX

#define X_SOCKET_MAX_BUF_SIZE 4096

#define X_SOCKET_DEFUALT_TIMEOUT 50

        class IServer :
            public IServerEvent
        {
#define  X_SOCKET_DEFUALT_LISTEN_CNT 256
        protected:
            int listener_fd_;
            PtrIServerEvent event_;
        public:
            virtual bool Start(PtrIServerEvent _ev, int _port, const char* _ip) = 0;
            virtual void Stop() = 0;
            virtual int Send(int _fd, uint8_t* _data, size_t _size);
        public:
            IServer();
            virtual ~IServer();
        };

        class IServerCore
        {
        protected:
            int id_;

            std::atomic<bool> run_flag_;
            PtrIServerEvent event_;

            int listener_fd_;

            std::mutex lock_mtx_;
            int max_conn_;
            std::set<int> conns_;
        public:
            // 初始化相关变量
            virtual bool Init(PtrIServerEvent _event, int _max_conn) = 0;

            // 加入监听socket
            virtual bool SetConnect(int _fd,bool _is_listener) = 0;

            // 执行逻辑
            virtual void Work() = 0;

            // 结束的处理
            virtual void Destroy() = 0;

            // 停止执行逻辑
            virtual void Stop();

            // 连接数
            virtual std::size_t ConnectSize();

            // 设置核心ID
            virtual bool SetID(int _id);

            // 获取核心ID
            int GetID();

            // 全部发送
            bool SendAll(uint8_t* _data, size_t _size,bool err_back = false);
        public:
            IServerCore();
            virtual ~IServerCore();
        };

        class IConnect :
            public IConnectEvent
        {
        protected:
            int conn_fd_;
            PtrIConnectEvent event_;
        public:
            virtual bool Connect(PtrIConnectEvent _ev, int _port, const char* _ip) = 0;
            virtual void Disconnect() = 0;
            int Send(int _fd,uint8_t* _data, size_t _size);
        public:
            IConnect();
            virtual ~IConnect();
        };

        class IConnectCore
        {
        protected:
            std::atomic<bool> run_flag_;
            PtrIConnectEvent event_;

            int conn_fd_;
        public:
            // 初始化相关变量
            virtual bool Init(PtrIConnectEvent _event, int _conn_fd) = 0;

            // 执行逻辑
            virtual void Work() = 0;

            // 结束的处理
            virtual void Destroy() = 0;

            // 停止执行逻辑
            virtual void Stop();
        public:
            IConnectCore();
            virtual ~IConnectCore();
        };
    }
}

# endif //!_X_LIBRARY_SOCKET_BASE_H_