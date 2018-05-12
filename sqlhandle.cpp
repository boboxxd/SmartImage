#include "sqlhandle.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>

SqlHandle::SqlHandle(QObject *parent) : QObject(parent)
{
    sql_query=nullptr;
}

void SqlHandle::setdb(QString name)
{
    dataname=name;
}

SqlHandle::~SqlHandle()
{
    if(sql_query!=nullptr)
    {
        delete sql_query;
        sql_query=nullptr;
    }
    database.close();
}

void SqlHandle::createtable()
{
    if(!isopen())
    {
        open();
    }
    database.setDatabaseName(dataname);
    QString create_sql ="create table alarminfo (id int primary key,path varchar(100),name varchar(30), time varchar(30) ,type varchar(30),state varchar(30))";
    sql_query->prepare(create_sql); //创建表
    if(!sql_query->exec()) //查看创建表是否成功
    {
        qDebug()<<QObject::tr("Table Create failed");
        qDebug()<<sql_query->lastError();
    }
    else
    {
        qDebug()<<QObject::tr("Table Create successful!");
    }
}

bool SqlHandle::open()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      database = QSqlDatabase::database("qt_sql_default_connection");
    else
      database = QSqlDatabase::addDatabase("QSQLITE");
     database.setDatabaseName(dataname);
    if (!database.open())
    {
        QString error=QString("Error: Failed to connect database!");
        QMessageBox::critical(NULL,"数据库错误", error, QMessageBox::Yes);
        return false;
    }
    else
    {
        qDebug()<<"open database successful!";
        sql_query=new QSqlQuery(dataname);
        return true;
    }
    return false;
}

bool SqlHandle::isopen()
{
    return database.isOpen();
}

void SqlHandle::close()
{
    if(sql_query!=0)
    {
        sql_query=0;
    }
    database.close();
}

int SqlHandle::rowcount()
{
    int count = 0;
    sql_query->exec("SELECT count(*) from alarminfo");
    sql_query->next();
    count = sql_query->value(0).toInt();
    return count;
}

void SqlHandle::insertRow(int row,const AlarmMsg& msg)
{
    if (!database.isOpen())
    {
        open();
    }
    QString insert_sql = "insert into alarminfo values(?,?,?,?,?,?)";    //插入数据
    sql_query->prepare(insert_sql);

    QVariantList Id;
    Id.append(row);
    QVariantList Path;
    Path.append(msg.path);
    QVariantList Name;
    Name.append(msg.name);
    QVariantList Time;
    Time.append(msg.time);
    QVariantList Type;
    Type.append(msg.type);
    QVariantList State;
    State.append(msg.state);
    sql_query->addBindValue(Id);
    sql_query->addBindValue(Path);
    sql_query->addBindValue(Name);
    sql_query->addBindValue(Time);
    sql_query->addBindValue(Type);
    sql_query->addBindValue(State);
    if(!sql_query->execBatch())
    {
        qDebug()<<sql_query->lastError();
    }
    else
    {
        qDebug()<<"插入记录成功";
    }
}


AlarmMsg SqlHandle::queryRow(int row)
{
    sql_query->exec("select * from alarminfo");
    sql_query->seek(row);
    QSqlRecord record = sql_query->record();
    AlarmMsg msg;
    msg.id = record.value("id").toInt();
    msg.path=record.value("Path").toString();
    msg.name = record.value("Name").toString();
    msg.time = record.value("Time").toString();
    msg.type = record.value("Type").toString();
    msg.state = record.value("State").toString();
    return msg;
}

QVector<AlarmMsg> SqlHandle::queryRow(const QString &kind)
{
    QVector<AlarmMsg> msgvec;
    QString query_sql = QString("select * from alarminfo where type = '%1'").arg(kind);    //插入数据
    if(!sql_query->exec(query_sql))
    {
        qDebug()<<sql_query->lastError();
    }
    while(sql_query->next())
    {
        AlarmMsg msg;
        msg.id = sql_query->value("id").toInt();
        msg.path=sql_query->value("Path").toString();
        msg.name = sql_query->value("Name").toString();
        msg.time = sql_query->value("Time").toString();
        msg.type = sql_query->value("Type").toString();
        msg.state = sql_query->value("State").toString();
        msgvec.append(msg);
    }
    return msgvec;
}
