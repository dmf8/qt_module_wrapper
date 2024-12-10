#ifndef DEBUG_H
#define DEBUG_H

#include <QDebug>
#include <QThread>
#include <QDateTime>

#define DBG_FUNC qDebug()<<__FUNCTION__

#define DBG_TIME qDebug()<<QTime::currentTime().toString("hh:mm:ss.zzz")
#define DBG_DATETIME qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss.zzz")
#define DBG_FUNC_TIME qDebug()<<__FUNCTION__<<QTime::currentTime().toString("hh:mm:ss.zzz")
#define DBG_FUNC_DATETIME qDebug()<<__FUNCTION__<<QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss.zzz")

#define DBG_THREAD qDebug()<<QThread::currentThread()
#define DBG_FUNC_THREAD qDebug()<<__FUNCTION__<<QThread::currentThread()

#endif //DEBUG_H
