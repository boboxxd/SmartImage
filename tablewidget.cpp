#include "tablewidget.h"
#include "ui_tablewidget.h"
#include <QDebug>
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <thread>
#include "config.h"
TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWidget)
{
    ui->setupUi(this);
    connect(ui->tableWidget,&TableSubWidget::sendimage,this,&TableWidget::recieceimage);
}

TableWidget::~TableWidget()
{

    delete ui;
}

void TableWidget::initUI()
{
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
}

void TableWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

}

void TableWidget::reciecekind(const QString &kind)
{
    if(this->kind!=kind)
    {
        int num=ui->tableWidget->rowCount();
        for(int i=0;i<=num;i++)
            ui->tableWidget->removeRow(0);
        this->kind=kind;
        ui->tableWidget->loadhistory(kind);
    }
    ui->progressBar->setValue(0);
}

void TableWidget::addentry(int row)
{
    ui->tableWidget->addentry(row);
}


void TableWidget::recieceimage(const QString &image)
{
    emit sendimage1(image);
    Config config;
    QString image2=config.path_out(kind)+"/"+QFileInfo(image).baseName()+"_result.jpg";
    qDebug()<<kind<<"result image:"<<image2;
    if(!image2.isEmpty())
        emit sendimage2(image2);
}

void TableWidget::updatestatuslabel(const QString &str)
{
    ui->statuslabel->setText(QString("has selected %1 :").arg(str));
}

void TableWidget::updateprogress(int present)
{
    ui->progressBar->setValue(present);
}

void TableWidget::threadfinished()
{
    ui->progressBar->setValue(100);
    ui->statuslabel->setText("分析结束");
}
