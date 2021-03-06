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
#ifndef SAKCHART_HH
#define SAKCHART_HH

#include <QObject>
#include <QPushButton>

class SAKDebugPage;
class MoreChartWidget;
class ThroughputWidget;
class SAKChartManager:public QObject
{
    Q_OBJECT
public:
    SAKChartManager(SAKDebugPage *debugPage, QObject *parent = nullptr);
    ~SAKChartManager();
private:
    SAKDebugPage *_debugPage;

    QPushButton *throughputPushButton;
//    QPushButton *moreChartPushButton;

    ThroughputWidget *throughputWidget;
    MoreChartWidget *moreChartWidget;

    /// 显示吞吐量面板
    void showThroughputPushWidget();
    /// 显示更多图表面板
    void showMoreChartWidget();

    void resetThroughputWidgetPtr();
    void resetMoreChartPushButtonPtr();
};

#endif
