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
#ifndef READWRITESETTINGSWIDGET_HH
#define READWRITESETTINGSWIDGET_HH

#include <QDialog>
#include <QComboBox>


namespace Ui {
class ReadWriteSettingsWidget;
};

class SAKDebugPage;
class ReadWriteSettingsWidget:public QDialog
{
    Q_OBJECT
public:
    ReadWriteSettingsWidget(SAKDebugPage *debugPage, QWidget* parent = nullptr);
private:
    Ui::ReadWriteSettingsWidget *ui = nullptr;

    QComboBox *readParametersComboBox;
    QComboBox *writeParametersComboBox;
private slots:
    void on_readParametersComboBox_currentTextChanged(const QString &text);
    void on_writeParametersComboBox_currentTextChanged(const QString &text);

private:
    SAKDebugPage *debugPage;
    int waitForReadyReadTime;
    int waitForBytesWrittenTime;

    void setReadWriteParameters();
};

#endif
