#ifndef __TINY_TOOLKIT__CRYPTO__HMAC_SHA512__H__
#define __TINY_TOOLKIT__CRYPTO__HMAC_SHA512__H__


/**
 *
 *  作者: hm
 *
 *  说明: hmac-sha512编码
 *
 */


#include "sha512.h"


namespace tinyToolkit
{
	class TINY_TOOLKIT_API HMAC_SHA512
	{
		typedef struct
		{
			uint8_t iPad[HMAC_PAD_128_SIZE]{ 0 };
			uint8_t oPad[HMAC_PAD_128_SIZE]{ 0 };
		}Context;

	public:
		/**
		 *
		 * 构造函数
		 *
		 */
		HMAC_SHA512();

		/**
		 *
		 * 重置
		 *
		 */
		void Reset();

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 待设置密钥
		 *
		 */
		void SetKey(const char * key);

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 待设置密钥
		 *
		 */
		void SetKey(const uint8_t * key);

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 待设置密钥
		 *
		 */
		void SetKey(const std::string & key);

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 待设置密钥
		 * @param length 待设置密钥长度
		 *
		 */
		void SetKey(const char * key, std::size_t length);

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 待设置密钥
		 * @param length 待设置密钥长度
		 *
		 */
		void SetKey(const uint8_t * key, std::size_t length);

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 待设置密钥
		 * @param length 待设置密钥长度
		 *
		 */
		void SetKey(const std::string & key, std::size_t length);

		/**
		 *
		 * 追加内容
		 *
		 * @param value 待追加内容
		 *
		 */
		void Append(const char * value);

		/**
		 *
		 * 追加内容
		 *
		 * @param value 待追加内容
		 *
		 */
		void Append(const uint8_t * value);

		/**
		 *
		 * 追加内容
		 *
		 * @param value 待追加内容
		 *
		 */
		void Append(const std::string & value);

		/**
		 *
		 * 追加内容
		 *
		 * @param value 待追加内容
		 * @param length 待追加内容长度
		 *
		 */
		void Append(const char * value, std::size_t length);

		/**
		 *
		 * 追加内容
		 *
		 * @param value 待追加内容
		 * @param length 待追加内容长度
		 *
		 */
		void Append(const uint8_t * value, std::size_t length);

		/**
		 *
		 * 追加内容
		 *
		 * @param value 待追加内容
		 * @param length 待追加内容长度
		 *
		 */
		void Append(const std::string & value, std::size_t length);

		/**
		 *
		 * 摘要
		 *
		 * @return 摘要
		 *
		 */
		const uint8_t * Digest();

		/**
		 *
		 * 摘要
		 *
		 * @return 摘要
		 *
		 */
		const std::string & Result();

	protected:
		/**
		 *
		 * 生成
		 *
		 */
		void Generate();

	protected:
		/**
		 *
		 * 初始化
		 *
		 * @param context 内容结构
		 *
		 */
		static void Initialization(Context & context);

	protected:
		bool _isComputed{ false };

		uint8_t _digest[SHA512_DIGEST_SIZE]{ 0 };

		SHA512 _sha512;

		Context _context{ };

		std::string _result{ };
	};
}


#endif // __TINY_TOOLKIT__CRYPTO__HMAC_SHA512__H__
