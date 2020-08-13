#include "x_library_socket_epoll.h"
#include "x_library_socket_select.h"
#include "x_library_socket_server.h"

#include <time.h>

class EPollTest :
	public xM::x_socket::EventBase
{
private:
	xM::x_socket::TcpServer<xM::x_socket::TcpEpollCore> server_;
	//xM::x_socket::TcpServer<xM::x_socket::TcpSelectCore> server_;
private:
	virtual void Connected(int _fd)
	{	
		xInfoPrintln("[Connected] [%d]", _fd);
	}
	virtual void DisConnect(int _fd)
	{
		xInfoPrintln("[DisConnect] [%d]", _fd);
	}
	virtual void Receive(int _fd, uint8_t* _data, size_t _size)
	{
		xInfoPrintln("[Receive] [%s]", (char *)_data);

		std::string str = std::to_string(time(NULL));
		server_.Send(_fd, (uint8_t*)str.c_str(), str.length());
	}
	virtual void Started()
	{
		xInfoPrintln("[Started]");
	}
	virtual void Stopped()
	{
		xInfoPrintln("[Stopped]");
	}
public:
	EPollTest()
	{
		//
	}
	~EPollTest()
	{
		//
	}
public:
	bool Start()
	{
		return server_.Start(this, 20301);
	}
	void Stop()
	{
		server_.Stop();
	}
};

int main()
{
	EPollTest test;
	if (test.Start())
	{
		getchar();
		test.Stop();
	}
	getchar();

	return 0;
}
