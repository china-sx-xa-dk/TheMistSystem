#include "deviceinfo.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QList>

DeviceInfo::DeviceInfo(int device_id,QString device_name, QString address, int port, QString agreement, QString out, QString relay, QString elevator, QString normal_audio, QString senior_audio, QString default_audio_play, QString specified_audio_play)
{
    this->device_id = device_id;
    this->device_name = device_name;
    this->address = address;
    this->port = port;
    this->agreement = agreement;
    this->out = out;
    this->relay = relay;
    this->elevator = elevator;
    this->normal_audio = normal_audio;
    this->senior_audio = senior_audio;
    this->default_audio_play = default_audio_play;
    this->specified_audio_play = specified_audio_play;
}

DeviceInfo::DeviceInfo()
{

}

DeviceInfo::~DeviceInfo()
{

}

QList<int> DeviceInfo::getDeviceList()
{
    //因为下边使用结果集直接循环,new对象的时候只走一遍程序,无法短时间理解并解决，故使用先获取结果集行数,然后使用for循环完成返回
    //查询数据库设备信息
    QString devicesSel = "SELECT * FROM devices_info_control";
    QSqlQuery query = dbUtil.ExecuteSqlQuery(devicesSel);
    QList<int> l;

    int forSize = 0;
    if (query.last())
    {
        forSize = query.at() + 1;
    }
    for (int i = 0; i < forSize; i++) {
       query.seek(i);
       //返回列表使用的元素下标,下标对应的DeviceInfo在Map中保存可以直接获取
       deivceMap.insert(i, new DeviceInfo(query.value(0).toInt(),
                                                    query.value(1).toString(),
                                                    query.value(2).toString(),
                                                    query.value(3).toInt(),
                                                    query.value(4).toString(),
                                                    query.value(5).toString(),
                                                    query.value(6).toString(),
                                                    query.value(7).toString(),
                                                    query.value(8).toString(),
                                                    query.value(9).toString(),
                                                    query.value(10).toString(),
                                                    query.value(11).toString()));
       l.append(i);
    }

//    query.seek(0);
//    qDebug()<<"结果集大小="<<query.value(1);
//    query.seek(1);
//    qDebug()<<"结果集大小="<<query.value(1);
//    query.seek(2);
//    qDebug()<<"结果集大小="<<query.value(1);


//    if (query.last()) {
//        do {
//            qDebug() << listIndex;
//            deivceMap.insert(listIndex++, new DeviceInfo);
//        } while (query.previous());
//    }
//    while(query.next())
//    {
//        qDebug() << listIndex;
//        d = new DeviceInfo(query.value(0).toInt(),
//                           query.value(1).toString(),
//                           query.value(2).toString(),
//                           query.value(3).toInt(),
//                           query.value(4).toString(),
//                           query.value(5).toString(),
//                           query.value(6).toString(),
//                           query.value(7).toString(),
//                           query.value(8).toString(),
//                           query.value(9).toString(),
//                           query.value(10).toString(),
//                           query.value(11).toString());
//       deivceMap.insert(listIndex++, new DeviceInfo);
//    }

//    qDebug() << "----------------------";
//    qDebug() << deivceMap[0]->device_name;
//    qDebug() << deivceMap[1]->device_name;
//    qDebug() << deivceMap[2]->device_name;
    //对deivceMap进行初始化并且完成插值
    //返回最后的设备列表给外部完成对应关系
    return l;
}
