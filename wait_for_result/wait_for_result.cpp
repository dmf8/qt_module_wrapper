#include "wait_for_result.h"

#include <QCoreApplication>
#include <QEventLoop>
#include <QTimer>

WaitForResult::WaitForResult(QObject *parent) :
    QObject(parent)
{
}

/**
 * @brief WaitForResult::Wait
 * @param timeout_ms
 * @return timeout: -1; other: get from result
 */
int WaitForResult::Wait(int timeout_ms)
{
    QEventLoop loop;

    //timeout
    QTimer timer;
    timer.setSingleShot(true);

    QMetaObject::Connection con_timeout = connect(&timer, &QTimer::timeout, [&](){
        loop.exit(-1);
    });

    //get wait result
    QMetaObject::Connection con_result = connect(this, &WaitForResult::Result, [&](int ret){
        loop.exit(ret);
    });

    QCoreApplication::processEvents();
    if (timeout_ms > 0)
        timer.start(timeout_ms);
    int ret = loop.exec();
    timer.stop();

    disconnect(con_timeout);
    disconnect(con_result);

    return ret;
}
