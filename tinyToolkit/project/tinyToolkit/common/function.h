#ifndef __TINY_TOOLKIT__COMMON__FUNCTION__H__
#define __TINY_TOOLKIT__COMMON__FUNCTION__H__


/**
 *
 *  作者: hm
 *
 *  说明: 函数定义
 *
 */


#include "platform.h"


#define INHERITANCE_DECLARE(child, parent)		\
												\
class TINY_TOOLKIT_API child : public parent	\
{												\
public:											\
	using parent::parent;						\
}


#define TINY_TOOLKIT_YIELD()						std::this_thread::yield()


#define TINY_TOOLKIT_SLEEP_H(n)						std::this_thread::sleep_for(std::chrono::hours(n))
#define TINY_TOOLKIT_SLEEP_M(n)						std::this_thread::sleep_for(std::chrono::minutes(n))
#define TINY_TOOLKIT_SLEEP_S(n)						std::this_thread::sleep_for(std::chrono::seconds(n))
#define TINY_TOOLKIT_SLEEP_NS(n)					std::this_thread::sleep_for(std::chrono::nanoseconds(n))
#define TINY_TOOLKIT_SLEEP_MS(n)					std::this_thread::sleep_for(std::chrono::milliseconds(n))
#define TINY_TOOLKIT_SLEEP_US(n)					std::this_thread::sleep_for(std::chrono::microseconds(n))


#define TINY_TOOLKIT_JOIN_STR(prefix, suffix)		prefix##suffix
#define TINY_TOOLKIT_JOIN_VALUE(prefix, suffix)		TINY_TOOLKIT_JOIN_STR(prefix, suffix)


#endif // __TINY_TOOLKIT__COMMON__FUNCTION__H__
