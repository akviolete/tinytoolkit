#include "klog.h"

class TestLogLayout : public tinyToolkit::ILogLayout
{
public:
    std::string Format(const tinyToolkit::LogEvent &event) override
    {

        return tinyToolkit::String::Format(
                "{} {:02}/{:02}/{:02} {:02}:{:02}:{:02}.{}][{}]{}\n",
                tinyToolkit::LogPriority::Name(event.priority),
                (event.tm.tm_year + 1900) % 100,
                event.tm.tm_mon + 1,
                event.tm.tm_mday,
                event.tm.tm_hour,
                event.tm.tm_min,
                event.tm.tm_sec,
                tinyToolkit::Time::Microseconds(event.time) % 1000000,
                event.threadID,
                event.message);
    }
};


void CloseKlog()
{
    sAsyncLogger.Wait();
}

void StartKlog()
{

    auto sink_file = std::make_shared<tinyToolkit::FileLogSink>("RotatingFileLogSink", "/tmp/log.log");

    auto sink_comsole = std::make_shared<tinyToolkit::ConsoleLogSink>("console");

    auto layout = std::make_shared<TestLogLayout>();
    auto filter_1 = std::make_shared<tinyToolkit::PriorityLogFilter>("D");
    auto filter_2 = std::make_shared<tinyToolkit::PriorityLogFilter>("D");

    sink_file->SetLayout(layout);
    sink_file->SetFilter(filter_2);

    sink_comsole->SetLayout(layout);
    sink_comsole->SetFilter(filter_1);

    sAsyncLogger.AddSink(sink_file);
    sAsyncLogger.AddSink(sink_comsole);

    sAsyncLogger.EnableSinkAutoFlush();

    KLOG_INFO("StartApp:{}", tinyToolkit::OS::ProcessID());

}


//打印栈错误信息
void PrintError(int32_t signalNo)
{
    for (auto &iter : tinyToolkit::StackTrace::Content(signalNo))
    {
        KLOG_ERROR("{}", iter);
    }

    CloseKlog();

    exit(0);
}

//程序异常触发信号
void Terminate(int32_t signalno)
{
    KLOG_ERROR("Terminate:{}", signalno);

    CloseKlog();

    exit(0);
}
