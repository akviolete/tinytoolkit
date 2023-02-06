#ifndef __KLOG__H__
#define __KLOG__H__

#include "define.h"

#define sAsyncLogger tinyToolkit::AsyncLogger::Instance()

/*
 *  数字转字符串宏
 * */
#define _TO_STRING_LINE_1(line) #line
#define __TO_STRING_LINE__1(line) _TO_STRING_LINE_1(line)
#define __TO__STRING__LINE__1 __TO_STRING_LINE__1(__LINE__)

#define __FILE__LINE__1 __FILE__ ":" __TO__STRING__LINE__1

/*
 * __FILE__ 文件名(不包含路径名)
 * */
#define KLOG_DEBUG(fmt, ...) sAsyncLogger.Debug(__FILE__LINE__1  "[" fmt, ##__VA_ARGS__)
#define KLOG_INFO(fmt, ...) sAsyncLogger.Info(__FILE__LINE__1  "[" fmt, ##__VA_ARGS__)
#define KLOG_WARNING(fmt, ...) sAsyncLogger.Warning(__FILE__LINE__1  "[" fmt, ##__VA_ARGS__)
#define KLOG_ERROR(fmt, ...) sAsyncLogger.Error(__FILE__LINE__1  "[" fmt, ##__VA_ARGS__)
#define KLOG_FATAT(fmt, ...) sAsyncLogger.Fatal(__FILE__LINE__1  "[" fmt, ##__VA_ARGS__)

/*
 * 初始化日志
 * */
void StartKlog();

/*
 * 关闭日志
 * */
void CloseKlog();

/*
 * 打印栈错误信息
 */
void PrintError(int32_t signalNo);


/*
* 程序异常触发信号
*/
void Terminate(int32_t signalno);


#endif