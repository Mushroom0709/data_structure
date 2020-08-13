#ifndef _X_LIBRARY_REDIS_BASE_H_
#define _X_LIBRARY_REDIS_BASE_H_

#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

extern "C" 
{
#include <hiredis/hiredis.h>
}

namespace xM
{
	namespace db
	{
		class xRedisBase
		{
		private:
			redisContext* ctx_ = nullptr;
		public:
			xRedisBase();
			xRedisBase(const xRedisBase&) = delete;
			xRedisBase(xRedisBase&& _value);
			virtual ~xRedisBase();
		private:
			redisReply* io_bin(std::vector<std::string>& _values);
		public:
			bool IOBin(std::vector<std::string>& _values);
			bool IOBin(std::vector<std::string>& _values, std::string& _result);
			bool IOBin(std::vector<std::string>& _values, redisReply** _reply);

			bool IOString(const char* _format, ...);
			bool IOString(std::string& _result, const char* _format, ...);
			bool IOString(redisReply** _reply, const char* _format, ...);
		public:
			bool Connect(const char* _ip = "127.0.0.1", const int _port = 6379, struct timeval _timeout = { 1,0 });
			void Close();
		};
	}
}

#endif // !_X_LIBRARY_REDIS_BASE_H_