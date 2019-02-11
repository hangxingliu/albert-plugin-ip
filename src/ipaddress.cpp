#include "ipaddress.h"

const QString IpAddress::IpAddressItem::IPV6_DESCRIPTION_FORMAT = QStringLiteral("%1 (ipv6)");

IpAddress::IpAddressItem::IpAddressItem(QString interfaceName, const QHostAddress &address)
       : interfaceName(interfaceName) {

    ipAddress = address.toString();
    ipType = address.protocol() == QAbstractSocket::IPv4Protocol ? IpType::IPV4 : IpType::IPV6;
    if(ipType == IPV4)
        description = interfaceName;
    else
        description = IPV6_DESCRIPTION_FORMAT.arg(interfaceName);
}
