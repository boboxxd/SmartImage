#include "treewidget.h"
#include <QDebug>
#include <QList>
Treewidget::Treewidget(QWidget *parent) : QTreeWidget(parent)
{
    initUI();
    connect(this,&Treewidget::itemPressed,this,&Treewidget::onpressed);
}

void Treewidget::initUI()
{

}

void Treewidget::onpressed(QTreeWidgetItem *item)
{
    emit sendkind(todata(item->text(0)));
}

QString Treewidget::todata(const QString &str)
{
    QString result;
    if(str == "基础")
    {
        result = "jichu";
    }

    if(str == "杆塔")
    {
        result = "ganta";
    }

    if(str == "导地线")
    {
        result = "daodixian";
    }

    if(str == "绝缘子")
    {
        result = "jueyuanzi";
    }

    if(str == "附属设施")
    {
        result = "fushusheshi";
    }

    if(str == "接地")
    {
        result = "jiedi";
    }

    if(str == "大尺寸")
    {
        result = "dachicun";
    }

    if(str == "小尺寸")
    {
        result="xiaochicun";
    }

    if(str == "通道")
    {
        result="tongdao";
    }

    return result;
}
