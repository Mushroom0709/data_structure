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
			//����ָ�� key ��ֵ
			bool Set(std::string&& _key, std::string&& _value, REDIS_TIMEOUT_TYPE _type = RTT_NONE, time_t _timeout = 0);

			//ɾ��ָ�� key��
			int  Del(std::string&& _key);

			//��ȡָ�� key ��ֵ��
			bool Get(std::string&& _key, std::string& _value);

			//������ key �Ƿ���ڡ�
			bool Exists(std::string&& _key);

			//Ϊ���� key ���ù���ʱ��, ���� ���� ���� �ơ�
			bool Expire(std::string&& _key, REDIS_TIMEOUT_TYPE _type, time_t _timeout);

			//Ϊ���� key ���ù���ʱ��, ��unixʱ����� �� ���� ���� �ơ�
			bool ExpireAt(std::string&& _key, REDIS_TIMEOUT_TYPE _type, time_t _timeout);

			//�������з��ϸ���ģʽ(pattern)�� key ��
			bool Keys(std::string&& _pattern, std::vector<std::string>& _keys);

			//�Ƴ� key �Ĺ���ʱ�䣬key ���־ñ��֡�
			bool Persist(std::string&& _key);

			//�� �� ���� ���� Ϊ��λ���� key ��ʣ��Ĺ���ʱ��
			bool TTL(std::string&& _key, REDIS_TIMEOUT_TYPE _type, time_t& _ttl);

			//���� key �������ֵ�����͡�
			bool Type(std::string&& _key, std::string& _type);
		};
	}
}

#endif // !_X_LIBRARY_REDIS_H_