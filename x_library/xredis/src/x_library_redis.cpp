#include "x_library_redis.h"


namespace xM
{
	namespace db
	{
		xRedis::xRedis() :
			xRedisBase()
		{

		}
		xRedis::~xRedis()
		{
			//
		}

		bool xRedis::Set(std::string&& _key, std::string&& _value, REDIS_TIMEOUT_TYPE _type, time_t _timeout)
		{
			std::string result;
			std::vector<std::string> args;
			args.push_back("SET");
			args.push_back(std::move(_key));
			args.push_back(std::move(_value));
			switch (_type)
			{
			case RTT_SECONDS:
				args.push_back("EX");
				args.push_back(std::to_string(_timeout));
				break;
			case RTT_MILLISECONDS:
				args.push_back("PX");
				args.push_back(std::to_string(_timeout));
				break;
			}

			if (true == xRedisBase::IOBin(args, result) && result == "OK")
				return true;
			return false;
		}
		int	 xRedis::Del(std::string&& _key)
		{
			std::string result;
			std::vector<std::string> args;
			args.push_back("DEL");
			args.push_back(std::move(_key));

			if (false == xRedisBase::IOBin(args, result))
				return 0;
			return atoi(result.c_str());
		}
		bool xRedis::Get(std::string&& _key, std::string& _value)
		{
			std::string result;
			std::vector<std::string> args;
			args.push_back("GET");
			args.push_back(std::move(_key));

			if (false == xRedisBase::IOBin(args, _value))
				return false;
			return true;
		}
		bool xRedis::Exists(std::string&& _key)
		{
			std::string result;
			std::vector<std::string> args;
			args.push_back("EXISTS");
			args.push_back(std::move(_key));

			if (true == xRedisBase::IOBin(args, result) && result == "1")
				return true;
			return false;
		}
		bool xRedis::Expire(std::string&& _key, REDIS_TIMEOUT_TYPE _type, time_t _timeout)
		{
			std::string result;
			std::vector<std::string> args;
			switch (_type)
			{
			case RTT_SECONDS:
				args.push_back("EXPIRE");
				break;
			case RTT_MILLISECONDS:
				args.push_back("PEXPIRE");
				break;

			default:
				return false;
			}
			args.push_back(std::move(_key));
			args.push_back(std::to_string(_timeout));

			if (true == xRedisBase::IOBin(args, result) && result == "1")
				return true;
			return false;
		}
		bool xRedis::ExpireAt(std::string&& _key, REDIS_TIMEOUT_TYPE _type, time_t _timeout)
		{
			std::string result;
			std::vector<std::string> args;
			switch (_type)
			{
			case RTT_SECONDS:
				args.push_back("EXPIREAT");
				break;
			case RTT_MILLISECONDS:
				args.push_back("PEXPIREAT");
				break;

			default:
				return false;
			}
			args.push_back(std::move(_key));
			args.push_back(std::to_string(_timeout));

			if (true == xRedisBase::IOBin(args, result) && result == "1")
				return true;
			return false;
		}
		bool xRedis::Keys(std::string&& _pattern, std::vector<std::string>& _keys)
		{
			std::string result;
			std::vector<std::string> args;
			args.push_back("KEYS");
			args.push_back(std::move(_pattern));

			bool flag = false;
			redisReply* rp = nullptr;
			if (true == xRedisBase::IOBin(args, &rp))
			{
				_keys.clear();
				for (size_t i = 0; i < rp->elements; i++)
				{
					_keys.push_back(std::move(std::string(rp->element[i]->str, rp->element[i]->len)));
				}
				flag = true;
			}

			freeReplyObject(rp);
			return flag;
		}
		bool xRedis::Persist(std::string&& _key)
		{
			std::string result;
			std::vector<std::string> args;
			args.push_back("PERSIST");
			args.push_back(std::move(_key));

			if (true == xRedisBase::IOBin(args, result) && result == "1")
				return true;
			return false;
		}
		bool xRedis::TTL(std::string&& _key, REDIS_TIMEOUT_TYPE _type, time_t& _ttl)
		{
			std::string result;
			std::vector<std::string> args;
			switch (_type)
			{
			case RTT_SECONDS:
				args.push_back("TTL");
				break;
			case RTT_MILLISECONDS:
				args.push_back("PTTL");
				break;
			}
			args.push_back(std::move(_key));

			bool flag = false;
			redisReply* rp = nullptr;
			if (true == xRedisBase::IOBin(args, &rp))
			{
				_ttl = rp->integer;
				flag =  true;
			}
			freeReplyObject(rp);
			return flag;
		}
		bool xRedis::Type(std::string&& _key, std::string& _type)
		{
			std::string result;
			std::vector<std::string> args;
			args.push_back("Type");
			args.push_back(std::move(_key));

			return xRedisBase::IOBin(args, _type);
		}
	}
}