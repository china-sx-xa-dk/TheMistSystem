#ifndef OPERAWINDOW_H
#define OPERAWINDOW_H

#include <QWidget>

#include "deviceinfo.h"

namespace Ui {
class OperaWindow;
}

class OperaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OperaWindow(QWidget *parent = nullptr);
    ~OperaWindow();

    //初始化设备信息
    DeviceInfo * deviceInfo;

private slots:
    void onToggled(bool bChecked);

private:
    Ui::OperaWindow *ui;
};

#endif // OPERAWINDOW_H
