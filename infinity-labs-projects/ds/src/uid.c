#include "uid.h"

const uuid_t BAD_UID = {0};

uuid_t GetUID(void)
{
	uuid_t uid = BAD_UID;
	time_t now = time(NULL);
	
	if (now == (time_t) -1)
	{
		return BAD_UID;
	}
	else
	{
		static size_t counter = 0;
		
		uid.__time_ind__ = now;
		uid.__counter__ = ++counter;
		uid.__process_id__ = getpid();
		
		return uid;
	}
}

int IsEqualUID(uuid_t uid1, uuid_t uid2)
{
	return ((uid1.__counter__ == uid2.__counter__) && (uid1.__process_id__ == uid2.__process_id__) && (uid1.__time_ind__ == uid2.__time_ind__));
}
