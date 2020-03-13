#ifndef DBUTILBYSQLITE3_H
#define DBUTILBYSQLITE3_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQueryModel>

class DbUtilBySqlite3 : public QObject
{
    Q_OBJECT
public:
    explicit DbUtilBySqlite3(const QString& strDatabase = "smart.db");
    ~DbUtilBySqlite3();

    //数据库链接信息
    bool createConnection(const QString& strConn);
    //初始化所需的数据表
    //base_config 初始化配置表
    //base_user 用户表
    bool init_table_data();

    QSqlRecord ExecuteRecord(const QString& strQuery);
    QSqlRecord ExecuteRecord(const QString& strQuery, QList<QVariant> lstParameter);
    QSqlRecord ExecuteRecord(const QString& strQuery, QVariant Parameter);

    QSqlQuery ExecuteSqlQuery(const QString& strQuery, QList<QVariant> lstParameter);
    QSqlQuery ExecuteSqlQuery(const QString& strQuery, QVariant Parameter);
    QSqlQuery ExecuteSqlQuery(const QString& strQuery);

    int ExecuteInt(const QString& strQuery);
    int ExecuteInt(const QString& strQuery, QList<QVariant> lstParameter);
    int ExecuteInt(const QString& strQuery, QVariant Parameter);

    bool Execute(const QString& strQuery, QVariant Parameter);
    bool Execute(const QString& strQuery, QList<QVariant> lstParameter);

    QString ExecuteString(const QString& strQuery);

    void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery);
    void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery,
                           QList<QVariant> lstParameter);
    void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery, QVariant Parameter);

private:
    QSqlDatabase m_db;
    QString m_strDatabase;

signals:

};

#endif // DBUTILBYSQLITE3_H
