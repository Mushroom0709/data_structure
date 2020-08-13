# include "x_library_redis_base.h"

namespace xM
{
	namespace db
	{
		xRedisBase::xRedisBase()
		{
			ctx_ = nullptr;
		}
		xRedisBase::xRedisBase(xRedisBase&& _value)
		{
			ctx_ = std::move(_value.ctx_);
			_value.ctx_ = nullptr;
		}
		xRedisBase::~xRedisBase()
		{
			Close();
		}

		redisReply* xRedisBase::io_bin(std::vector<std::string>& _values)
		{
			redisReply* reply = nullptr;
			int size = _values.size();
			char* args[size];
			size_t lens[size];

			for (size_t i = 0; i < size; i++)
			{
				args[i] = const_cast<char*>(_values[i].data());
				lens[i] = _values[i].size();
			}

			return (redisReply*)redisCommandArgv(
				ctx_, size,
				const_cast<const char**>(args), const_cast<const size_t*>(lens));
		}

		bool xRedisBase::IOBin(std::vector<std::string>& _values)
		{
			bool status = false;
			redisReply* reply = io_bin(_values);

			if (reply != NULL)
			{
				status = true;
			}

			freeReplyObject(reply);

			return status;
		}
		bool xRedisBase::IOBin(std::vector<std::string>& _values, std::string& _result)
		{
			bool status = false;
			redisReply* reply = io_bin(_values);

			if (reply != NULL)
			{
				status = true;
				_result = std::move(std::string(reply->str, reply->len));
			}

			freeReplyObject(reply);

			return status;
		}
		bool xRedisBase::IOBin(std::vector<std::string>& _values, redisReply** _reply)
		{
			bool status = false;
			*_reply = io_bin(_values);

			if (*_reply != NULL)
			{
				status = true;
			}

			return status;
		}

		bool xRedisBase::IOString(const char* _format, ...)
		{
			bool status = false;
			va_list ap;
			va_start(ap, _format);
			redisReply* reply = (redisReply*)redisvCommand(ctx_, _format, ap);
			va_end(ap);

			if (reply != NULL)
				status = true;

			freeReplyObject(reply);
			return status;
		}
		bool xRedisBase::IOString(std::string& _result, const char* _format, ...)
		{
			bool status = false;
			va_list ap;
			va_start(ap, _format);
			redisReply* reply = (redisReply*)redisvCommand(ctx_, _format, ap);
			va_end(ap);

			if (reply != NULL)
			{
				_result = std::move(std::string(reply->str, reply->len));
				status = true;
			}

			freeReplyObject(reply);
			return status;
		}
		bool xRedisBase::IOString(redisReply** _reply, const char* _format, ...)
		{
			bool status = false;
			va_list ap;
			va_start(ap, _format);
			*_reply = (redisReply*)redisvCommand(ctx_, _format, ap);
			va_end(ap);

			if (*_reply != NULL)
				status = true;

			return status;
		}

		bool xRedisBase::Connect(const char* _ip, const int _port, struct timeval _timeout)
		{
			Close();

			ctx_ = redisConnectWithTimeout(_ip, _port, _timeout);
			if (ctx_ == NULL || ctx_->err != 0)
			{
				if (ctx_ != NULL)
					redisFree(ctx_);
				return false;
			}
			return true;
		}
		void xRedisBase::Close()
		{
			if (ctx_ != nullptr)
			{
				redisFree(ctx_);
				ctx_ = nullptr;
			}
		}
	}
}