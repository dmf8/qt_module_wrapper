#include "wait_for_result2.h"

#include <QCoreApplication>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <thread>

WaitForResult2::WaitForResult2(QObject *parent)
    : QObject(parent)
    , atomic(-1)
{
}

int WaitForResult2::Wait(int timeout_ms)
{
    // timeout
    QTimer timer;
    timer.setSingleShot(true);

    QMetaObject::Connection con_timeout =
        connect(&timer, &QTimer::timeout, [&]() { loop.exit(-1); });

    // get wait result
    QMetaObject::Connection con_result = connect(
        this, &WaitForResult2::Result, [&](int ret) { loop.exit(ret); });

    QCoreApplication::processEvents();
    if (timeout_ms > 0) timer.start(timeout_ms);
    int ret = loop.exec();
    timer.stop();

    disconnect(con_timeout);
    disconnect(con_result);

    return ret;
}

void WaitForResult2::TrySet(int ret)
{
    if (atomic.load() == -1) atomic.store(ret);
}

void WaitForResult2::SendResult()
{
    if (!loop.isRunning()) {
        QTimer::singleShot(10, [&] { SendResult(); });
    } else
        emit Result(atomic.load());
}
