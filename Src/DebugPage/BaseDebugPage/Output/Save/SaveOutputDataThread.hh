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
#ifndef SAVEOUTPUTDATATHREAD_HH
#define SAVEOUTPUTDATATHREAD_HH

#include "SaveOutputDataSettings.hh"
#include <QThread>

class SaveOutputDataThread:public QThread
{
    Q_OBJECT
public:
    SaveOutputDataThread(QObject *parent = nullptr);

    void writeDataToFile(QByteArray data, SaveOutputDataSettings::SaveOutputDataParamters parameters);
private:
    void run() final;
};

#endif
