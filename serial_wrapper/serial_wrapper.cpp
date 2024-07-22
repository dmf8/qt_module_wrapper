#include "serial_wrapper.h"

#include <QSerialPort>
#include <QSerialPortInfo>

SerialWrapper::SerialWrapper(QObject *parent)
    : QObject(parent)
{
    connect(port, &QSerialPort::readyRead, this, &SerialWrapper::ReadyRead);
}

QStringList SerialWrapper::AvailablePorts()
{
    QStringList list;
    for (const auto &info : QSerialPortInfo::availablePorts())
        list.append(info.portName());

    return list;
}

void SerialWrapper::Init(const QString &name, int baud)
{
    port->setPortName(name);
    port->setBaudRate(baud);
}

bool SerialWrapper::Open(QIODevice::OpenMode mode)
{
    return port->open(mode);
}

void SerialWrapper::Close()
{
    if (port->isOpen()) port->close();
}

QByteArray SerialWrapper::ReadAll()
{
    return port->readAll();
}

void SerialWrapper::Write(const QByteArray &data)
{
    port->write(data);
}

QString SerialWrapper::GetName() const
{
    return port->portName();
}

bool SerialWrapper::IsOpened() const
{
    return port->isOpen();
}
