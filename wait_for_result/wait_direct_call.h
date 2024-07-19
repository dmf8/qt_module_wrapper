#ifndef WAIT_DIRECT_CALL_H
#define WAIT_DIRECT_CALL_H

#include <QEventLoop>
#include <QObject>
#include <QTimer>

class QMutex;
class WaitDirectCall : public QObject
{
    Q_OBJECT
public:
    explicit WaitDirectCall(QObject *parent = nullptr);
    int Wait(int timeout_ms=0);

signals:

private:
    void OnTimeout();

private:
    QEventLoop loop_;
    QTimer timer_;
    QMutex* mutex_;
};

#endif // WAIT_DIRECT_CALL_H
