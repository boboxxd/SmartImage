#ifndef SQLHANDLE_H
#define SQLHANDLE_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVector>
struct AlarmMsg{
    int id;
    QString path;
    QString name;
    QString time;
    QString type;
    QString state;
};

class SqlHandle : public QObject
{
    Q_OBJECT
public:
    explicit SqlHandle(QObject *parent = nullptr);
    void setdb(QString name);
    ~SqlHandle();
    void createtable();
    bool open();
    bool isopen();
    void close();
    int rowcount();
signals:

public slots:
    void insertRow(int row,const AlarmMsg& msg);
    AlarmMsg queryRow(int row);
    QVector<AlarmMsg> queryRow(const QString &kind);
private:
    QSqlDatabase database;
    QSqlQuery *sql_query;
    QString dataname;
};

#endif // SQLHANDLE_H
