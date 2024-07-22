#ifndef SERIAL_WRAPPER_H
#define SERIAL_WRAPPER_H

#include <QIODevice>
#include <QObject>

#include "serial_wrapper_global.h"

class QStringList;
class QSerialPort;

class SERIAL_WRAPPER_EXPORT SerialWrapper : public QObject
{
    Q_OBJECT
public:
    SerialWrapper(QObject* parent = nullptr);

    // init
    static QStringList AvailablePorts();
    void Init(const QString& name, int baud = 115200);

    // open
    bool Open(QIODevice::OpenMode mode = QIODevice::ReadWrite);
    void Close();

    // io
    QByteArray ReadAll();
    void Write(const QByteArray& data);

    // status
    bool IsOpened() const;
    QString GetName() const;

signals:
    void ReadyRead();

private:
    QSerialPort* port;
};

#endif  // SERIAL_WRAPPER_H
