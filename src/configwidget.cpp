// Copyright (C) 2014-2018 Manuel Schneider

#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include "configwidget.h"
#include "extension.h"

/** ***************************************************************************/
IpAddress::ConfigWidget::ConfigWidget(Extension *extension, QWidget *parent)
    : QWidget(parent), extension_(extension) {

    ui.setupUi(this);
    // Initialize connections
    // connect(ui.tableView_searches, &QTableView::activated,
    //        this, &ConfigWidget::onActivated);
}



/** ***************************************************************************/
IpAddress::ConfigWidget::~ConfigWidget() {
}
