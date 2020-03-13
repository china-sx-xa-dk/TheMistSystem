#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QObject>
#include "dbutilbysqlite3.h"

class DeviceInfo : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInfo(int device_id,QString device_name, QString address,int port,QString agreement,QString out,QString relay,QString elevator,QString normal_audio,QString senior_audio,QString default_audio_play,QString specified_audio_play);
    explicit DeviceInfo();

    ~DeviceInfo();
    //  数据库链接
    DbUtilBySqlite3 dbUtil;

    //  属性
    int device_id;  //  设备id
    QString device_name;    //  设备名称
    QString address;    //  访问设备ip地址
    int port;   //  访问设备端口
    QString agreement;  //  访问协议
    QString out;    //  out 1-8 0:输出0v 1输出12v
    QString relay;  //  relay 1-2 0:断开 1:闭合
    QString elevator;   //  elevator控制 1 0:停止 1:升/正转 2:降/反转
    QString normal_audio;   //  音频常规 默认0 此位无意义
    QString senior_audio;   // 音频高级 1-5 根据文档
    QString default_audio_play; //  默认目录播放 1-16 默认0 此位无意义
    QString specified_audio_play;   // 特定目录曲目播放 1-16

    QMap<int, DeviceInfo *> deivceMap;

    //设置选中的设备信息
    DeviceInfo * chooseDevice = NULL;

    //  获取设备信息列表
    QList<int> getDeviceList();

signals:

};

#endif // DEVICEINFO_H
