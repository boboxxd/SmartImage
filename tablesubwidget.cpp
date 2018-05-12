#include "tablesubwidget.h"
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDebug>
#include <tablewidget.h>
#include "config.h"
#include <QVector>
TableSubWidget::TableSubWidget(QWidget *parent) : QTableWidget(parent)
{
    initUI();
    connect(this,&TableSubWidget::itemClicked,this,&TableSubWidget::onPressed);
    sqlhandle.setdb("/home/hhit/xxdcode/build-SmartImage-Desktop_Qt_5_9_4_GCC_64bit-Debug/data.db");
    sqlhandle.open();
    //sqlhandle.createtable();
    qDebug()<<sqlhandle.isopen();

}

void TableSubWidget::initUI()
{
    horizontalHeader()->setFixedHeight(25);
    horizontalHeader()->setDefaultSectionSize(width()/6);
    setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改
    setAlternatingRowColors(true);                        //设置隔一行变一颜色，即：一灰一白
    setSortingEnabled(true);
}

void TableSubWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    horizontalHeader()->setDefaultSectionSize(width()/6);
}

void TableSubWidget::onPressed(QTableWidgetItem *item)
{
    int row = item->row();
    QString name = this->item(row,1)->data(Qt::DisplayRole).toString()+"/"+this->item(row,2)->data(Qt::DisplayRole).toString();
    emit sendimage(name);
}

void TableSubWidget::addentry(int row)
{
    qDebug()<<"update from sql"<<row;
    Config config;
    int widgetrow=this->rowCount();
    this->insertRow(widgetrow);
    AlarmMsg msg=std::move(sqlhandle.queryRow(row-1));
    QTableWidgetItem *item0=new QTableWidgetItem(QString("%1").arg(widgetrow+1));
    QTableWidgetItem *item1=new QTableWidgetItem(msg.path);
    QTableWidgetItem *item2=new QTableWidgetItem(msg.name);
    QTableWidgetItem *item3=new QTableWidgetItem(msg.time);
    QTableWidgetItem *item4=new QTableWidgetItem(msg.type);
    QTableWidgetItem *item5=new QTableWidgetItem(msg.state);
    item0->setTextAlignment(Qt::AlignHCenter);
    item1->setTextAlignment(Qt::AlignHCenter);
    item2->setTextAlignment(Qt::AlignHCenter);
    item3->setTextAlignment(Qt::AlignHCenter);
    item4->setTextAlignment(Qt::AlignHCenter);
    item5->setTextAlignment(Qt::AlignHCenter);
    setItem(widgetrow,0,item0);
    setItem(widgetrow,1,item1);
    setItem(widgetrow,2,item2);
    setItem(widgetrow,3,item3);
    setItem(widgetrow,4,item4);
    setItem(widgetrow,5,item5);
}

void TableSubWidget::loadhistory(const QString &kind)
{
    qDebug()<<"void TableSubWidget::loadhistory(const QString &kind)";

    QVector<AlarmMsg> msgvec = sqlhandle.queryRow(kind);

    for (auto i=msgvec.begin();i!=msgvec.end();i++)
    {
        int widgetrow=this->rowCount();
        this->insertRow(widgetrow);
        AlarmMsg msg=std::move(*i);
        qDebug()<<msg.name;
        QTableWidgetItem *item0=new QTableWidgetItem(QString("%1").arg(widgetrow+1));
        QTableWidgetItem *item1=new QTableWidgetItem(msg.path);
        QTableWidgetItem *item2=new QTableWidgetItem(msg.name);
        QTableWidgetItem *item3=new QTableWidgetItem(msg.time);
        QTableWidgetItem *item4=new QTableWidgetItem(msg.type);
        QTableWidgetItem *item5=new QTableWidgetItem(msg.state);
        item0->setTextAlignment(Qt::AlignHCenter);
        item1->setTextAlignment(Qt::AlignHCenter);
        item2->setTextAlignment(Qt::AlignHCenter);
        item3->setTextAlignment(Qt::AlignHCenter);
        item4->setTextAlignment(Qt::AlignHCenter);
        item5->setTextAlignment(Qt::AlignHCenter);
        setItem(widgetrow,0,item0);
        setItem(widgetrow,1,item1);
        setItem(widgetrow,2,item2);
        setItem(widgetrow,3,item3);
        setItem(widgetrow,4,item4);
        setItem(widgetrow,5,item5);
    }
}
