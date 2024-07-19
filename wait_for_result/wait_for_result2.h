#ifndef WAIT_FOR_RESULT2_H
#define WAIT_FOR_RESULT2_H

#include <QEventLoop>
#include <QObject>
#include <atomic>

class WaitForResult2 : public QObject
{
    Q_OBJECT
public:
    explicit WaitForResult2(QObject *parent = nullptr);

    int Wait(int timeout_ms = 0);
    void TrySet(int ret);
    void SendResult();

signals:
    void Result(int ret);

private:
    std::atomic<int> atomic;
    QEventLoop loop;
};

#endif  // WAIT_FOR_RESULT2_H
