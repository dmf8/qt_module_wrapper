#include "network_interface.h"

#include <QByteArray>
#include <QDebug>
#include <QHostAddress>
#include <QNetworkInterface>

NetworkInterface::NetworkInterface()
{
}

QString NetworkInterface::GetEthernetActiveMac()
{
    QByteArray mac_raw(6, 0x00);

    QList<QNetworkInterface> list = GetAll();
    FiltByType(QNetworkInterface::Ethernet, list);
    FiltByFlagExists(QNetworkInterface::IsUp, list);
    if (!list.size()) return mac_raw.toHex();

    QString temp = list[0].hardwareAddress();
    FiltByIpv4Exists(list);
    if (list.size()) temp = list[0].hardwareAddress();

    return GetCleanMac(temp);
}

QList<QNetworkInterface> NetworkInterface::GetAll()
{
    return QNetworkInterface::allInterfaces();
}

void NetworkInterface::FiltByType(int type, QList<QNetworkInterface> &list)
{
    for (int i = list.size() - 1; i >= 0; --i) {
        if (list[i].type() != type) list.removeAt(i);
    }
}

void NetworkInterface::FiltByFlagExists(int flag, QList<QNetworkInterface> &list)
{
    for (int i = list.size() - 1; i >= 0; --i) {
        if (!list[i].flags().testFlag((QNetworkInterface::InterfaceFlag)flag)) list.removeAt(i);
    }
}

void NetworkInterface::FiltByIpv4Exists(QList<QNetworkInterface> &list)
{
    for (int i = list.size() - 1; i >= 0; --i) {
        QList<QNetworkAddressEntry> ips = list[i].addressEntries();
        bool found = false;
        for (const QNetworkAddressEntry &ip : ips)
            if (ip.ip().protocol() == QAbstractSocket::IPv4Protocol ||
                ip.ip().protocol() == QAbstractSocket::AnyIPProtocol) {
                found = true;
                continue;
            }
        if (!found) list.removeAt(i);
    }
}

void NetworkInterface::FiltByIpv6Exists(QList<QNetworkInterface> &list)
{
    for (int i = list.size() - 1; i >= 0; --i) {
        QList<QNetworkAddressEntry> ips = list[i].addressEntries();
        bool found = false;
        for (const QNetworkAddressEntry &ip : ips)
            if (ip.ip().protocol() == QAbstractSocket::IPv6Protocol ||
                ip.ip().protocol() == QAbstractSocket::AnyIPProtocol) {
                found = true;
                continue;
            }
        if (!found) list.removeAt(i);
    }
}

QString NetworkInterface::GetCleanMac(const QString &mac)
{
    QString ret = mac;
    ret.replace(':', "");
    return ret;
}
