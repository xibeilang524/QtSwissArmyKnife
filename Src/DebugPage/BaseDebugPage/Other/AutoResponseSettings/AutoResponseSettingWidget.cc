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
#include "AutoResponseItemWidget.hh"
#include "AutoResponseSettingWidget.hh"
#include "ui_AutoResponseSettingWidget.h"

#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include <QDomElement>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>

AutoResponseSettingWidget::AutoResponseSettingWidget(SAKDebugPage *debugPage, QWidget *parent)
    :QWidget (parent)
    ,_debugPage (debugPage)
    ,ui (new Ui::AutoResponseSettingWidget)
{
    ui->setupUi(this);
    listWidget = ui->listWidget;
    forbidAllCheckBox = ui->forbidAllCheckBox;
    deleteItemPushButton = ui->deleteItemPushButton;
    addItemPushButton = ui->addItemPushButton;
    msgLabel = ui->msgLabel;

    setWindowTitle(tr("自动回复设置"));

    clearMessageInfoTimer.setInterval(5*1000);
    connect(&clearMessageInfoTimer, &QTimer::timeout, this, &AutoResponseSettingWidget::clearMessage);
}

AutoResponseSettingWidget::~AutoResponseSettingWidget()
{
    delete ui;
}

void AutoResponseSettingWidget::on_forbidAllCheckBox_clicked()
{
    for(int i = 0; i < listWidget->count(); i++){
        QListWidgetItem *item = listWidget->item(i);
        QWidget *widget = listWidget->itemWidget(item);
        bool disAble = forbidAllCheckBox->isChecked();
        reinterpret_cast<AutoResponseItemWidget*>(widget)->setAllAutoResponseDisable(disAble);
    }
}

void AutoResponseSettingWidget::on_deleteItemPushButton_clicked()
{
    QListWidgetItem *item = listWidget->currentItem();
    if (!item){
        outputMessage(tr("未选择行，请选择要删除的行后重试"), false);
        return;
    }

    listWidget->removeItemWidget(item);
    delete item;
}

void AutoResponseSettingWidget::on_addItemPushButton_clicked()
{
    QListWidgetItem *item = new QListWidgetItem(listWidget);
    listWidget->addItem(item);
    AutoResponseItemWidget *itemWidget = new AutoResponseItemWidget(_debugPage, listWidget);
    item->setSizeHint(QSize(itemWidget->width(), itemWidget->height()));
    listWidget->setItemWidget(item, itemWidget);
}


void AutoResponseSettingWidget::outputMessage(QString msg, bool isInfo)
{
    QString color = "black";
    if (!isInfo){
        color = "red";
        QApplication::beep();
    }
    msgLabel->setStyleSheet(QString("QLabel{color:%1}").arg(color));

    msgLabel->setText(QTime::currentTime().toString("hh:mm:ss ") + msg);
    clearMessageInfoTimer.start();
}

void AutoResponseSettingWidget::clearMessage()
{
    clearMessageInfoTimer.stop();
    msgLabel->clear();
}
