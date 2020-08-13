#include "x_library_redis.h"

int main(int argc, char* argv[])
{
	std::string result;
	xM::db::xRedis rb;

	if (false == rb.Connect())
		return false;

	//rb.SetKey("mushroom", "1234");
	//rb.DelKey("mushroom");

	std::string svalue;
	time_t tvalue;

	for (size_t i = 0; i < 1000; i++)
	{
		rb.Set("key_" + std::to_string(i), std::to_string(i));
	}

	for (size_t i = 0; i < 1000; i++)
	{
		rb.Expire("key_" + std::to_string(i), xM::db::RTT_SECONDS, 60);
	}


	for (size_t i = 0; i < 1000; i++)
	{
		rb.Expire("key_" + std::to_string(i), xM::db::RTT_SECONDS, 60);
		rb.Get("key_" + std::to_string(i), svalue);
		rb.TTL("key_" + std::to_string(i), xM::db::RTT_SECONDS, tvalue);

		printf("%s:\t%s\t%ld\n", ("key_" + std::to_string(i)).c_str(), svalue.c_str(), tvalue);
	}


	getchar();
	return 0;
}
