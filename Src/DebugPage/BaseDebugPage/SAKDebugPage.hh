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
#ifndef SAKTABPAGE_HH
#define SAKTABPAGE_HH

#include <QSize>
#include <QTimer>
#include <QLabel>
#include <QMutex>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QDateTime>
#include <QMetaEnum>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QTextBrowser>

#include "SAKCRCInterface.hh"
#include "ReadWriteSettingsWidget.hh"
#include "AutoResponseSettingWidget.hh"

class SAKDataFactory;
class SAKChartManager;
class SAKCRCInterface;
class SAKOtherSettings;
class SAKStatisticsManager;
class TransmissionSettings;
class DebugPageInputManager;
class DebugPageOutputManager;
class HighlightSettingsWidget;

namespace Ui {
    class SAKDebugPage;
}

class SAKDebugPage : public QWidget
{
    Q_OBJECT
public:
    SAKDebugPage(QWidget *parent = Q_NULLPTR);
    ~SAKDebugPage();

public:
    /**
     * @brief write             -- 写数据
     * @param data              -- 待写的数据
     */
    void write(QByteArray data);

    /**
     * @brief writeRawData      -- 写数据
     * @param rawData           -- 代写数据（特殊格式字符串，未经过处理）
     * @param textFormat        -- SAKBase::SAKTextFormat，文本格式
     */
    void writeRawData(QString rawData, int textFormat);

    /// 输出内部信息
    void outputMessage(QString msg, bool isInfo = true);

signals:
    /// 读取数据后发射该信号，参数为已读取的数据
    void bytesRead(QByteArray data);
    /// 发送数据后发射该信号，参数为已发送的数据
    void bytesWritten(QByteArray data);
    /// 子类关联该信号来发送数据即可
    void writeDataRequest(QByteArray data);
    /// 子类设备状态发生改变时(是否就绪)发送该信号
    void deviceStatusChanged(bool ready);
signals:
    void writeRawDataRequest(QString data, int textFormat);

    /*
     * 读写参数
     */
public:
    struct ReadWriteParameters {
        int waitForBytesWrittenTime;
        int waitForReadyReadTime;
    };

    struct ReadWriteParameters readWriteParameters();
    void setReadWriteParameters(struct ReadWriteParameters parameters);
private:
    struct ReadWriteParameters _readWriteParameters;
    QMutex readWriteParametersQMutex;


protected:
    /**
     * @brief openOrColoseDevice    -- 打开或者关闭设备
     */
    virtual void openOrColoseDevice();
    /**
     * @brief refreshDevice         -- 刷新设备
     */
    virtual void refreshDevice();
    /**
     * @brief controllerWidget  -- 安装控制面板
     */
    virtual QWidget *controllerWidget();
    /**
     * @brief setUpController -- 安装控制器（控制面板）
     */
    void setUpController();
    /**
     * @brief changedDeviceStatus   -- 设备打开或者关闭时执行该函数
     * @param opened                -- true: 设备一打开 false：设备已关闭
     */
    void changedDeviceStatus(bool opened);
private:
    QTimer clearInfoTimer;
    void cleanInfo();

private:
    /// 日志类型
    const char *logCategory = "SAKDebugPage";


    // ------------------------------------------------------------------------
    // 设备设置
protected:    
    QPushButton *refreshPushButton              = nullptr;  // 刷新按钮
    QPushButton *switchPushButton               = nullptr;  // 打开关闭设备按钮
    QFrame      *deviceSettingFrame             = nullptr;  // 控制面板
private slots:
    void on_refreshPushButton_clicked();
    void on_switchPushButton_clicked();

     // 输入设置组
protected:
    QComboBox   *inputModelComboBox             = nullptr;  // 输入模式预选框
    QCheckBox   *cycleEnableCheckBox            = nullptr;  // 循环使能复选框
    QLineEdit   *cycleTimeLineEdit              = nullptr;  // 循环周期输入框
    QPushButton *readinFilePushButton           = nullptr;  // 读入文件按钮
    QPushButton *saveInputDataPushButton        = nullptr;  // 保存发送输入框数据
    QCheckBox   *addCRCCheckBox                 = nullptr;  // 发送数据添加crc校验
    QCheckBox   *bigeEndianCheckBox             = nullptr;  // crc值以大端形式添加
    QPushButton *clearInputPushButton           = nullptr;  // 清空输入框按钮
    QPushButton *sendPushButton                 = nullptr;  // 发送数据按钮
    QTextEdit   *inputTextEdit                  = nullptr;  // 数据输入框
    QComboBox   *crcParameterModelsComboBox     = nullptr;  // crc计算参数模型
    QLabel      *crcLabel                       = nullptr;  // crc显示标签
    QPushButton *addInputItemPushButton;
    QPushButton *deleteInputItemPushButton;
    QListWidget *inputDataItemListWidget;
    QPushButton *presetPushButton;
    QPushButton *sendPresetPushButton;


    //数据输出组管理
protected:
    QLabel *infoLabel                           = nullptr;  // 消息输标签

    // 消息输出组
protected:
    QLabel      *rxLabel                        = nullptr;  // 接受指示灯
    QLabel      *txLabel                        = nullptr;  // 发送指示灯
    QComboBox   *outputModelComboBox            = nullptr;  // 输出模式复选框
    QCheckBox   *showDateCheckBox               = nullptr;  // 显示日期使能复选框
    QCheckBox   *autoWrapCheckBox               = nullptr;  // 自动换行使能复选框
    QCheckBox   *showTimeCheckBox               = nullptr;  // 显示时间使能复选框
    QCheckBox   *showMsCheckBox                 = nullptr;  // 显示毫秒使能复选框
    QCheckBox   *showRxDataCheckBox             = nullptr;  // 显示接收数据使能复选框
    QCheckBox   *showTxDataCheckBox             = nullptr;  // 显示发送数据使能复选框
    QCheckBox   *saveOutputFileToFilecheckBox   = nullptr;  // 使能输出数据保存
    QPushButton *outputFilePathPushButton       = nullptr;  // 显示输出设置面板
    QPushButton *clearOutputPushButton          = nullptr;  // 清空输出按钮
    QPushButton *saveOutputPushButton           = nullptr;  // 保存输出按钮
    QTextBrowser *outputTextBroswer             = nullptr;  // 用于输出显示收发的数据

    // 图表
protected:
    QPushButton *throughputPushButton;
    QPushButton *moreChartPushButton;

    // 数据统计
protected:
    bool        receivedFlag                    = false;    // 接受状态指示灯
    bool        sendFlag                        = false;    // 接受指示灯状态

    QLabel      *rxSpeedLabel;
    QLabel      *txSpeedLabel;
    QLabel      *rxFramesLabel;
    QLabel      *txFramesLabel;
    QLabel      *rxBytesLabel;
    QLabel      *txBytesLabel;
    QPushButton *resetTxCountPushButton;
    QPushButton *resetRxCountPushButton;

private:
    SAKChartManager         *chartManager;
    SAKOtherSettings        *otherSettings;
    SAKStatisticsManager    *statisticsManager;
    DebugPageOutputManager  *outputManager;
    DebugPageInputManager   *debugPageInputManager;

private:
    /**
     * @brief ui    -- 界面文件
     */
    Ui::SAKDebugPage *ui = nullptr;

    /**
     * @brief initUiPointer -- 初始化指向ui控件的数据成员（指针）
     */
    void initUiPointer();    
public:
    friend class SAKChartManager;
    friend class SAKOtherSettings;
    friend class SAKStatisticsManager;
    friend class DebugPageInputManager;
    friend class DebugPageOutputManager;
};

#endif  // SAKTabPage_H
