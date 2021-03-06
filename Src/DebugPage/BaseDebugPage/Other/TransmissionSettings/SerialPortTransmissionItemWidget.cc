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
#include "SAKBase.hh"
#include "SAKDebugPage.hh"
#include "SerialPortTransmissionItemWidget.hh"
#include "ui_SerialPortTransmissionItemWidget.h"

#include <QDebug>
#ifdef SAK_IMPORT_COM_MODULE
#include <QSerialPortInfo>
Q_DECLARE_METATYPE(QSerialPortInfo)
#endif

SerialPortTransmissionItemWidget::SerialPortTransmissionItemWidget(SAKDebugPage *debugPage, QWidget *parent)
    :BaseTransmissionItemWidget (debugPage, parent)
#ifdef SAK_IMPORT_COM_MODULE
    ,ui (new Ui::SerialPortTransmissionItemWidget)
    ,serialPort (nullptr)
#endif
{    
#ifdef SAK_IMPORT_COM_MODULE
    ui->setupUi(this);
    enableCheckBox              = ui->enableCheckBox;
    handleReceiveDataCheckBox   = ui->handleReceiveDataCheckBox;
    comComboBox                 = ui->comComboBox;
    customBaudrateCheckBox      = ui->customBaudrateCheckBox;
    baudRateComboBox            = ui->baudRateComboBox;
    dataBitscomboBox            = ui->dataBitscomboBox;
    stopBitscomboBox            = ui->stopBitscomboBox;
    parityComboBox              = ui->parityComboBox;

    SAKBase::instance()->initComComboBox(comComboBox);
    SAKBase::instance()->initBaudRateComboBox(baudRateComboBox);
    SAKBase::instance()->initDataBitsComboBox(dataBitscomboBox);
    SAKBase::instance()->initStopBitsComboBox(stopBitscomboBox);
    SAKBase::instance()->initParityComboBox(parityComboBox);

    handleReceiveDataCheckBox->setChecked(true);
#else
    QHBoxLayout *layout = new QHBoxLayout(this);
    QLabel *label = new QLabel("该版本软件不支持数据通过串口转发", this);
    label->setObjectName(QString("label%1fkldfjsdajflsadfjasdf").arg(__LINE__));
    label->setStyleSheet(QString("QLabel#%1{color:red}").arg(label->objectName()));
    label->setAlignment(Qt::AlignHCenter);
    layout->addWidget(label, Qt::AlignHCenter);
    setLayout(layout);
#endif
}

#ifdef SAK_IMPORT_COM_MODULE
SerialPortTransmissionItemWidget::~SerialPortTransmissionItemWidget()
{
    delete ui;
}
#endif

#ifdef SAK_IMPORT_COM_MODULE
void SerialPortTransmissionItemWidget::write(QByteArray data)
{
    if (serialPort){
        if (serialPort->write(data)){
#ifdef QT_DEBUG
            qDebug() << "send data error:" << serialPort->errorString();
#endif
        }
    }
}
#endif

#ifdef SAK_IMPORT_COM_MODULE
void SerialPortTransmissionItemWidget::on_enableCheckBox_clicked()
{
    // c++11 lambda表达式
    auto closeDev = [&](){
        if (serialPort){
            disconnect(serialPort, &QSerialPort::readyRead, this, &SerialPortTransmissionItemWidget::read);
            serialPort->close();
            serialPort->deleteLater();
            serialPort = nullptr;
            this->setUiEnable(true);
        }
    };

    if (enableCheckBox->isChecked()){
        serialPort = new QSerialPort(comComboBox->currentData().value<QSerialPortInfo>());
        serialPort->setBaudRate(baudRateComboBox->currentData().value<qint32>());
        serialPort->setParity(parityComboBox->currentData().value<QSerialPort::Parity>());
        serialPort->setDataBits(dataBitscomboBox->currentData().value<QSerialPort::DataBits>());
        serialPort->setStopBits(stopBitscomboBox->currentData().value<QSerialPort::StopBits>());
        if (serialPort->open(QSerialPort::ReadWrite)){
            this->setUiEnable(false);
            connect(serialPort, &QSerialPort::readyRead, this, &SerialPortTransmissionItemWidget::read, Qt::QueuedConnection);
#ifdef QT_DEBUG
            qInfo() << tr("串口打开成功")
                    << tr("串口名称：") << serialPort->portName()
                    << tr("波特率：") << serialPort->baudRate()
                    << tr("数据位：") << serialPort->dataBits()
                    << tr("校验方式：") << serialPort->parity();
#endif
        }else{
            emit requestOutputMessage(serialPort->errorString(), false);
            enableCheckBox->setChecked(false);
            closeDev();
        }
    }else{
        if (serialPort){
            closeDev();
        }
    }
}
#endif

#ifdef SAK_IMPORT_COM_MODULE
void SerialPortTransmissionItemWidget::on_customBaudrateCheckBox_clicked()
{
    baudRateComboBox->setEditable(customBaudrateCheckBox->isChecked());
}
#endif

#ifdef SAK_IMPORT_COM_MODULE
void SerialPortTransmissionItemWidget::read()
{
    if (serialPort){
        QByteArray data = serialPort->readAll();
        if (!data.isEmpty()){
            if (handleReceiveDataCheckBox->isChecked()){
                emit bytesRead(data);
            }
        }
    }
}
#endif

#ifdef SAK_IMPORT_COM_MODULE
void SerialPortTransmissionItemWidget::setUiEnable(bool enable)
{
    comComboBox->setEnabled(enable);
    customBaudrateCheckBox->setEnabled(enable);
    baudRateComboBox->setEnabled(enable);
    dataBitscomboBox->setEnabled(enable);
    stopBitscomboBox->setEnabled(enable);
    parityComboBox->setEnabled(enable);
}
#endif
