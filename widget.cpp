#include "widget.h"
#include "ui_widget.h"
#include <QPalette>
#include "scrollarea.h"
#include "imagelabel.h"
#include "tablewidget.h"
#include <QScrollBar>
#include <QFileDialog>
#include <QDebug>
#include "config.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Config config;//chu shi hua
    worker=nullptr;
    worker=new DetectorWorker(this);
    initUI();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
    if(worker!=nullptr)
    {
        worker->stop();
        delete worker;
    }
        worker=nullptr;
}

void Widget::onQThreadFinished()
{
    qDebug()<<"ALL Task finished!";
    ui->startbtn->setText("开始分析");
    ui->startbtn->setChecked(false);
}

void Widget::ondowork(bool state)
{
    if(state)
    {
        ui->startbtn->setText("结束分析");
    }else
    {
        ui->startbtn->setText("开始分析");
    }
}

void Widget::initUI()
{
    setWindowTitle(tr(""));
    ui->startbtn->setCheckable(true);
    connect(ui->scrollArea1,&ScrollArea::scaleradio,ui->imagelabel1,&IMageLabel::RecieveScale);
    connect(ui->scrollArea2,&ScrollArea::scaleradio,ui->imagelabel2,&IMageLabel::RecieveScale);
    connect(ui->tablewidget,&TableWidget::sendimage1,ui->imagelabel1,&IMageLabel::RecieveImage);
    connect(ui->tablewidget,&TableWidget::sendimage2,ui->imagelabel2,&IMageLabel::RecieveImage);
    connect(ui->startbtn,&QPushButton::clicked,worker,&DetectorWorker::dowork);
    connect(ui->startbtn,&QPushButton::clicked,this,&Widget::ondowork);
    connect(ui->treeWidget,&Treewidget::sendkind,worker,&DetectorWorker::recieve);
    connect(ui->treeWidget,&Treewidget::sendkind,ui->tablewidget,&TableWidget::updatestatuslabel);
    connect(ui->treeWidget,&Treewidget::sendkind,ui->tablewidget,&TableWidget::reciecekind);
    connect(worker,&DetectorWorker::update,ui->tablewidget,&TableWidget::addentry);
    connect(worker,&DetectorWorker::finished,this,&Widget::onQThreadFinished);
    connect(worker,&DetectorWorker::message,ui->tablewidget,&TableWidget::updatestatuslabel);
    connect(worker,&DetectorWorker::progress,ui->tablewidget,&TableWidget::updateprogress);
    connect(worker,&DetectorWorker::finished,ui->tablewidget,&TableWidget::threadfinished);
}
