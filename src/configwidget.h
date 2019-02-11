// Copyright (C) 2014-2018 Manuel Schneider

#pragma once
#include <QWidget>
#include "ui_configwidget.h"

namespace IpAddress {

    class Extension;

    class ConfigWidget final : public QWidget {
        Q_OBJECT

    public:

        explicit ConfigWidget(Extension *extension, QWidget *parent = 0);
        ~ConfigWidget();
        Ui::ConfigWidget ui;

    private:
        Extension *extension_;
    };

}
