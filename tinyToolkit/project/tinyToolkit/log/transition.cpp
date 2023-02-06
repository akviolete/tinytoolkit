/**
 *
 *  作者: hm
 *
 *  说明: 日志类型处理
 *
 */


#include "transition.h"


namespace tinyToolkit
{
	/**
	 *
	 * 星期数值
	 *
	 * @param week 星期名称
	 *
	 * @return 星期数值
	 *
	 */
	int32_t LogWeek::Value(const char * week)
	{
		assert(week);

		static std::unordered_map<std::string, int32_t> WeekValue
		{
			{ "Sun", 0 },
			{ "Sunday", 0 },
			{ "Mon", 1 },
			{ "Monday", 1 },
			{ "Tue", 2 },
			{ "Tuesday", 2 },
			{ "Wed", 3 },
			{ "Wednesday", 3 },
			{ "Thu", 4 },
			{ "Thursday", 4 },
			{ "Fri", 5 },
			{ "Friday", 5 },
			{ "Sat", 6 },
			{ "Saturday", 6 },
		};

		return WeekValue[week];
	}

	/**
	 *
	 * 星期数值
	 *
	 * @param week 星期名称
	 *
	 * @return 星期数值
	 *
	 */
	int32_t LogWeek::Value(const std::string & week)
	{
		return Value(week.c_str());
	}

	/**
	 *
	 * 星期缩略名称
	 *
	 * @param week 星期数值
	 *
	 * @return 星期缩略名称
	 *
	 */
	std::string & LogWeek::Name(int32_t week)
	{
		static std::unordered_map<int32_t, std::string> WeekName
		{
			{ 0, "Sunday", },
			{ 1, "Monday", },
			{ 2, "Tuesday", },
			{ 3, "Wednesday", },
			{ 4, "Thursday", },
			{ 5, "Friday", },
			{ 6, "Saturday", },
		};

		return WeekName[week];
	}

	/**
	 *
	 * 星期名称
	 *
	 * @param week 星期数值
	 *
	 * @return 星期名称
	 *
	 */
	std::string & LogWeek::SimpleName(int32_t week)
	{
		static std::unordered_map<int32_t, std::string> WeekName
		{
			{ 0, "Sun", },
			{ 1, "Mon", },
			{ 2, "Tue", },
			{ 3, "Wed", },
			{ 4, "Thu", },
			{ 5, "Fri", },
			{ 6, "Sat", },
		};

		return WeekName[week];
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////


	/**
	 *
	 * 月份数值
	 *
	 * @param month 月份名称
	 *
	 * @return 月份数值
	 *
	 */
	int32_t LogMonth::Value(const char * month)
	{
		assert(month);

		static std::unordered_map<std::string, int32_t> MonthValue
		{
			{ "Jan", 0 },
			{ "January", 0 },
			{ "Feb", 1 },
			{ "February", 1 },
			{ "Mar", 2 },
			{ "March", 2 },
			{ "Apr", 3 },
			{ "April", 3 },
			{ "May", 4 },
			{ "May", 4 },
			{ "Jun", 5 },
			{ "June", 5 },
			{ "Jul", 6 },
			{ "July", 6 },
			{ "Aug", 7 },
			{ "August", 7 },
			{ "Sep", 8 },
			{ "September", 8 },
			{ "Oct", 9 },
			{ "October", 9 },
			{ "Nov", 10 },
			{ "November", 10 },
			{ "Dec", 11 },
			{ "December", 11 },
		};

		return MonthValue[month];
	}

	/**
	 *
	 * 月份数值
	 *
	 * @param week 月份名称
	 *
	 * @return 月份数值
	 *
	 */
	int32_t LogMonth::Value(const std::string & month)
	{
		return Value(month.c_str());
	}

	/**
	 *
	 * 月份缩略名称
	 *
	 * @param month 月份数值
	 *
	 * @return 月份缩略名称
	 *
	 */
	std::string & LogMonth::Name(int32_t month)
	{
		static std::unordered_map<int32_t, std::string> MonthName
		{
			{  0, "January", },
			{  1, "February", },
			{  2, "March", },
			{  3, "April", },
			{  4, "May", },
			{  5, "June", },
			{  6, "July", },
			{  7, "August", },
			{  8, "September", },
			{  9, "October", },
			{ 10, "November", },
			{ 11, "December", },
		};

		return MonthName[month];
	}

	/**
	 *
	 * 月份名称
	 *
	 * @param month 月份数值
	 *
	 * @return 月份名称
	 *
	 */
	std::string & LogMonth::SimpleName(int32_t month)
	{
		static std::unordered_map<int32_t, std::string> MonthName
		{
			{  0, "Jan", },
			{  1, "Feb", },
			{  2, "Mar", },
			{  3, "Apr", },
			{  4, "May", },
			{  5, "Jun", },
			{  6, "Jul", },
			{  7, "Aug", },
			{  8, "Sep", },
			{  9, "Oct", },
			{ 10, "Nov", },
			{ 11, "Dec", },
		};

		return MonthName[month];
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////


	/**
	 *
	 * 优先级名称
	 *
	 * @param priority 优先级数值
	 *
	 * @return 优先级名称
	 *
	 */
	std::string & LogPriority::Name(LOG_PRIORITY_TYPE priority)
	{
		static std::unordered_map<LOG_PRIORITY_TYPE, std::string> PriorityName
		{
			{ LOG_PRIORITY_TYPE::DEBUGS,   "DEBUG" },
			{ LOG_PRIORITY_TYPE::INFO,     "INFO" },
			{ LOG_PRIORITY_TYPE::NOTICE,   "NOTICE" },
			{ LOG_PRIORITY_TYPE::WARNING,  "WARNING" },
			{ LOG_PRIORITY_TYPE::ERRORS,   "ERROR" },
			{ LOG_PRIORITY_TYPE::CRITICAL, "CRITICAL" },
			{ LOG_PRIORITY_TYPE::ALERT,    "ALERT" },
			{ LOG_PRIORITY_TYPE::FATAL,    "FATAL" },
			{ LOG_PRIORITY_TYPE::EMERG,    "EMERG" },
		};

		return PriorityName[priority];
	}

	/**
	 *
	 * 优先级数值
	 *
	 * @param priority 优先级名称
	 *
	 * @return 优先级数值
	 *
	 */
	LOG_PRIORITY_TYPE LogPriority::Value(const char * priority)
	{
		assert(priority);

		static std::unordered_map<std::string, LOG_PRIORITY_TYPE> PriorityValue
		{
			{ "DEBUG", LOG_PRIORITY_TYPE::DEBUGS },
			{ "INFO", LOG_PRIORITY_TYPE::INFO },
			{ "NOTICE", LOG_PRIORITY_TYPE::NOTICE },
			{ "WARNING", LOG_PRIORITY_TYPE::WARNING },
			{ "ERROR", LOG_PRIORITY_TYPE::ERRORS },
			{ "CRITICAL", LOG_PRIORITY_TYPE::CRITICAL },
			{ "ALERT", LOG_PRIORITY_TYPE::ALERT },
			{ "FATAL", LOG_PRIORITY_TYPE::FATAL },
			{ "EMERG", LOG_PRIORITY_TYPE::EMERG },
		};

		return PriorityValue[priority];
	}

	/**
	 *
	 * 优先级数值
	 *
	 * @param priority 优先级名称
	 *
	 * @return 优先级数值
	 *
	 */
	LOG_PRIORITY_TYPE LogPriority::Value(const std::string & priority)
	{
		return Value(priority.c_str());
	}
}
