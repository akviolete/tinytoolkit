#ifndef __TINY_TOOLKIT__UTILITIES__SINGLETON__H__
#define __TINY_TOOLKIT__UTILITIES__SINGLETON__H__


/**
 *
 *  作者: hm
 *
 *  说明: 单例模式
 *
 */


#include "../common/common.h"


namespace tinyToolkit
{
	template <typename TypeT>
	class TINY_TOOLKIT_API Singleton
	{
	public:
		/**
		 *
		 * 获取单例
		 *
		 * @tparam Args [all built-in types]
		 *
		 * @param args 待初始化数据
		 *
		 * @return 单例对象引用
		 *
		 */
		template <typename ... Args>
		static TypeT & Instance(Args &&... args)
		{
			std::call_once(_onceFlag, [&](){ _instance = new TypeT(std::forward<Args>(args)...); });

			return *_instance;
		}

		/**
		 *
		 * 构造函数
		 *
		 * @param rhs 实例化对象
		 *
		 */
		Singleton(const Singleton &) = delete;

		/**
		 *
		 * 函数重载
		 *
		 * @param rhs 待赋值实例化
		 *
		 * @return 实例化对象
		 *
		 */
		Singleton & operator=(const Singleton &) = delete;

	protected:
		/**
		 *
		 * 构造函数
		 *
		 */
		Singleton() = default;

		/**
		 *
		 * 析构函数
		 *
		 */
		virtual ~Singleton() = default;

	protected:
		class TINY_TOOLKIT_API GarbageCollector
		{
		public:
			/**
			*
			* 析构函数
			*
			*/
			~GarbageCollector()
			{
				if (Singleton<TypeT>::_instance)
				{
					delete Singleton<TypeT>::_instance;

					Singleton<TypeT>::_instance = nullptr;
				}
			}
		};

	protected:
		static TypeT * _instance;

		static std::once_flag _onceFlag;

		static GarbageCollector _garbageCollector;
	};

	template <typename TypeT>
	TypeT * Singleton<TypeT>::_instance = nullptr;

	template <typename TypeT>
	std::once_flag Singleton<TypeT>::_onceFlag;

	template <typename TypeT>
	typename Singleton<TypeT>::GarbageCollector Singleton<TypeT>::_garbageCollector;
}


#endif // __TINY_TOOLKIT__UTILITIES__SINGLETON__H__
