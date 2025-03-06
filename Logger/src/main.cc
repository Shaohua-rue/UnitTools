/**
 * @brief 日志模块的单元测试
*/

#include <iostream>
#include <string>
#include <Logger.h>

#define LOGDEBUG

void fatalFunction()
{
    LOG_FATAL("%s:%s:%d 程序错误结束!\n", __FILE__, __FUNCTION__, __LINE__);
}
int main()
{
    std::string info = "info";
    int no = 1;
    LOG_INFO("test name %s, no%d\n", info.c_str(),no);
    LOG_ERROR("test error");
   
    LOG_DEBUG("test debug");

    fatalFunction();
    
    return 0;
}