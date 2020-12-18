#include "log.h"
#include "log4cpp/RollingFileAppender.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/PropertyConfigurator.hh"
#include <QCoreApplication>

Log::Log()
{
    init();
}

Log::~Log()
{
    log4cpp::Category::shutdown();
}

Log &Log::getInstace()
{
    static Log instance;
    return instance;
}

void Log::init()
{
   m_pLogger = NULL;

   try {
        QString initFileName = QCoreApplication::applicationDirPath();
        initFileName = initFileName + PATHDELIMITER + "log.conf";

        log4cpp::PropertyConfigurator::configure(initFileName.toStdString());

        log4cpp::Category &sub = log4cpp::Category::getRoot();
        m_pLogger = &sub;
   } catch (std::exception const& e) {
        printf("log init failed%s", e.what());
   }
}

void Log::write(Level level, const char *file, const char *func, int line, const char *format, ...)
{
    int priority = m_pLogger->getPriority();
    if(priority < level)
    {
        return;
    }

    if(m_pLogger == NULL)
    {
        return;
    }

    std::string info;
    va_list alist;
    va_start (alist, format);
    formatFunc(file, func, line, format, alist, info);
    va_end(alist);

    try {
            switch(level) {
            case FATAL:
                m_pLogger->fatal(info);
                break;
            case ALERT:
                m_pLogger->alert(info);
                break;
            case CRIT:
                m_pLogger->crit(info);
                break;
            case ERROR:
                m_pLogger->error(info);
                break;
            case WARN:
                m_pLogger->warn(info);
                break;
            case NOTICE:
                m_pLogger->notice(info);
                break;
            case INFO:
                m_pLogger->info(info);
                break;
            case DEBUG:
                m_pLogger->debug(info);
                break;
            default:
                break;
            }
        } catch(...) {
             printf("log write failed");
        }
}

void Log::formatFunc(const char* file, const char* func, int line, const char* format, va_list alist, std::string& msg)
{
    char buf[BUF_LEN] = {0};
    const char *basename = NULL;

    GET_FILE_NAME_TO_LOG(file, basename);

    int prefixLen = snprintf(buf, BUF_LEN-1, "[%s:%d:%s] ", basename, line, func);

    int contentLen = vsnprintf(buf+prefixLen, BUF_LEN-1-prefixLen, format, alist);

    int dataLen = prefixLen + contentLen;
//    buf[dataLen] = '\n';

    msg = buf;
}
