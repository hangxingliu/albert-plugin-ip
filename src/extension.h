// Copyright (C) 2014-2018 Manuel Schneider

#pragma once
#include <QLoggingCategory>
#include <memory>
#include "albert/extension.h"
#include "albert/queryhandler.h"
#include "albert/fallbackprovider.h"
#include "ipaddress.h"

Q_DECLARE_LOGGING_CATEGORY(qlc_ip)

namespace IpAddress {

class ExtensionContext;

class Extension final :
        public Core::Extension,
        public Core::QueryHandler/*,
        public Core::FallbackProvider*/
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ALBERT_EXTENSION_IID FILE "metadata.json")

public:

    Extension();
    ~Extension() override;

    QString name() const override { return "IpAddress"; }
    QWidget *widget(QWidget *parent = nullptr) override;
//    QStringList triggers() const override;
    void handleQuery(Core::Query * query) const override;

    // // fallbacks will be invoke when result of albert is empty!
    // std::vector<std::shared_ptr<Core::Item>> fallbacks(const QString &) override;

private:
    std::unique_ptr<ExtensionContext> extensionContext;
    std::vector<IpAddressItem> getIpAddresses(IpAddressItem::IpType filter = IpAddressItem::IpType::NONE) const;
};

}
