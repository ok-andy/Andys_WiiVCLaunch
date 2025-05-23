#pragma once

#include <coreinit/debug.h>
#include <string.h>
#include <whb/log.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define LOG_APP_TYPE "P"
#define LOG_APP_NAME "WiiVCLaunch"

#define __FILENAME_X__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILENAME_X__)

#define LOG(LOG_FUNC, FMT, ARGS...) LOG_EX(LOG_FUNC, "", "", FMT, ##ARGS)

#define LOG_EX(LOG_FUNC, LOG_LEVEL, LINE_END, FMT, ARGS...)                                                                                            \
    do                                                                                                                                                 \
    {                                                                                                                                                  \
        LOG_FUNC("[(%s)%s][%23s]%30s@L%04d: " LOG_LEVEL "" FMT "" LINE_END, LOG_APP_TYPE, LOG_APP_NAME, __FILENAME__, __FUNCTION__, __LINE__, ##ARGS); \
    } while (0)

#ifdef DEBUG

#ifdef VERBOSE_DEBUG
#define DEBUG_FUNCTION_LINE_VERBOSE(FMT, ARGS...) LOG(WHBLogPrintf, FMT, ##ARGS)
#else
#define DEBUG_FUNCTION_LINE_VERBOSE(FMT, ARGS...) while (0)
#endif

#define DEBUG_FUNCTION_LINE(FMT, ARGS...) LOG(WHBLogPrintf, FMT, ##ARGS)

#define DEBUG_FUNCTION_LINE_WRITE(FMT, ARGS...) LOG(WHBLogWritef, FMT, ##ARGS)

#define DEBUG_FUNCTION_LINE_ERR(FMT, ARGS...) LOG_EX(WHBLogPrintf, "##ERROR## ", "", FMT, ##ARGS)
#define DEBUG_FUNCTION_LINE_WARN(FMT, ARGS...) LOG_EX(WHBLogPrintf, "##WARN ## ", "", FMT, ##ARGS)
#define DEBUG_FUNCTION_LINE_INFO(FMT, ARGS...) LOG_EX(WHBLogPrintf, "##INFO ## ", "", FMT, ##ARGS)

#else

#define DEBUG_FUNCTION_LINE_VERBOSE(FMT, ARGS...) while (0)

#define DEBUG_FUNCTION_LINE(FMT, ARGS...) while (0)

#define DEBUG_FUNCTION_LINE_WRITE(FMT, ARGS...) while (0)

#define DEBUG_FUNCTION_LINE_ERR(FMT, ARGS...) LOG_EX(OSReport, "##ERROR## ", "\n", FMT, ##ARGS)
#define DEBUG_FUNCTION_LINE_WARN(FMT, ARGS...) LOG_EX(OSReport, "##WARN ## ", "\n", FMT, ##ARGS)
#define DEBUG_FUNCTION_LINE_INFO(FMT, ARGS...) LOG_EX(OSReport, "##INFO ## ", "\n", FMT, ##ARGS)

#endif

    void initLogging();
    void deinitLogging();

#ifdef __cplusplus
}
#endif
