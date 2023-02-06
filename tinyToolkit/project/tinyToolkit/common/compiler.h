#ifndef __TINY_TOOLKIT__COMMON__COMPILER__H__
#define __TINY_TOOLKIT__COMMON__COMPILER__H__


/**
 *
 *  作者: hm
 *
 *  说明: 编译器信息
 *
 */


#define TINY_TOOLKIT_COMPILER_VC 			1
#define TINY_TOOLKIT_COMPILER_GNU       	2
#define TINY_TOOLKIT_COMPILER_SUN     		3
#define TINY_TOOLKIT_COMPILER_INTEL     	4
#define TINY_TOOLKIT_COMPILER_BORLAND   	5


#if defined( _MSC_VER )
#
#  define TINY_TOOLKIT_COMPILER TINY_TOOLKIT_COMPILER_VC
#
#elif defined( __GNUC__ )
#
#  define TINY_TOOLKIT_COMPILER TINY_TOOLKIT_COMPILER_GNU
#
#  define TINY_TOOLKIT_COMPILER_VERSION ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ )
#
#elif defined( __SUNPRO_C ) || defined( __SUNPRO_CC )
#
#  define TINY_TOOLKIT_COMPILER TINY_TOOLKIT_COMPILER_SUN
#
#elif defined( __INTEL_COMPILER )
#
#  define TINY_TOOLKIT_COMPILER TINY_TOOLKIT_COMPILER_INTEL
#
#elif defined( __BORLANDC__ )
#
#  define TINY_TOOLKIT_COMPILER TINY_TOOLKIT_COMPILER_BORLAND
#
#else
#
#  error "FATAL ERROR: Unknown compiler."
#
#endif


#endif // __TINY_TOOLKIT__COMMON__COMPILER__H__
