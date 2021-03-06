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
#include "SAKBase.hh"


#include <QHostAddress>
#include <QAbstractSocket>
#include <QNetworkInterface>

#ifdef SAK_IMPORT_COM_MODULE
#include <QSerialPort>
#include <QSerialPortInfo>
Q_DECLARE_METATYPE(QSerialPortInfo)
#endif

SAKBase *SAKBase::instance()
{
    if (!_this){
        new SAKBase;
    }

    return SAKBase::_this;
}

SAKBase *SAKBase::_this = nullptr;
SAKBase::SAKBase(QObject *parent)
    :QObject (parent)
{

}

#ifdef SAK_IMPORT_COM_MODULE
void SAKBase::initComComboBox(QComboBox *comboBox)
{
    if (comboBox){
        comboBox->clear();
        QList<QSerialPortInfo> coms = QSerialPortInfo::availablePorts();
        for(auto var:coms){
            comboBox->addItem(var.portName() + " " + var.description(), QVariant::fromValue(var));
        }
    }
}
#endif

#ifdef SAK_IMPORT_COM_MODULE
void SAKBase::initBaudRateComboBox(QComboBox *comboBox)
{
    if (comboBox){
        comboBox->clear();
        QList<qint32> bd = QSerialPortInfo::standardBaudRates();
        for (auto var:bd) {
            comboBox->addItem(QString::number(var), QVariant::fromValue(var));
        }

        comboBox->setCurrentText("9600");
    }
}
#endif

#ifdef SAK_IMPORT_COM_MODULE
void SAKBase::initDataBitsComboBox(QComboBox *comboBox)
{
    if (comboBox){
        comboBox->clear();
        comboBox->addItem(tr("8位"), QVariant::fromValue(QSerialPort::Data8));
        comboBox->addItem(tr("7位"), QVariant::fromValue(QSerialPort::Data7));
        comboBox->addItem(tr("6位"), QVariant::fromValue(QSerialPort::Data6));
        comboBox->addItem(tr("5位"), QVariant::fromValue(QSerialPort::Data5));
    }
}
#endif

#ifdef SAK_IMPORT_COM_MODULE
void SAKBase::initStopBitsComboBox(QComboBox *comboBox)
{
    if (comboBox){
        comboBox->clear();
        comboBox->addItem(tr("1位"), QVariant::fromValue(QSerialPort::OneStop));
#ifdef Q_OS_WINDOWS
        comboBox->addItem(tr("1.5位"), QVariant::fromValue(QSerialPort::OneAndHalfStop));
#endif
        comboBox->addItem(tr("2位"), QVariant::fromValue(QSerialPort::TwoStop));
    }
}
#endif

#ifdef SAK_IMPORT_COM_MODULE
void SAKBase::initParityComboBox(QComboBox *comboBox)
{
    if (comboBox){
        comboBox->clear();
        comboBox->addItem(tr("无校验位"), QVariant::fromValue(QSerialPort::NoParity));
        comboBox->addItem(tr("偶校验"), QVariant::fromValue(QSerialPort::EvenParity));
        comboBox->addItem(tr("奇校验"), QVariant::fromValue(QSerialPort::OddParity));
        comboBox->addItem(tr("SpaceParity"), QVariant::fromValue(QSerialPort::SpaceParity));
        comboBox->addItem(tr("MarkParity"), QVariant::fromValue(QSerialPort::MarkParity));
    }
}
#endif

void SAKBase::initIpComboBox(QComboBox *comboBox)
{
    if (comboBox){
        comboBox->clear();
        QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
        for(auto var:addresses){
            if (var.protocol() == QAbstractSocket::IPv4Protocol) {
                comboBox->addItem(var.toString());
            }
        }
    }
}

void SAKBase::initTextFormatComboBox(QComboBox *comboBox)
{
    if (comboBox){
        comboBox->clear();

        comboBox->addItem(tr("二进制"), Bin);
        comboBox->addItem(tr("八进制"), Oct);
        comboBox->addItem(tr("十进制"), Dec);
        comboBox->addItem(tr("十六进制"), Hex);
        comboBox->addItem(tr("ASCII"), Ascii);
        comboBox->addItem(tr("UTF8"), Hex);
        comboBox->addItem(tr("系统地区"), Local);

        comboBox->setCurrentIndex(4);
    }
}
