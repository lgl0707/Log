#include <QCoreApplication>
#include "log.h"

#ifdef WIN32
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Advapi32.lib")
#endif

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LOG(DEBUG, "gomfvmdlpmvpd:%s:%d", "liuganlu", 1234);

    return a.exec();
}




