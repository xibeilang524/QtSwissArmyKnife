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
#include <QHostAddress>
#include "SAKBase.hh"
#include "TcpTransmissionItemWidget.hh"
#include "ui_TcpTransmissionItemWidget.h"

TcpTransmissionItemWidget::TcpTransmissionItemWidget(SAKDebugPage *debugPage, QWidget *parent)
    :BaseTransmissionItemWidget (debugPage, parent)
    ,ui (new Ui::TcpTransmissionItemWidget)
    ,tcpSocket (nullptr)
{
    ui->setupUi(this);

    enableCheckBox = ui->enableCheckBox;
    customAddressCheckBox = ui->customAddressCheckBox;
    localAddressComboBox = ui->addressComboBox;
    localPortLineEdit = ui->portLineEdit;
    handleReceiveDataCheckBox = ui->handleReceiveDataCheckBox;
    serverAddressLineEdit = ui->targetAddressLineEdit;
    serverPortLineEdit = ui->targetPortLineEdit;

    SAKBase::instance()->initIpComboBox(localAddressComboBox);
}

TcpTransmissionItemWidget::~TcpTransmissionItemWidget()
{
    if (tcpSocket){
        delete tcpSocket;
    }
    delete ui;
}

void TcpTransmissionItemWidget::write(QByteArray data)
{
    if (tcpSocket){
        if (!tcpSocket->write(data)){
#ifdef QT_DEBUG
        qDebug() << "发送取数据失败" << tcpSocket->errorString();
#endif
        }
    }
}

void TcpTransmissionItemWidget::on_enableCheckBox_clicked()
{
    auto closeDev = [&](){
        if (tcpSocket){
            tcpSocket->disconnectFromHost();
            if (tcpSocket->state() == QTcpSocket::ConnectedState){
                tcpSocket->waitForDisconnected();
            }
            disconnect(tcpSocket, &QTcpSocket::readyRead, this, &TcpTransmissionItemWidget::read);
            delete tcpSocket;
            tcpSocket = nullptr;
            this->setUiEnable(true);
        }
    };

    if (enableCheckBox->isChecked()){
        tcpSocket = new QTcpSocket;
        if (customAddressCheckBox->isChecked()){
             if (!tcpSocket->bind(QHostAddress(localAddressComboBox->currentText()), static_cast<quint16>(localPortLineEdit->text().toInt()))){
                emit requestOutputMessage(tr("设备绑定失败：") + tcpSocket->errorString(), false);
                enableCheckBox->setChecked(false);
                closeDev();
                return;
             }
        }

        if (!tcpSocket->open(QTcpSocket::ReadWrite)){
            emit requestOutputMessage(tr("设备无法打开：") + tcpSocket->errorString(), false);
            enableCheckBox->setChecked(false);
            closeDev();
            return;
        }

        connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpTransmissionItemWidget::read);
        tcpSocket->connectToHost(serverAddressLineEdit->text(), static_cast<quint16>(serverPortLineEdit->text().toInt()));
        if (!tcpSocket->waitForConnected()){
            emit requestOutputMessage(tr("无法连接服务器：") + tcpSocket->errorString(), false);
            enableCheckBox->setChecked(false);            
            closeDev();
        }else{
            this->setUiEnable(false);
        }
    }else{
        closeDev();
    }
}

void TcpTransmissionItemWidget::read()
{    
    if (tcpSocket){
        QByteArray data = tcpSocket->readAll();
        if (handleReceiveDataCheckBox->isChecked()){
            emit bytesRead(data);;
        }
    }
}

void TcpTransmissionItemWidget::setUiEnable(bool enable)
{
    customAddressCheckBox->setEnabled(enable);
    localAddressComboBox->setEnabled(enable);
    localPortLineEdit->setEnabled(enable);
    serverAddressLineEdit->setEnabled(enable);
    serverPortLineEdit->setEnabled(enable);
}
