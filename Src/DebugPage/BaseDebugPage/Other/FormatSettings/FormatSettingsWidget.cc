﻿/*
 * Copyright (C) 2018-2019 wuuhii. All rights reserved.
 *
 * The file is encoding with utf-8 (with BOM). It is a part of QtSwissArmyKnife
 * project. The project is a open source project, you can get the source from:
 *     https://github.com/wuuhii/QtSwissArmyKnife
 *     https://gitee.com/wuuhii/QtSwissArmyKnife
 *
 * If you want to know more about the project, please join our QQ group(952218522).
 * In addition, the email address of the project author is wuuhii@outlook.com.
 * Welcome to bother.
 *
 * I write the comment in English, it's not because that I'm good at English,
 * but for "installing B".
 */
#include "FormatSettingsWidget.hh"
#include "ui_FormatSettingsWidget.h"

FormatSettingsWidget::FormatSettingsWidget(SAKDebugPage *debugPage, QWidget *parent)
    :QWidget (parent)
    ,_debugPage (debugPage)
    ,ui (new Ui::FormatSettingsWidget)
{
    ui->setupUi(this);
    setWindowTitle(tr("格式设置"));
}

FormatSettingsWidget::~FormatSettingsWidget()
{

}
