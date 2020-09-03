#include "x_library_connect_select.h"
#include "x_library_socket_tcp_connect.h"

#include <time.h>

class SockConnect :
	public xM::x_socket::IConnectEvent
{
private:
	xM::x_socket::TcpConnect<xM::x_socket::ConnectSelectCore> connect_;
	//xM::x_socket::TcpConnect connect_;
private:
	virtual void Receive(int _fd, uint8_t* _data, size_t _size)
	{
		xInfoPrintln("[Receive] [%s]", (char*)_data);

		std::string str = std::to_string(time(NULL));
		connect_.Send(_fd, (uint8_t*)str.c_str(), str.length());
	}
public:
	SockConnect()
	{
		//
	}
	~SockConnect()
	{
		//
	}
public:
	bool Start()
	{
		return connect_.Connect(this, 20301,"192.168.137.1");
	}
	void Stop()
	{
		connect_.Disconnect();
	}
};

int main()
{
	SockConnect test;
	if (test.Start())
	{
		getchar();
		test.Stop();
	}

	return 0;
}
