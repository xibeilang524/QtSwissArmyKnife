﻿/*
 * Copyright (C) 2019 wuuhii. All rights reserved.
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
#ifndef BASETRANSMISSSIONITEMWIDGET_HH
#define BASETRANSMISSSIONITEMWIDGET_HH

#include <QWidget>
#include <QIODevice>

class SAKDebugPage;
class BaseTransmissionItemWidget:public QWidget
{
    Q_OBJECT
public:
    BaseTransmissionItemWidget(SAKDebugPage *debugPage, QWidget *parent);

    /// 转发函数，子类必须重新实现
    virtual void write(QByteArray data);
signals:
    /// 读取数据后，发射该信号
    void bytesRead(QByteArray data);
    /// 输出消息
    void requestOutputMessage(QString info, bool isInfo = true);
protected:
    SAKDebugPage *debugPage;
    void outputMessage();
};

#endif
