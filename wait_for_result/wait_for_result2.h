#ifndef WAIT_FOR_RESULT2_H
#define WAIT_FOR_RESULT2_H

#include <QEventLoop>
#include <QObject>
#include <atomic>

#include "wait_for_result_global.h"

class WAIT_FOR_RESULT_EXPORT WaitForResult2 : public QObject
{
    Q_OBJECT
public:
    explicit WaitForResult2(QObject *parent = nullptr);

    /**
     * @brief Wait for some time, until Result signal raised or timeout
     * @param timeout_ms
     * @return return code
     * -1 if timeout
     * user value set by TrySet function
     */
    int Wait(int timeout_ms = 0);

    /**
     * @brief call this function to set the return code
     * return code can only be set to once if return code != -1
     * @param return code
     */
    void TrySet(int ret);

    /**
     * @brief make sure Result signal is sent while event loop is running
     * if event loop is not started, try to send the signal every 10ms
     */
    void SendResult();

signals:
    /**
     * @brief catch this signal only, do not need to send manually.
     * use SendResult instead
     */
    void Result(int ret);

private:
    std::atomic<int> atomic;  // init value -1
    QEventLoop loop;
};

#endif  // WAIT_FOR_RESULT2_H
