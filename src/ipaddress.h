#pragma once
#include <QHostAddress>
#include <QString>

namespace IpAddress {
    class IpAddressItem {
    public:
        static const QString IPV6_DESCRIPTION_FORMAT;

        enum IpType {
           NONE = 0,
           IPV4 = 4,
           IPV6 = 6,
        };

        QString interfaceName;
        QString ipAddress;
        IpType ipType;

        /**
         * Eg. "wlp9s0" or "docker0 (ipv6)"
         */
        QString description;


        IpAddressItem(QString interfaceName, const QHostAddress& address);
    };
}
