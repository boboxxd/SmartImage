#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>
class Config
{
public:
    explicit Config();
    ~Config(){delete setting;}
    QString path_in(const QString& kind);
    QString path_out(const QString& kind);
    QString model(const QString& kind);
private:
    QSettings *setting;
    void init();
    void add(const QString& kind);
};

#endif // CONFIG_H
