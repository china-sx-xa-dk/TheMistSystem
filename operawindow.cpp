#include "operawindow.h"
#include "ui_operawindow.h"

#include <QDebug>

#include "deviceinfo.h"
#include "switchcontrol.h"

OperaWindow::OperaWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperaWindow)
{
    ui->setupUi(this);

    SwitchControl *pSwitchControl = new SwitchControl(this);
//    SwitchControl *pGreenSwitchControl = new SwitchControl(this);
//    SwitchControl *pDisabledSwitchControl = new SwitchControl(this);

//    // 设置状态、样式
//    pGreenSwitchControl->setToggle(true);
//    pGreenSwitchControl->setCheckedColor(QColor(0, 160, 230));
//    pDisabledSwitchControl->setDisabled(true);
//    pDisabledSwitchControl->setToggle(true);

    // 连接信号槽
    connect(pSwitchControl, SIGNAL(toggled(bool)), this, SLOT(onToggled(bool)));
}

OperaWindow::~OperaWindow()
{
    delete ui;
}

void OperaWindow::onToggled(bool bChecked)
{
    qDebug() << "State : " << bChecked;
}
