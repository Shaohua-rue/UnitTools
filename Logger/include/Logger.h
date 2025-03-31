#pragma once
#include <iostream>
#include <string>
#include "rang.hpp"



// LOG_INFO("%s %d", arg1, arg2)
#define LOG_INFO(logmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(INFO); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)

#define LOG_ERROR(logmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(ERROR); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)

#define LOG_FATAL(logmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(FATAL); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
        exit(-1); \
    } while(0)


#define LOG_DEBUG(logmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(DEBUG); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)


//定义日志级别 INFO ERROR FATAL DEBUG
enum LogLevel
{
    INFO,   //普通信息
    ERROR,  //错误信息
    FATAL,  //core dump 信息
    DEBUG   //调试信息
};
/************************时间戳类**********************/

class Timestamp
{
public:
    Timestamp();
    explicit Timestamp(int64_t microSecondsSinceEpoch);
    static Timestamp now();
    std::string toString() const;
private:
    int64_t microSecondsSinceEpoch_;
};

Timestamp::Timestamp():microSecondsSinceEpoch_(0)
{
}

Timestamp::Timestamp(int64_t microSecondsSinceEpoch):microSecondsSinceEpoch_ (microSecondsSinceEpoch)
{
}
 
Timestamp Timestamp:: now()
{
    return Timestamp(time(NULL));
}
std::string Timestamp::toString() const
{
    char buf[128] = {0};
    tm *tm_time = localtime(&microSecondsSinceEpoch_);
    snprintf(buf, 128, "%4d/%02d/%02d %02d:%02d:%02d",
            tm_time->tm_year + 1900,
            tm_time->tm_mon + 1,
            tm_time->tm_mday,
            tm_time->tm_hour,
            tm_time->tm_min,
            tm_time->tm_sec);
    return buf;
}

/*********************************日志类**************************************/
class Logger 
{
public:
    //获取日志唯一的实例对象
    static Logger & instance();
    Logger() = default;
    ~Logger() = default;

    Logger(const Logger&) = delete;
    Logger &operator = (const Logger &) = delete;

    //设置日志级别
    void setLogLevel(int level);
    
    //写日志
    void log(std::string msg);


private:
    int logLevel_;
};

//获取日志的唯一实例对象，单例

Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}

//设置日志级别
void Logger::setLogLevel(int level)
{
    logLevel_ = level;
}

//写日志[级别信息] time ：msg
void Logger::log(std::string msg)
{
   switch (logLevel_)
   {
   case INFO:
       std::cout << rang::style::bold 
       << rang::fg::green
       << "[INFO ] "
       <<Timestamp::now().toString() << " " 
       <<msg <<rang::style::reset << std::endl;
       break;
   case ERROR:
        std::cout << rang::style::bold
        << rang::fg::yellow
        << "[ERROR] "
        <<Timestamp::now().toString()<< " " 
        << msg <<rang::style::reset << std::endl;
       break;
   case FATAL:
        std::cout << rang::style::bold
        << rang::fg::red
        << "[FATAL] "<<
       Timestamp::now().toString() << " "  
        << msg <<rang::style::reset << std::endl;
       break;
   case DEBUG:
        std::cout << rang::style::bold << "[DEBUG] "
       <<Timestamp::now().toString() << " " 
       << msg <<rang::style::reset<< std::endl;
       break;
   default:
       break;
   }
   
  
}






