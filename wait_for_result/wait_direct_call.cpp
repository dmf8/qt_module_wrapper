#include "wait_direct_call.h"

WaitDirectCall::WaitDirectCall(QObject *parent)
    : QObject(parent)
{
    timer_.setSingleShot(true);
}


int WaitDirectCall::Wait(int timeout_ms)
{
    timer_.setInterval(timeout_ms);
}
