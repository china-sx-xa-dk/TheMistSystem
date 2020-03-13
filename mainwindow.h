#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dbutilbysqlite3.h"
#include "deviceinfo.h"
#include "operawindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //设备类
    DeviceInfo deviceInfo;

    //设备操作面板初始化
    OperaWindow operaWin;

    //刷新三个配置信息
    void refreshConfig();
    //发送消息给指定peizhi
    void sendMsg();

    //初始化设备列表
    void initDeviceList();

private slots:
    void on_actionquit_triggered();

    void on_btnSend_clicked();

    void on_btnClearHistory_clicked();

    void on_btnClearSend_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
