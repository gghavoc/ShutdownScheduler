#ifndef SHUTDOWN_H
#define SHUTDOWN_H
#include <stdint.h>

#ifndef SHUTDOWN_FLAGS
#define SHUTDOWN_FLAGS
    #ifdef Q_OS_UNIX
        #define SHUTDOWN_COMMAND "shutdown"
        #define SHUTDOWN "-P"
        #define RESTART "-r"
        #define HALT "-H"
        #define CANCEL "-c"
        #define TIME "-t"
    #elif defined Q_OS_WIN
        #define SHUTDOWN_COMMAND "shutdown"
        #define SHUTDOWN "/s"
        #define RESTART "/r"
        #define HALT "/s"
        #define CANCEL "/c"
        #define TIME "/t"
    #endif // Q_OS_UNIX
#endif // SHUTDOWN_FLAGS

#ifndef TO_SECONDS
#define TO_SECONDS
    #define SECONDS_IN_YEAR 32140800
    #define SECONDS_IN_MONTH 2678400
    #define SECONDS_IN_DAY 86400
    #define SECONDS_IN_HOUR 3600
    #define SECONDS_IN_MINUTE 60
#endif

#ifndef APP_INFO
#define APP_INFO
    #define APP_VERSION "0.1.0"
    #define APP_STATUS "Work In Progress"
    #define APP_BUILD_NO "365"
#endif

namespace ShutdownScheduler {
    enum class Type : int16_t
    {
        Invalid = -1,
        Shutdown,
        Restart,
        LogOut,
    };

    enum class Timing : int16_t
    {
        Invalid = -1,
        Now,
        At,
        After,
    };
}

#endif // SHUTDOWN_H
