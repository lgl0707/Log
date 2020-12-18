#ifndef LOG_H
#define LOG_H

#include "log4cpp/Category.hh"
#include <string.h>

#ifndef WIN32
#define PATHDELIMITER "/"
#else
#define PATHDELIMITER "\\"
#endif

#define GET_FILE_NAME_TO_LOG(file, basename)                                   \
    do {                                                                       \
        basename = strrchr((file), '\\');                                      \
        if (basename)                                                          \
            basename++;                                                        \
        else                                                                   \
            basename = (file);                                                 \
    } while (0)

typedef enum {EMERG  = 0,
              FATAL  = 0,
              ALERT  = 100,
              CRIT   = 200,
              ERROR  = 300,
              WARN   = 400,
              NOTICE = 500,
              INFO   = 600,
              DEBUG  = 700,
              NOTSET = 800
}Level;

#define BUF_LEN 4096

#define LOG(level, format, ...) do {\
        Log::getInstace().write(level, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);\
    }while(0)

class Log
{ 
public:
    ~Log();
    Log(const Log &) = delete ;
    Log &operator=(const Log &)=delete;
    static Log& getInstace();

    void write(Level level, const char* file, const char* func, int line, const char* format, ...);

private:
    Log();
    void init();
    void formatFunc(const char* file, const char* func, int line, const char* format, va_list alist, std::string& msg);

private:
    log4cpp::Category *m_pLogger;
};

#endif // LOG_H
