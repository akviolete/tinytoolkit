/**
 *
 *  作者: hm
 *
 *  说明: sha512编码
 *
 */


#include "sha512.h"

#include "../utilities/string.h"
#include "../utilities/operator.h"


namespace tinyToolkit
{
	/**
	 *
	 * 构造函数
	 *
	 */
	SHA512::SHA512()
	{
		Initialization(_context);
	}

	/**
	 *
	 * 重置
	 *
	 */
	void SHA512::Reset()
	{
		_isComputed = false;

		memset(_digest, 0, sizeof(_digest));
		memset(reinterpret_cast<void *>(&_context), 0, sizeof(_context));

		Operator::Clear(_result);

		Initialization(_context);
	}

	/**
	 *
	 * 追加内容
	 *
	 * @param value 待追加内容
	 *
	 */
	void SHA512::Append(const char * value)
	{
		if (value == nullptr)
		{
			return;
		}

		Append(value, strlen(value));
	}

	/**
	 *
	 * 追加内容
	 *
	 * @param value 待追加内容
	 *
	 */
	void SHA512::Append(const uint8_t * value)
	{
		if (value == nullptr)
		{
			return;
		}

		Append(value, strlen(reinterpret_cast<const char *>(value)));
	}

	/**
	 *
	 * 追加内容
	 *
	 * @param value 待追加内容
	 *
	 */
	void SHA512::Append(const std::string & value)
	{
		Append(value, value.size());
	}

	/**
	 *
	 * 追加内容
	 *
	 * @param value 待追加内容
	 * @param length 待追加内容长度
	 *
	 */
	void SHA512::Append(const char * value, std::size_t length)
	{
		if (value == nullptr || length == 0)
		{
			return;
		}

		Append(reinterpret_cast<const uint8_t *>(value), length);
	}

	/**
	 *
	 * 追加内容
	 *
	 * @param value 待追加内容
	 * @param length 待追加内容长度
	 *
	 */
	void SHA512::Append(const uint8_t * value, std::size_t length)
	{
		if (value == nullptr || length == 0)
		{
			return;
		}

		Update(_context, value, static_cast<uint32_t>(length));

		_isComputed = false;
	}

	/**
	 *
	 * 追加内容
	 *
	 * @param value 待追加内容
	 * @param length 待追加内容长度
	 *
	 */
	void SHA512::Append(const std::string & value, std::size_t length)
	{
		Append(value.c_str(), length);
	}

	/**
	 *
	 * 摘要
	 *
	 * @return 摘要
	 *
	 */
	const uint8_t * SHA512::Digest()
	{
		Generate();

		return _digest;
	}

	/**
	 *
	 * 摘要
	 *
	 * @return 摘要
	 *
	 */
	const std::string & SHA512::Result()
	{
		Generate();

		return _result;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////


	/**
	 *
	 * 生成
	 *
	 */
	void SHA512::Generate()
	{
		if (!_isComputed)
		{
			_isComputed = true;

			Context context{ };

			memcpy(&context, &_context, sizeof(context));

			Final(context, _digest);

			_result.assign(String::AsHexString(_digest, sizeof(_digest), false));
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////


	/**
	 *
	 * 完成
	 *
	 * @param context 内容结构
	 * @param digest 存储摘要
	 *
	 */
	void SHA512::Final(Context & context, uint8_t * digest)
	{
		#define UNPACK32(x, str)                      \
		{                                             \
			*((str) + 3) = (uint8_t) ((x)      );     \
			*((str) + 2) = (uint8_t) ((x) >>  8);     \
			*((str) + 1) = (uint8_t) ((x) >> 16);     \
			*((str) + 0) = (uint8_t) ((x) >> 24);     \
		}

		#define UNPACK64(x, str)                      \
		{                                             \
			*((str) + 7) = (uint8_t) ((x)      );     \
			*((str) + 6) = (uint8_t) ((x) >>  8);     \
			*((str) + 5) = (uint8_t) ((x) >> 16);     \
			*((str) + 4) = (uint8_t) ((x) >> 24);     \
			*((str) + 3) = (uint8_t) ((x) >> 32);     \
			*((str) + 2) = (uint8_t) ((x) >> 40);     \
			*((str) + 1) = (uint8_t) ((x) >> 48);     \
			*((str) + 0) = (uint8_t) ((x) >> 56);     \
		}

		uint32_t totalLength = (context.totalLength + context.blockLength) << 3;
		uint32_t blockNumber = (1 + ((SHA512_BLOCK_SIZE - 17) < (context.blockLength % SHA512_BLOCK_SIZE)));
		uint32_t blockLength = blockNumber << 7;

		memset(&context.block[context.blockLength], 0, blockLength - context.blockLength);

		context.block[context.blockLength] = 0x80;

		UNPACK32(totalLength, context.block + blockLength - 4)

		Transform(context, context.block, blockNumber);

		for (int32_t i = 0 ; i < 8; i++)
		{
			UNPACK64(context.hash[i], &digest[i << 3])
		}
	}

	/**
	 *
	 * 更新
	 *
	 * @param context 内容结构
	 * @param value 待更新内容
	 * @param length 待更新内容长度
	 *
	 */
	void SHA512::Update(Context & context, const uint8_t * value, uint32_t length)
	{
		uint32_t fill = SHA512_BLOCK_SIZE - context.blockLength;

		if (fill > length)
		{
			fill = length;
		}

		memcpy(&context.block[context.blockLength], value, fill);

		if (context.blockLength + length < SHA512_BLOCK_SIZE)
		{
			context.blockLength += length;

			return;
		}

		uint32_t overLength = length - fill;
		uint32_t blockNumber = overLength / SHA512_BLOCK_SIZE;

		const uint8_t * overValue = value + fill;

		Transform(context, context.block, 1);
		Transform(context, overValue, blockNumber);

		fill = overLength % SHA512_BLOCK_SIZE;

		memcpy(context.block, &overValue[blockNumber << 7], fill);

		context.blockLength  = fill;
		context.totalLength += (blockNumber + 1) << 7;
	}

	/**
	 *
	 * 转换
	 *
	 * @param context 内容结构
	 * @param block 待转换块
	 * @param number 待转换块个数
	 *
	 */
	void SHA512::Transform(Context & context, const uint8_t * block, uint32_t number)
	{
		#define CH(x, y, z) ((x & y) ^ (~x & z))
		#define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))

		#define SHFR(x, n) (x >> n)
		#define ROTR(x, n) ((x >> n) | (x << ((sizeof(x) << 3) - n)))
		#define ROTL(x, n) ((x << n) | (x >> ((sizeof(x) << 3) - n)))

		#define PACK64(str, x)                        \
		{                                             \
			*(x) =	((uint64_t) *((str) + 7)      ) | \
					((uint64_t) *((str) + 6) <<  8) | \
					((uint64_t) *((str) + 5) << 16) | \
					((uint64_t) *((str) + 4) << 24) | \
					((uint64_t) *((str) + 3) << 32) | \
					((uint64_t) *((str) + 2) << 40) | \
					((uint64_t) *((str) + 1) << 48) | \
					((uint64_t) *((str) + 0) << 56);  \
		}

		#define SHA512_F1(x) (ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39))
		#define SHA512_F2(x) (ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41))
		#define SHA512_F3(x) (ROTR(x,  1) ^ ROTR(x,  8) ^ SHFR(x,  7))
		#define SHA512_F4(x) (ROTR(x, 19) ^ ROTR(x, 61) ^ SHFR(x,  6))

		#define SHA512_SCR(i)                        \
		{                                            \
			Y[i] = SHA512_F4(Y[i -  2]) + Y[i -  7]  \
				 + SHA512_F3(Y[i - 15]) + Y[i - 16]; \
		}

		uint64_t SHA512_KEY[80] =
		{
			0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL,
			0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
			0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL,
			0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
			0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
			0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
			0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL,
			0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
			0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL,
			0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
			0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL,
			0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
			0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL,
			0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
			0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
			0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
			0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL,
			0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
			0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL,
			0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
			0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL,
			0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
			0xd192e819d6ef5218ULL, 0xd69906245565a910ULL,
			0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
			0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
			0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
			0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL,
			0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
			0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL,
			0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
			0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL,
			0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
			0xca273eceea26619cULL, 0xd186b8c721c0c207ULL,
			0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
			0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
			0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
			0x28db77f523047d84ULL, 0x32caab7b40c72493ULL,
			0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
			0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL,
			0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
		};

		uint64_t X[8]{ 0 };
		uint64_t Y[80]{ 0 };

		for (uint32_t i = 0; i < number; i++)
		{
			const uint8_t * blockValue = block + (i << 7);

			for (int32_t j = 0; j < 16; j++)
			{
				PACK64(&blockValue[j << 3], &Y[j])
			}

			for (int32_t j = 16; j < 80; j++)
			{
				SHA512_SCR(j)
			}

			for (int32_t j = 0; j < 8; j++)
			{
				X[j] = context.hash[j];
			}

			for (int32_t j = 0; j < 80; j++)
			{
				uint64_t t1 = X[7] + SHA512_F2(X[4]) + CH(X[4], X[5], X[6]) + SHA512_KEY[j] + Y[j];
				uint64_t t2 = SHA512_F1(X[0]) + MAJ(X[0], X[1], X[2]);

				X[7] = X[6];
				X[6] = X[5];
				X[5] = X[4];
				X[4] = X[3] + t1;
				X[3] = X[2];
				X[2] = X[1];
				X[1] = X[0];
				X[0] = t1 + t2;
			}

			for (int32_t j = 0; j < 8; j++)
			{
				context.hash[j] += X[j];
			}
		}
	}

	/**
	 *
	 * 初始化
	 *
	 * @param context 内容结构
	 *
	 */
	void SHA512::Initialization(Context & context)
	{
		context.hash[0] = 0x6a09e667f3bcc908ULL;
		context.hash[1] = 0xbb67ae8584caa73bULL;
		context.hash[2] = 0x3c6ef372fe94f82bULL;
		context.hash[3] = 0xa54ff53a5f1d36f1ULL;
		context.hash[4] = 0x510e527fade682d1ULL;
		context.hash[5] = 0x9b05688c2b3e6c1fULL;
		context.hash[6] = 0x1f83d9abfb41bd6bULL;
		context.hash[7] = 0x5be0cd19137e2179ULL;
	}
}
