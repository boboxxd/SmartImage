#include "config.h"
#include <QFileInfo>
#include <QDebug>
static QString storename="config.ini";
Config::Config()
{
    setting = new QSettings(storename,QSettings::IniFormat);
    init();
}

Config::~Config()
{
    delete setting;
}

QString Config::path_out(const QString &kind)
{
    return setting->value(kind+"/output").toString();
}

QString Config::path_in(const QString &kind)
{
    return setting->value(kind+"/input").toString();
}

QString Config::model(const QString &kind)
{
    return setting->value(kind+"/model").toString();
}

void Config::init()
{
    if(QFileInfo(storename).isFile())
        return;

    add("jichu");
    add("ganta");
    add("jueyuanzi");
    add("daodixian");
    add("jiedi");
    add("tongdao");
    add("dachicun");
    add("xiaochicun");
    add("fushusheshi");
}

void Config::add(const QString &kind)
{

    setting->setValue(kind+"/input","");
    setting->setValue(kind+"/output","");
    setting->setValue(kind+"/model","");
}
