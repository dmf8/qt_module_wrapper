#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

#include <QList>

#include "local_device_global.h"
class QNetworkInterface;

class LOCAL_DEVICE_EXPORT NetworkInterface
{
public:
    NetworkInterface();

    static QString GetEthernetActiveMac();

private:
    static QList<QNetworkInterface> GetAll();
    static void FiltByType(int type, QList<QNetworkInterface>& list);
    static void FiltByFlagExists(int flag, QList<QNetworkInterface>& list);
    static void FiltByIpv4Exists(QList<QNetworkInterface>& list);
    static void FiltByIpv6Exists(QList<QNetworkInterface>& list);
    static QString GetCleanMac(const QString& mac);
};

#endif  // NETWORK_INTERFACE_H
