#ifndef WAIT_FOR_RESULT_H
#define WAIT_FOR_RESULT_H

#include "wait_for_result_global.h"

#include <QObject>

class WAIT_FOR_RESULT_EXPORT WaitForResult : public QObject
{
    Q_OBJECT
public:
    WaitForResult(QObject* parent = nullptr);

    /**
     * @brief block current thread and wait for result or timeout
     * @param timeout_ms, 0 or negative value means never timeout
     * @return timeout: -1; other: result code
     */
    int Wait(int timeout_ms = 0);

signals:
    /**
     * @brief connect all result signals to this one to end wait
     * user should confirm only corresponding signal may be emitted when waiting
     * @param ret, user defined return code. do not use -1, which means wait timeout
     */
    void Result(int ret);
};

#endif // WAIT_FOR_RESULT_H
