#ifndef __TINY_TOOLKIT__UTILITIES__SINGLETON__H__
#define __TINY_TOOLKIT__UTILITIES__SINGLETON__H__


#include "../common/common.h"

namespace Toolkit
{
    template<typename TypeT>
    class Singleton
    {
    public:
        template<typename ... Args>
        static TypeT &Instance(Args &&... args)
        {
            std::call_once(_onceFlag, [&]()
            { _instance = new TypeT(std::forward<Args>(args)...); });

            return *_instance;
        }

        Singleton(const Singleton &) = delete;

        Singleton &operator=(const Singleton &) = delete;

    protected:

        Singleton() = default;

        virtual ~Singleton() = default;

    protected:
        static TypeT *_instance;

        static std::once_flag _onceFlag;
    };

    template<typename TypeT>
    TypeT *Singleton<TypeT>::_instance = nullptr;

    template<typename TypeT>
    std::once_flag Singleton<TypeT>::_onceFlag;
}


#endif // __TINY_TOOLKIT__UTILITIES__SINGLETON__H__
