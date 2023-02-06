/**
 *
 *  作者: hm
 *
 *  说明: base64编码
 *
 */


#include "base64.h"


namespace tinyToolkit
{
	/**
	 *
	 * 编码
	 *
	 * @param value 待编码内容
	 *
	 * @return 编码后内容
	 *
	 */
	std::string Base64::Encode(const char * value)
	{
		assert(value);

		return Encode(value, strlen(value));
	}

	/**
	 *
	 * 编码
	 *
	 * @param value 待编码内容
	 *
	 * @return 编码后内容
	 *
	 */
	std::string Base64::Encode(const uint8_t * value)
	{
		assert(value);

		return Encode(value, strlen(reinterpret_cast<const char *>(value)));
	}

	/**
	 *
	 * 编码
	 *
	 * @param value 待编码内容
	 *
	 * @return 编码后内容
	 *
	 */
	std::string Base64::Encode(const std::string & value)
	{
		return Encode(value, value.size());
	}

	/**
	 *
	 * 编码
	 *
	 * @param value 待编码内容
	 * @param length 待编码内容长度
	 *
	 * @return 编码后内容
	 *
	 */
	std::string Base64::Encode(const char * value, std::size_t length)
	{
		assert(value);

		return Encode(reinterpret_cast<const uint8_t *>(value), length);
	}

	/**
	 *
	 * 编码
	 *
	 * @param value 待编码内容
	 * @param length 待编码内容长度
	 *
	 * @return 编码后内容
	 *
	 */
	std::string Base64::Encode(const uint8_t * value, std::size_t length)
	{
		assert(value);

		static char EncodeTable[64] =
		{
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
			'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
			'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
			'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
			'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
			'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
			'w', 'x', 'y', 'z', '0', '1', '2', '3',
			'4', '5', '6', '7', '8', '9', '+', '/'
		};

		std::string res;

		while (length > 2)
		{
			res += EncodeTable[                            value[0] >> 2 ];
			res += EncodeTable[((value[0] & 0x03) << 4) + (value[1] >> 4)];
			res += EncodeTable[((value[1] & 0x0f) << 2) + (value[2] >> 6)];
			res += EncodeTable[  value[2] & 0x3f];

			value  += 3;
			length -= 3;
		}

		if (length > 0)
		{
			res += EncodeTable[value[0] >> 2];

			if (length % 3 == 1)
			{
				res += EncodeTable[(value[0] & 0x03) << 4];
				res += "==";
			}
			else if (length % 3 == 2)
			{
				res += EncodeTable[((value[0] & 0x03) << 4) + (value[1] >> 4)];
				res += EncodeTable[ (value[1] & 0x0f) << 2];
				res += "=";
			}
		}

		return res;
	}

	/**
	 *
	 * 编码
	 *
	 * @param value 待编码内容
	 * @param length 待编码内容长度
	 *
	 * @return 编码后内容
	 *
	 */
	std::string Base64::Encode(const std::string & value, std::size_t length)
	{
		return Encode(value.c_str(), length);
	}

	/**
	 *
	 * 解码
	 *
	 * @param value 待解码内容
	 *
	 * @return 解码后内容
	 *
	 */
	std::string Base64::Decode(const char * value)
	{
		assert(value);

		return Decode(value, strlen(value));
	}

	/**
	 *
	 * 解码
	 *
	 * @param value 待解码内容
	 *
	 * @return 解码后内容
	 *
	 */
	std::string Base64::Decode(const uint8_t * value)
	{
		assert(value);

		return Decode(value, strlen(reinterpret_cast<const char *>(value)));
	}

	/**
	 *
	 * 解码
	 *
	 * @param value 待解码内容
	 *
	 * @return 解码后内容
	 *
	 */
	std::string Base64::Decode(const std::string & value)
	{
		return Decode(value, value.size());
	}

	/**
	 *
	 * 解码
	 *
	 * @param value 待解码内容
	 * @param length 待解码内容长度
	 *
	 * @return 解码后内容
	 *
	 */
	std::string Base64::Decode(const char * value, std::size_t length)
	{
		assert(value);

		return Decode(reinterpret_cast<const uint8_t *>(value), length);
	}

	/**
	 *
	 * 解码
	 *
	 * @param value 待解码内容
	 * @param length 待解码内容长度
	 *
	 * @return 解码后内容
	 *
	 */
	std::string Base64::Decode(const uint8_t * value, std::size_t length)
	{
		assert(value);

		static char DecodeTable[256] =
		{
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
			52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1,  0, -1, -1,
			-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
			15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
			-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
			41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
		};

		char ch;

		int32_t bin = 0;

		std::size_t i = 0;
		std::size_t pos = 0;

		std::string res;

		while ((ch = *value++) != '\0' && i <= length)
		{
			pos = i % 4;

			if (ch == '=')
			{
				/**
				 *
				 * 先说明一个概念 : 在解码时, 4个字符为一组进行一轮字符匹配.
				 *
				 * 两个条件 :
				 * 1、如果某一轮匹配的第二个是 "=" 且第三个字符不是 "=" , 说明这个带解析字符串不合法, 直接返回空
				 * 2、如果当前 "=" 不是第二个字符, 且后面的字符只包含空白符, 则说明这个这个条件合法, 可以继续.
				 *
				 */
				if (*value != '=' && pos == 1)
				{
					throw std::runtime_error("Decrypt data is invalid");
				}

				continue;
			}

			ch = DecodeTable[static_cast<uint8_t>(ch)];

			if (ch < 0)
			{
				continue;  /// 空格或者其它分隔符属于不合法的字符, 直接跳过
			}

			switch (pos)
			{
				case 0:
				{
					bin = ch << 2;

					break;
				}

				case 1:
				{
					bin |= ch >> 4;

					res.push_back(static_cast<char>(bin));

					bin = (ch & 0x0f) << 4;

					break;
				}

				case 2:
				{
					bin |= ch >> 2;

					res.push_back(static_cast<char>(bin));

					bin = (ch & 0x03) << 6;

					break;
				}

				case 3:
				{
					bin |= ch;

					res.push_back(static_cast<char>(bin));

					break;
				}

				default:
				{
					break;
				}
			}

			++i;
		}

		return res;
	}

	/**
	 *
	 * 解码
	 *
	 * @param value 待解码内容
	 * @param length 待解码内容长度
	 *
	 * @return 解码后内容
	 *
	 */
	std::string Base64::Decode(const std::string & value, std::size_t length)
	{
		return Decode(value.c_str(), length);
	}
}
