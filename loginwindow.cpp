#include "loginwindow.h"
#include "ui_loginwindow.h"

#include<QList>
#include<QVariant>
#include<QSqlRecord>
#include<QDebug>
#include<QSqlQuery>
#include<QMessageBox>
#include<QByteArray>

#include "mainwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    setFixedSize(370, 220);
    ui->setupUi(this);

    //取消按钮
    connect(ui->btn_canel, &QPushButton::clicked, [=](){
        this->close();
    });

    //登陆按钮
    connect(ui->btn_login, &QPushButton::clicked, [=](){
        QString con_username = ui->edit_username->text();
        QString con_password = ui->edit_password->text();
        //校验填入的参数
        if(con_username.length() <= 3 || con_password.length() <= 3)
        {
            QMessageBox::critical(NULL, "填写错误", "账号或密码太短");
        }else
        {
            //封装查询登陆
            QString str_select = QString("SELECT * FROM base_user WHERE username = ? AND password = ? AND id = 1");
            QVariant username(con_username);
            QVariant password(con_password);
            QList<QVariant> lstParameter;
            lstParameter.append(username);
            lstParameter.append(password);

            QSqlQuery query = dbUtil.ExecuteSqlQuery(str_select, lstParameter);
            bool loginFlag = false;
            while(query.next())
            {
                if(query.value(1).toString() == con_username && query.value(2).toString() == con_password)
                {
                    loginFlag = true;
                    break;
                }
            }

            //登陆成功跳转到主页面,登陆失败进行提示
            if(loginFlag){
                this->hide();
                m = new MainWindow(this);
                m->show();
            }
            else
            {
                QApplication::setQuitOnLastWindowClosed(false);
                QMessageBox::critical(NULL, "登陆失败", "账号或密码错误");
                QApplication::setQuitOnLastWindowClosed(true);
            }
        }
    });
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
