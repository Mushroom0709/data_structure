#ifndef _X_LIBRARY_REDIS_H_
#define _X_LIBRARY_REDIS_H_

#include "x_library_redis_base.h"

namespace xM
{
	namespace db
	{
		typedef enum _REDIS_TIMEOUT_TYPE_
		{
			RTT_NONE = 0x00,
			RTT_SECONDS = 0x10,
			RTT_MILLISECONDS = 0x11
		}REDIS_TIMEOUT_TYPE;

		class xRedis:
			public xRedisBase
		{
		public:
			xRedis();
			~xRedis();
		public:
			//设置指定 key 的值
			bool Set(std::string&& _key, std::string&& _value, REDIS_TIMEOUT_TYPE _type = RTT_NONE, time_t _timeout = 0);

			//删除指定 key。
			int  Del(std::string&& _key);

			//获取指定 key 的值。
			bool Get(std::string&& _key, std::string& _value);

			//检查给定 key 是否存在。
			bool Exists(std::string&& _key);

			//为给定 key 设置过期时间, 以秒 或者 毫秒 计。
			bool Expire(std::string&& _key, REDIS_TIMEOUT_TYPE _type, time_t _timeout);

			//为给定 key 设置过期时间, 以unix时间戳的 秒 或者 毫秒 计。
			bool ExpireAt(std::string&& _key, REDIS_TIMEOUT_TYPE _type, time_t _timeout);

			//查找所有符合给定模式(pattern)的 key 。
			bool Keys(std::string&& _pattern, std::vector<std::string>& _keys);

			//移除 key 的过期时间，key 将持久保持。
			bool Persist(std::string&& _key);

			//以 秒 或者 毫秒 为单位返回 key 的剩余的过期时间
			bool TTL(std::string&& _key, REDIS_TIMEOUT_TYPE _type, time_t& _ttl);

			//返回 key 所储存的值的类型。
			bool Type(std::string&& _key, std::string& _type);
		};
	}
}

#endif // !_X_LIBRARY_REDIS_H_