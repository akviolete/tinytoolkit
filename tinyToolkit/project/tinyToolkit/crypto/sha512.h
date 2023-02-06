#ifndef __TINY_TOOLKIT__CRYPTO__SHA512__H__
#define __TINY_TOOLKIT__CRYPTO__SHA512__H__


/**
 *
 *  作者: hm
 *
 *  说明: sha512编码
 *
 */


#include "../common/common.h"


namespace tinyToolkit
{
	class TINY_TOOLKIT_API SHA512
	{
		typedef struct Context
		{
			uint8_t block[2 * SHA512_BLOCK_SIZE]{ 0 };

			uint64_t hash[8]{ 0 };

			uint32_t totalLength{ 0 };
			uint32_t blockLength{ 0 };
		}Context;

	public:
		/**
		 *
		 * 构造函数
		 *
		 */
		SHA512();

		/**
		 *
		 * 重置
		 *
		 */
		void Reset();

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
		 * 完成
		 *
		 * @param context 内容结构
		 * @param digest 存储摘要
		 *
		 */
		static void Final(Context & context, uint8_t * digest);

		/**
		 *
		 * 更新
		 *
		 * @param context 内容结构
		 * @param value 待更新内容
		 * @param length 待更新内容长度
		 *
		 */
		static void Update(Context & context, const uint8_t * value, uint32_t length);

		/**
		 *
		 * 转换
		 *
		 * @param context 内容结构
		 * @param block 待转换块
		 * @param number 待转换块个数
		 *
		 */
		static void Transform(Context & context, const uint8_t * block, uint32_t number);

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

		Context _context{ };

		std::string _result{ };
	};
}


#endif // __TINY_TOOLKIT__CRYPTO__SHA512__H__
