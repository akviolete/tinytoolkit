/**
 *
 *  作者: hm
 *
 *  说明: 字符串处理
 *
 */


#include "string.h"


namespace tinyToolkit
{
	/**
	 *
	 * 去除首尾字符
	 *
	 * @param value 待处理字符串
	 * @param group 处理字符集
	 *
	 */
	void String::Trim(std::string & value, const char * group)
	{
		assert(group);

		std::string::size_type end   = value.find_last_not_of(group);
		std::string::size_type start = value.find_first_not_of(group);

		value = (start == std::string::npos) ? "" : value.substr(start, 1 + end - start);
	}

	/**
	 *
	 * 去除首尾字符
	 *
	 * @param value 待处理字符串
	 * @param group 处理字符集
	 *
	 * @return 处理后字符串
	 *
	 */
	std::string String::Trim(const std::string & value, const char * group)
	{
		assert(group);

		std::string::size_type end   = value.find_last_not_of(group);
		std::string::size_type start = value.find_first_not_of(group);

		return (start == std::string::npos) ? "" : value.substr(start, 1 + end - start);
	}

	/**
	 *
	 * 转换小写
	 *
	 * @param value 待处理字符串
	 * @param index 偏移位置
	 *
	 */
	void String::Lower(std::string & value, std::size_t index)
	{
		std::transform(value.begin() + index, value.end(), value.begin() + index, ::tolower);
	}

	/**
	 *
	 * 转换小写
	 *
	 * @param value 待处理字符串
	 * @param index 偏移位置
	 *
	 * @return 处理后字符串
	 *
	 */
	std::string String::Lower(const std::string & value, std::size_t index)
	{
		std::string str = value;

		Lower(str, index);

		return str;
	}

	/**
	 *
	 * 转换大写
	 *
	 * @param value 待处理字符串
	 * @param index 偏移位置
	 *
	 */
	void String::Upper(std::string & value, std::size_t index)
	{
		std::transform(value.begin() + index, value.end(), value.begin() + index, ::toupper);
	}

	/**
	 *
	 * 转换大写
	 *
	 * @param value 待处理字符串
	 * @param index 偏移位置
	 *
	 * @return 处理后字符串
	 *
	 */
	std::string String::Upper(const std::string & value, std::size_t index)
	{
		std::string str = value;

		Upper(str, index);

		return str;
	}

	/**
	 *
	 * 删除字符串指定字符
	 *
	 * @param value 待查找的字符串
	 * @param key 被查找的字符串
	 * @param index 偏移位置
	 *
	 */
	void String::Erase(std::string & value, char key, std::size_t index)
	{
		while ((index = value.find(key, index)) != std::string::npos)
		{
			value.erase(index, 1);
		}
	}

	/**
	 *
	 * 删除字符串指定字符
	 *
	 * @param value 待查找的字符串
	 * @param key 被查找的字符串
	 * @param index 偏移位置
	 *
	 * @return 处理后字符串
	 *
	 */
	std::string String::Erase(const std::string & value, char key, std::size_t index)
	{
		std::string str = value;

		Erase(str, key, index);

		return str;
	}

	/**
	 *
	 * 删除字符串指定字符
	 *
	 * @param value 待查找的字符串
	 * @param key 被查找的字符串
	 * @param index 偏移位置
	 *
	 */
	void String::Erase(std::string & value, const std::string & key, std::size_t index)
	{
		while ((index = value.find(key, index)) != std::string::npos)
		{
			value.erase(index, key.size());
		}
	}

	/**
	 *
	 * 删除字符串指定字符
	 *
	 * @param value 待查找的字符串
	 * @param key 被查找的字符串
	 * @param index 偏移位置
	 *
	 * @return 处理后字符串
	 *
	 */
	std::string String::Erase(const std::string & value, const std::string & key, std::size_t index)
	{
		std::string str = value;

		Erase(str, key, index);

		return str;
	}

	/**
	 *
	 * 删除字符串指定字符
	 *
	 * @param value 待处理字符串
	 * @param function 判断函数
	 * @param index 偏移位置
	 *
	 */
	void String::Erase(std::string & value, const std::function<bool(char)> & function, std::size_t index)
	{
		for (auto iter = value.begin() + index; iter != value.end();)
		{
			if (function(*iter))
			{
				value.erase(iter, iter + 1);
			}
			else
			{
				++iter;
			}
		}
	}

	/**
	 *
	 * 删除字符串指定字符
	 *
	 * @param value 待处理字符串
	 * @param function 判断函数
	 * @param index 偏移位置
	 *
	 * @return 处理后字符串
	 *
	 */
	std::string String::Erase(const std::string & value, const std::function<bool(char)> & function, std::size_t index)
	{
		std::string str = value;

		Erase(str, function, index);

		return str;
	}

	/**
	 *
	 * 字符串替换字符
	 *
	 * @param value 待处理字符串
	 * @param src 被替换字符串
	 * @param dst 待替换字符串
	 * @param index 偏移位置
	 *
	 */
	void String::Replace(std::string & value, const std::string & src, const std::string & dst, std::size_t index)
	{
		for (std::size_t pos = index; pos != std::string::npos; pos += dst.size())
		{
			if ((pos = value.find(src, pos)) == std::string::npos)
			{
				break;
			}
			else
			{
				value.replace(pos, src.size(), dst);
			}
		}
	}

	/**
	 *
	 * 字符串替换字符
	 *
	 * @param value 待处理字符串
	 * @param src 被替换字符串
	 * @param dst 待替换字符串
	 * @param index 偏移位置
	 *
	 * @return 处理后字符串
	 *
	 */
	std::string String::Replace(const std::string & value, const std::string & src, const std::string & dst, std::size_t index)
	{
		std::string str = value;

		Replace(str, src, dst, index);

		return str;
	}

	/**
	 *
	 * 字符串替换字符
	 *
	 * @param value 待处理字符串
	 * @param src 被替换字符串
	 * @param dst 待替换字符串
	 * @param index 偏移位置
	 *
	 */
	void String::ReplaceAll(std::string & value, const std::string & src, const std::string & dst, std::size_t index)
	{
		while (true)
		{
			std::size_t pos = value.find(src, index);

			if (pos == std::string::npos)
			{
				break;
			}
			else
			{
				value.replace(pos, src.size(), dst);
			}
		}
	}

	/**
	 *
	 * 字符串替换字符
	 *
	 * @param value 待处理字符串
	 * @param src 被替换字符串
	 * @param dst 待替换字符串
	 * @param index 偏移位置
	 *
	 * @return 处理后字符串
	 *
	 */
	std::string String::ReplaceAll(const std::string & value, const std::string & src, const std::string & dst, std::size_t index)
	{
		std::string str = value;

		ReplaceAll(str, src, dst, index);

		return str;
	}

	/**
	 *
	 * 是否包含被查找的字符
	 *
	 * @param value 待查找字符串
	 * @param infix 被查找字符
	 * @param index 偏移位置
	 *
	 * @return 查找结果
	 *
	 */
	bool String::With(const char * value, char infix, std::size_t index)
	{
		assert(value);

		return std::strchr(value + index, infix) != nullptr;
	}

	/**
	 *
	 * 是否包含被查找的字符串
	 *
	 * @param value 待查找字符串
	 * @param infix 被查找字符串
	 * @param index 偏移位置
	 *
	 * @return 查找结果
	 *
	 */
	bool String::With(const char * value, const char * infix, std::size_t index)
	{
		assert(value && infix);

		return strstr(value + index, infix) != nullptr;
	}

	/**
	 *
	 * 是否包含被查找的字符
	 *
	 * @param value 待查找字符串
	 * @param infix 被查找字符
	 * @param index 偏移位置
	 *
	 * @return 查找结果
	 *
	 */
	bool String::With(const std::string & value, char infix, std::size_t index)
	{
		return value.find(infix, index) != std::string::npos;
	}

	/**
	 *
	 * 是否包含被查找的字符串
	 *
	 * @param value 待查找字符串
	 * @param infix 被查找字符串
	 * @param index 偏移位置
	 *
	 * @return 查找结果
	 *
	 */
	bool String::With(const std::string & value, const char * infix, std::size_t index)
	{
		assert(infix);

		return value.find(infix, index) != std::string::npos;
	}

	/**
	 *
	 * 是否包含被查找的字符串
	 *
	 * @param value 待查找字符串
	 * @param infix 被查找字符串
	 * @param index 偏移位置
	 *
	 * @return 查找结果
	 *
	 */
	bool String::With(const std::string & value, const std::string & infix, std::size_t index)
	{
		return value.find(infix, index) != std::string::npos;
	}

	/**
	 *
	 * 是否以字符串结尾
	 *
	 * @param value 待查找字符串
	 * @param prefix 被查找字符串
	 *
	 * @return 查找结果
	 *
	 */
	bool String::EndWith(const std::string & value, const std::string & suffix)
	{
		return value.size() >= suffix.size() && std::equal(suffix.rbegin(), suffix.rend(), value.rbegin());
	}

	/**
	 *
	 * 是否字符串开头
	 *
	 * @param value 待查找字符串
	 * @param prefix 被查找字符串
	 *
	 * @return 查找结果
	 *
	 */
	bool String::StartWith(const std::string & value, const std::string & prefix)
	{
		return value.size() >= prefix.size() && std::equal(prefix.begin(), prefix.end(), value.begin());
	}

	/**
	 *
	 * 按字符串拆分
	 *
	 * @param value 待查找字符串
	 * @param key 被查找字符串
	 * @param container 结果容器
	 * @param keepEmpty 是否保留空串
	 *
	 * @return 拆分个数
	 *
	 */
	std::size_t String::Split(const std::string & value, const std::string & key, std::vector<std::string> & container, bool keepEmpty)
	{
		if (key.empty())
		{
			container.push_back(value);
		}
		else
		{
			std::string::const_iterator beg = value.begin();
			std::string::const_iterator end;

			while (true)
			{
				end = std::search(beg, value.end(), key.begin(), key.end());

				if (beg != end)
				{
					std::string str(beg, end);

					Trim(str, "\r\n");

					if (keepEmpty || !str.empty())
					{
						container.push_back(str);
					}

					if (end == value.end())
					{
						break;
					}
				}
				else if (beg == value.end())
				{
					break;
				}

				beg = end + key.size();
			}
		}

		return container.size();
	}

	/**
	 *
	 * 按字符串拆分
	 *
	 * @param value 待查找字符串
	 * @param key 被查找字符串
	 * @param keepEmpty 是否保留空串
	 *
	 * @return 结果容器
	 *
	 */
	std::vector<std::string> String::Split(const std::string & value, const std::string & key, bool keepEmpty)
	{
		std::vector<std::string> container;

		Split(value, key, container, keepEmpty);

		return container;
	}

	/**
	 *
	 * 按行拆分
	 *
	 * @param value 待查找字符串
	 * @param container 结果容器
	 * @param keepEnter 是否保留换行符
	 *
	 * @return 拆分的个数
	 *
	 */
	std::size_t String::SplitLines(const std::string & value, std::vector<std::string> & container, bool keepEnter)
	{
		std::size_t i = 0;
		std::size_t j = 0;

		while (i < value.size())
		{
			while (i < value.size() && value[i] != '\r' && value[i] != '\n' && value[i] != '\0')
			{
				++i;
			}

			std::size_t eol = i;

			if (i < value.size())
			{
				i += (value[i] == '\r' && i + 1 < value.size() && value[i + 1] == '\n') ? 2 : 1;

				if (keepEnter)
				{
					eol = i;
				}
			}

			container.push_back(value.substr(j, eol - j));

			j = i;
		}

		return container.size();
	}

	/**
	 *
	 * 按行拆分
	 *
	 * @param value 待查找字符串
	 * @param keepEmpty 是否保留换行符
	 *
	 * @return 结果容器
	 *
	 */
	std::vector<std::string> String::SplitLines(const std::string & value, bool keepEnter)
	{
		std::vector<std::string> container;

		SplitLines(value, container, keepEnter);

		return container;
	}

	/**
	 *
	 * 过滤注释
	 *
	 * @param value 待过滤数据
	 *
	 * @return 过滤后数据
	 *
	 */
	std::string String::FilterNote(const std::string & value)
	{
		enum class State : uint8_t
		{
			NORMAL,                 /// 正常代码
			SLASH,                  /// 斜杠
			NOTE_MULTI_LINE,        /// 多行注释
			NOTE_MULTI_LINE_STAR,   /// 多行注释遇到*
			NOTE_SINGLE_LINE,       /// 单行注释
			BACKSLASH,              /// 折行注释反斜线
			CHARACTER,              /// 字符
			ESCAPE_CHARACTER,       /// 字符中的转义字符
			STRING,                 /// 字符串
			ESCAPE_STRING           /// 字符串中的转义字符
		};

		std::string str{ };

		State state = State::NORMAL;

		for (const char c : value)
		{
			switch (state)
			{
				case State::NORMAL:  /// 正常代码
				{
					if (c == '/')
					{
						state = State::SLASH;
					}
					else
					{
						str.push_back(c);

						if (c == '\'')
						{
							state = State::CHARACTER;
						}
						else if (c == '\"')
						{
							state = State::STRING;
						}
						else
						{
							state = State::NORMAL;  /// 保持当前状态
						}
					}

					break;
				}

				case State::SLASH:  /// 斜杠
				{
					if (c == '*')
					{
						state = State::NOTE_MULTI_LINE;
					}
					else if (c == '/')
					{
						state = State::NOTE_SINGLE_LINE;
					}
					else
					{
						str.push_back('/');
						str.push_back(c);

						state = State::NORMAL;
					}

					break;
				}

				case State::NOTE_MULTI_LINE:  /// 多行注释
				{
					if (c == '*')
					{
						state = State::NOTE_MULTI_LINE_STAR;
					}
					else
					{
						state = State::NOTE_MULTI_LINE;  /// 保持当前状态
					}

					break;
				}

				case State::NOTE_MULTI_LINE_STAR:  /// 多行注释遇到*
				{
					if (c == '/')
					{
						state = State::NORMAL;  /// 注释结束
					}
					else if (c == '*')
					{
						state = State::NOTE_MULTI_LINE_STAR;  /// 保持当前状态
					}
					else
					{
						state = State::NOTE_MULTI_LINE;
					}

					break;
				}

				case State::NOTE_SINGLE_LINE:  /// 单行注释
				{
					if (c == '\\')
					{
						state = State::BACKSLASH;
					}
					else if (c == '\r' || c == '\n')
					{
						str.push_back(c);

						state = State::NORMAL;  /// 注释结束
					}
					else
					{
						state = State::NOTE_SINGLE_LINE;  /// 保持当前状态
					}

					break;
				}

				case State::BACKSLASH:  /// 折行注释反斜线
				{
					if (c == '\\' || c == '\r' || c == '\n')
					{
						state = State::BACKSLASH;  /// 保持当前状态
					}
					else
					{
						state = State::NOTE_SINGLE_LINE;
					}

					break;
				}

				case State::CHARACTER:  /// 字符
				{
					str.push_back(c);

					if (c == '\\')
					{
						state = State::ESCAPE_CHARACTER;
					}
					else if (c == '\'')
					{
						state = State::NORMAL;
					}
					else
					{
						state = State::CHARACTER;  /// 保持当前状态
					}

					break;
				}

				case State::ESCAPE_CHARACTER:  /// 字符中的转义字符
				{
					str.push_back(c);

					state = State::CHARACTER;

					break;
				}

				case State::STRING:  /// 字符串
				{
					str.push_back(c);

					if (c == '\\')
					{
						state = State::ESCAPE_STRING;
					}
					else if (c == '\"')
					{
						state = State::NORMAL;
					}
					else
					{
						state = State::STRING;  /// 保持当前状态
					}

					break;
				}

				case State::ESCAPE_STRING:  /// 字符串中的转义字符
				{
					str.push_back(c);

					state = State::STRING;

					break;
				}

				default:
				{
					break;
				}
			}
		}

		return str;
	}

	/**
	 *
	 * 转换16进制字符串
	 *
	 * @param value 待转换字符串
	 * @param reverse 是否反向转换
	 *
	 * @return 转换后字符串
	 *
	 */
	std::string String::AsHexString(const char * value, bool reverse)
	{
		assert(value);

		return AsHexString(value, strlen(value), reverse);
	}

	/**
	 *
	 * 转换16进制字符串
	 *
	 * @param value 待转换字符串
	 * @param reverse 是否反向转换
	 *
	 * @return 转换后字符串
	 *
	 */
	std::string String::AsHexString(const uint8_t * value, bool reverse)
	{
		assert(value);

		return AsHexString(value, strlen(reinterpret_cast<const char *>(value)), reverse);
	}

	/**
	 *
	 * 转换16进制字符串
	 *
	 * @param value 待转换字符串
	 * @param reverse 是否反向转换
	 *
	 * @return 转换后字符串
	 *
	 */
	std::string String::AsHexString(const std::string & value, bool reverse)
	{
		return AsHexString(value, value.size(), reverse);
	}

	/**
	 *
	 * 转换16进制字符串
	 *
	 * @param value 待转换字符串
	 * @param size 转换长度
	 * @param reverse 是否反向转换
	 *
	 * @return 转换后字符串
	 *
	 */
	std::string String::AsHexString(const char * value, std::size_t size, bool reverse)
	{
		assert(value);

		return AsHexString(reinterpret_cast<const uint8_t *>(value), size, reverse);
	}

	/**
	 *
	 * 转换16进制字符串
	 *
	 * @param value 待转换字符串
	 * @param size 转换长度
	 * @param reverse 是否反向转换
	 *
	 * @return 转换后字符串
	 *
	 */
	std::string String::AsHexString(const uint8_t * value, std::size_t size, bool reverse)
	{
		assert(value);

		int64_t op   = reverse ? -1 : 1;
		int64_t init = reverse ? static_cast<int64_t>(size) - 1 : 0;
		int64_t end  = reverse ? -1 : static_cast<int64_t>(size);

		std::ostringstream stream{ };

		for (int64_t i = init; i != end; i += op)
		{
			stream << fmt::format("{:02x}", value[i]);
		}

		return stream.str();
	}

	/**
	 *
	 * 转换16进制字符串
	 *
	 * @param value 待转换字符串
	 * @param size 转换的长度
	 * @param reverse 是否反向转换
	 *
	 * @return 转换后字符串
	 *
	 */
	std::string String::AsHexString(const std::string & value, std::size_t size, bool reverse)
	{
		return AsHexString(value.c_str(), size, reverse);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////


	/**
	 *
	 * 转换字符
	 *
	 * @param value 待转换数据
	 *
	 * @return 转换后字符
	 *
	 */
	uint8_t HexString::AsByte(const char * value)
	{
		return static_cast<uint8_t>(strtol(value, nullptr, 16));
	}

	/**
	 *
	 * 转换字符
	 *
	 * @param value 待转换字符串
	 *
	 * @return 转换后字符
	 *
	 */
	uint8_t HexString::AsByte(const std::string & value)
	{
		return AsByte(value.c_str());
	}

	/**
	 *
	 * 转换字符串
	 *
	 * @param value 待转换字符串
	 * @param reverse 是否反向转换
	 *
	 * @return 转换后字符串
	 *
	 */
	std::string HexString::AsString(const char * value, bool reverse)
	{
		assert(value);

		return AsString(value, strlen(value), reverse);
	}

	/**
	 *
	 * 转换字符串
	 *
	 * @param value 待转换字符串
	 * @param reverse 是否反向转换
	 *
	 * @return 转换后字符串
	 *
	 */
	std::string HexString::AsString(const std::string & value, bool reverse)
	{
		return AsString(value, value.size(), reverse);
	}

	/**
	 *
	 * 转换字符串
	 *
	 * @param value 待转换字符串
	 * @param size 字符串长度
	 * @param reverse 是否反向转换
	 *
	 * @return 转换后字符串
	 *
	 */
	std::string HexString::AsString(const char * value, std::size_t size, bool reverse)
	{
		int64_t op   = reverse ? -2 : 2;
		int64_t init = reverse ? static_cast<int64_t>(size) - 2 : 0;
		int64_t end  = reverse ? -2 : static_cast<int64_t>(size);

		std::string content = { };

		for (int64_t i = init; i != end; i += op)
		{
			char buffer[3] = { value[i], value[i + 1], '\0' };

			content.push_back(AsByte(buffer));
		}

		return content;
	}

	/**
	 *
	 * 转换字符串
	 *
	 * @param value 待转换字符串
	 * @param size 字符串长度
	 * @param reverse 是否反向转换
	 *
	 * @return 转换后字符串
	 *
	 */
	std::string HexString::AsString(const std::string & value, std::size_t size, bool reverse)
	{
		return AsString(value.c_str(), size, reverse);
	}
}
