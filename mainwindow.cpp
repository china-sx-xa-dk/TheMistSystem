#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>
#include<QTime>
#include<QSqlQuery>
#include<QKeyEvent>
#include<QMessageBox>
#include<QWidget>
#include<QList>
#include "deviceinfo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initDeviceList();

    //设备信息初始化
    DeviceInfo * d = new DeviceInfo();
    d->getDeviceList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMsg()
{
    //获取发送框内容
    QString content = ui->textEdit->toPlainText();
    if(content == "" || content == NULL)
    {
        return;
    }

    //封装当前时间
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd HH:mm:ss");
    //构建发送内容
//    QString sendContent = QString("%1 \n 发送至(%4 %2:%3) : %5;\n").arg(current_date).arg(this->address).arg(this->port).arg(this->agreement).arg(content);

//    ui->textBrowser->append(sendContent);
    ui->textEdit->clear();
}

//在初始化设备列表
void MainWindow::initDeviceList()
{
    ui->tableWidget->setColumnCount(1); //设置列数
    QStringList sListHeader;
    sListHeader << "设备列表";
    ui->tableWidget->setHorizontalHeaderLabels(sListHeader);
    QFont font = ui->tableWidget->horizontalHeader()->font(); //先获取字体
    font.setBold(true); //字体设置为粗体
    ui->tableWidget->horizontalHeader()->setFont(font); //设置每一列的标题字体为粗体
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择模式，选择单行
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50); //设置行高
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);//禁止鼠标拖动缩放行高度
//    ui->tableWidget->setRowHeight(1, 35);//设置第一行高度
//    ui->tableWidget->setRowHidden(1, true);//隐藏第一行
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(10); //设置行高
    ui->tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    ui->tableWidget->setShowGrid(false); //设置不显示格子线
    ui->tableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  //可多选（Ctrl、Shift、  Ctrl+A都可以）

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->tableWidget->horizontalHeader()->resizeSection(0,150); //设置表头第一列的宽度为150
    ui->tableWidget->horizontalHeader()->setFixedHeight(25); //设置表头的高度
    ui->tableWidget->setStyleSheet("selection-background-color:red;"); //设置选中背景色
//    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

    //初始化信号槽
    //从数据库中获取获取信号槽的数据
    QList<int> ls = deviceInfo.getDeviceList();
    ui->tableWidget->setRowCount(ls.size());//设置展示的总行数
    for (int i = 0; i < ls.size() ; i++) {
        QTableWidgetItem * item = new QTableWidgetItem(deviceInfo.deivceMap[i]->device_name,QTableWidgetItem::Type);
        ui->tableWidget->setItem(i, 0, item);
    }
//    QTableWidgetItem * item = new QTableWidgetItem("设备1",QTableWidgetItem::Type);
//    ui->tableWidget->setItem(0, 0, item);

    //函数指针完成的参数的传递
    void (QTableWidget:: * kehaixing)(int, int) = &QTableWidget::cellDoubleClicked;
    //设置双击信号槽
    connect(ui->tableWidget, kehaixing , [=](int row, int col){
        //封装选中的设备信息
        deviceInfo.chooseDevice = deviceInfo.deivceMap[row];
        //显示设备操作面板
        if(deviceInfo.chooseDevice != NULL){
            //关闭最后一个窗口关闭退出程序的问题
            QApplication::setQuitOnLastWindowClosed(false);
            operaWin.show();
        }
    });
}

//退出关闭
void MainWindow::on_actionquit_triggered()
{
    this->close();
}

//发送按钮
void MainWindow::on_btnSend_clicked()
{
    sendMsg();
}

//清除历史信息
void MainWindow::on_btnClearHistory_clicked()
{
    ui->textBrowser->clear();
}

//清除发送信息
void MainWindow::on_btnClearSend_clicked()
{
    ui->textEdit->clear();
}
