// Copyright (C) 2014-2018 Manuel Schneider

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPointer>
#include <QStandardPaths>
#include <QHostAddress>
#include <QUrl>
#include <QNetworkInterface>

#include <vector>
#include <string>

#include "configwidget.h"
#include "extension.h"
#include "ipaddress.h"
#include "albert/util/standardactions.h"
#include "albert/util/standarditem.h"
#include "xdg/iconlookup.h"


Q_LOGGING_CATEGORY(qlc_ip, "ip")
#define DEBUG qCDebug(qlc_ip).noquote()
#define INFO qCInfo(qlc_ip).noquote()
#define WARNING qCWarning(qlc_ip).noquote()
#define CRITICAL qCCritical(qlc_ip).noquote()

using namespace Core;
using namespace std;
using namespace IpAddress;

// namespace {
//     static constexpr const char * CONFIG_FILE_JSON = "ipaddress.json";
// }

/** ***************************************************************************/
/** ***************************************************************************/
/** ***************************************************************************/
/** ***************************************************************************/
class IpAddress::ExtensionContext {
public:
    QPointer<ConfigWidget> widget;

    QLocale locale;
    QString iconPath;
};



/** ***************************************************************************/
/** ***************************************************************************/
/** ***************************************************************************/
/** ***************************************************************************/
IpAddress::Extension::Extension()
    : Core::Extension("org.albert.extension.ip"),
      Core::QueryHandler(Core::Plugin::id()),
      extensionContext(new ExtensionContext) {

    registerQueryHandler(this);

    // QString configJson = configLocation().filePath(CONFIG_FILE_JSON);
    // Deserialize engines
    // QFile file(configJson);
    // if (file.open(QIODevice::ReadOnly)) {
    //    QJsonArray array = QJsonDocument::fromJson(file.readAll()).array();
    //    // load config
    // } else {
    //     WARNING << QString("Could not load from file: '%1'.").arg(configJson);
    // }


    extensionContext->locale = QLocale(QLocale::system().name());

    QString iconPath = XDG::IconLookup::iconPath("info");
    extensionContext->iconPath = iconPath.isNull() ? ":network" : iconPath;

}



/** ***************************************************************************/
IpAddress::Extension::~Extension() {

}



/** ***************************************************************************/
QWidget *IpAddress::Extension::widget(QWidget *parent) {
    if (extensionContext->widget.isNull())
        extensionContext->widget = new ConfigWidget(this, parent);
    return extensionContext->widget;
}



/** ***************************************************************************/
void IpAddress::Extension::handleQuery(Core::Query * query) const {
    const auto& ctx = extensionContext;
    const auto& queryString = query->string();

    if(!queryString.startsWith("ip"))
        return;

    std::vector<IpAddressItem> ipAddresses;
    if(queryString == "ip") ipAddresses = getIpAddresses(IpAddressItem::IPV4);
    else if(queryString.indexOf('6') >= 0) ipAddresses = getIpAddresses(IpAddressItem::IPV6);
    else ipAddresses = getIpAddresses();

    int i = 0;
    for(const auto& ip: ipAddresses) {
        auto item = make_shared<StandardItem>("ipaddress_" + QString::number(i++));
        item->setIconPath(ctx->iconPath);
        item->setText(ip.ipAddress);
        item->setSubtext(ip.description);
        item->setCompletion(item->text());
        item->addAction(make_shared<ClipAction>("Copy ip address to clipboard",ip.ipAddress));
        query->addMatch(move(item), UINT_MAX);
    }

}

/** ***************************************************************************/
std::vector<IpAddressItem> IpAddress::Extension::getIpAddresses(IpAddressItem::IpType filter) const {
    std::vector<IpAddressItem> result;
    for (const auto& interface: QNetworkInterface::allInterfaces()) {
        auto interfaceName = interface.humanReadableName();
        auto flag = interface.flags();
        DEBUG << interfaceName;

        if(flag.testFlag(QNetworkInterface::IsLoopBack)) continue;
        if(!flag.testFlag(QNetworkInterface::IsUp)) continue;

        for(const auto& addressEntry: interface.addressEntries()) {
            const auto& address = addressEntry.ip();
            DEBUG << "  " << address.toString();

            if(address.isBroadcast()) continue;
            if(address.isLoopback()) continue;
            if(address.isNull()) continue;

            IpAddressItem item(interfaceName, address);
            if(filter && filter != item.ipType)
                continue;
            result.push_back(std::move(item));
        };
    }
    return result;
}
