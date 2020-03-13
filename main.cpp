#include "loginwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

#include "dbutilbysqlite3.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //关闭主窗口时触发关闭所有打开的其他窗口
    a.setQuitOnLastWindowClosed(true);

    //添加项目默认样式
    QFile qss(":/common_main.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    LoginWindow w_login;
    w_login.show();
    return a.exec();
}
