#ifndef CRC16UTIL_H
#define CRC16UTIL_H

#include <QObject>

class CRC16Util : public QObject
{
    Q_OBJECT
public:
    explicit CRC16Util();
    ~CRC16Util();

    //进行CRC16位加密码   返回值是一个int数组指针 有CRC16验证码 两位
    QList<QByteArray> getCRC16(int sBuffer[1024], int usDataLen);

signals:

};

#endif // CRC16UTIL_H
