#include "dbutilbysqlite3.h"

#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
#include<QSqlRecord>

DbUtilBySqlite3::DbUtilBySqlite3(const QString &strDatabase) : m_strDatabase(strDatabase)
{
    createConnection(m_strDatabase);
    //初始化数据
    init_table_data();
}

//析构函数关闭数据库链接
DbUtilBySqlite3::~DbUtilBySqlite3()
{
    m_db.close();
}

bool DbUtilBySqlite3::createConnection(const QString &strConn)
{
    //一个contains判断，如果之前建立了连接，我们就获取连接到的数据库，如果没有建立连接，我们就新建一个数据库
    m_db=QSqlDatabase::contains("qt_sql_default_connection")?QSqlDatabase::database("qt_sql_default_connection")
                                                                      :QSqlDatabase::addDatabase("QSQLITE", "qt_sql_default_connection");
    m_db.setDatabaseName(strConn);
    m_db.setUserName("admin");
    m_db.setPassword("123456");
    //打开数据库
    if (!m_db.open())
    {
        qDebug() << "Open database failed!";
        return false;
    }
    else
    {
        return true;
    }
}

bool DbUtilBySqlite3::init_table_data()
{
    //判定是否需要进行初始化base_config和base_user两张表
    int isInitFlag = ExecuteInt(QString ("select count(*)  from sqlite_master where type='table' and name = 'base_config'"));
    if(isInitFlag == 0)
    {
        QString user_createStr = QString("create table base_user(id INTEGER PRIMARY KEY AUTOINCREMENT ,username varchar(20),password varchar(20))");
        QString user_insertStr = QString("insert into base_user values %1").arg("(NULL, 'admin', 'admin')");
        ExecuteString(user_createStr);
        ExecuteString(user_insertStr);

        QString devices_createStr = QString("CREATE TABLE devices_info_control (device_id INTEGER PRIMARY KEY,device_name varchar(20), address varchar(20),port varchar(20),agreement varchar(20),out varchar(50),relay varchar(20),elevator varchar(20),normal_audio varchar(20),senior_audio varchar(20),default_audio_play varchar(20),specified_audio_play varchar(100))");
        QString devices_insertStr = QString("INSERT INTO main.devices_info_control(device_id,device_name,address,port,agreement, out, relay, elevator, normal_audio, senior_audio, default_audio_play, specified_audio_play) VALUES (1,'初始化全配电路板' ,'192.168.2.3', '23', 'modbus', ',1,2,3,4,5,6,7,8,', ',1,2,', ',0,1,2,', ',0,', ',0,1,2,3,4,5,', ',0,', ',1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,')");
        QString devices_insertStr1 = QString("INSERT INTO main.devices_info_control(device_id,device_name,address,port,agreement, out, relay, elevator, normal_audio, senior_audio, default_audio_play, specified_audio_play) VALUES (2,'初始化全配电路板2' ,'192.168.2.4', '23', 'modbus', ',1,2,3,4,5,6,7,8,', ',1,2,', ',0,1,2,', ',0,', ',0,1,2,3,4,5,', ',0,', ',1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,')");
        QString devices_insertStr2 = QString("INSERT INTO main.devices_info_control(device_id,device_name,address,port,agreement, out, relay, elevator, normal_audio, senior_audio, default_audio_play, specified_audio_play) VALUES (3,'初始化全配电路板3' ,'192.168.2.5', '23', 'modbus', ',1,2,3,4,5,6,7,8,', ',1,2,', ',0,1,2,', ',0,', ',0,1,2,3,4,5,', ',0,', ',1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,')");
        ExecuteString(devices_createStr);
        ExecuteString(devices_insertStr);
        ExecuteString(devices_insertStr1);
        ExecuteString(devices_insertStr2);
    }
    return true;
}

QSqlRecord DbUtilBySqlite3::ExecuteRecord(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.exec();
    return query.record();
}

QSqlRecord DbUtilBySqlite3::ExecuteRecord(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    query.exec();
    return query.record();
}

QSqlRecord DbUtilBySqlite3::ExecuteRecord(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    query.exec();
    return query.record();
}

QSqlQuery DbUtilBySqlite3::ExecuteSqlQuery(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.setForwardOnly(true);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    query.exec();
    return query;
}

QSqlQuery DbUtilBySqlite3::ExecuteSqlQuery(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.setForwardOnly(true);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    query.exec();
    return query;
}

QSqlQuery DbUtilBySqlite3::ExecuteSqlQuery(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.setForwardOnly(false);
    query.prepare(strQuery);
    query.exec();
    return query;
}

int DbUtilBySqlite3::ExecuteInt(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.exec();
    int ID = 0;
    while(query.next())
    {
        ID = query.value(0).toInt();
    }
    return ID;
}

int DbUtilBySqlite3::ExecuteInt(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    query.exec();
    int ID = 0;
    while(query.next())
    {
        ID = query.value(0).toInt();
    }
    return ID;
}

int DbUtilBySqlite3::ExecuteInt(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    query.exec();
    int ID = 0;
    while(query.next())
    {
        ID = query.value(0).toInt();
    }
    return ID;
}

bool DbUtilBySqlite3::Execute(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    return query.exec();
}

bool DbUtilBySqlite3::Execute(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    return query.exec();
}

QString DbUtilBySqlite3::ExecuteString(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.exec();
    QString temp;
    while(query.next())
    {
        temp = query.value(0).toString();
    }
    return temp;
}

void DbUtilBySqlite3::ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    p_queryModel->setQuery(strQuery, m_db);
}

void DbUtilBySqlite3::ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery,
                       QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    p_queryModel->setQuery(query);
}

void DbUtilBySqlite3::ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery,
                                   QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    p_queryModel->setQuery(query);
 }
