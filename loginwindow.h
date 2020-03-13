#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

#include "dbutilbysqlite3.h"
#include "mainwindow.h"
#include "operawindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    //初始化数据库和数据交互类
    DbUtilBySqlite3 dbUtil;
    //主窗口初始化
    MainWindow * m;
    OperaWindow operaWin;
    ~LoginWindow();

    quint16 calculate_crc16(quint16 wCRCin,quint16 wCPoly,quint16 wResultXOR,bool input_invert,bool ouput_invert,const char *puchMsg, int usDataLen);

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
