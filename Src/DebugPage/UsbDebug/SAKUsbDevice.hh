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
#ifndef SAKUSBDEVICE_HH
#define SAKUSBDEVICE_HH

#include <QThread>
#include <QUdpSocket>

class SAKDebugPage;
class SAKUsbDevice:public QThread
{
    Q_OBJECT
public:
    SAKUsbDevice(QString localHost, quint16 localPort,
                 bool enableCustomLocalSetting,
                 QString targetHost, quint16 targetPort,
                 SAKDebugPage *debugPage,
                 QObject *parent = Q_NULLPTR);
    void readBytes();
    void writeBytes(QByteArray data);
private:
    void run();    
private:
    QString localHost;
    quint16 localPort;
    bool enableCustomLocalSetting;
    QString targetHost;
    quint16 targetPort;
    SAKDebugPage *debugPage;
    QUdpSocket *udpSocket;

signals:
    void bytesRead(QByteArray);
    void bytesWriten(QByteArray);

    void deviceStatuChanged(bool opened);
    void messageChanged(QString message, bool isInfo);
};

#endif
