#include "detectorworker.h"
#include <QDebug>
#include <QFileInfo>
#include <QStringList>
#include <QString>
#include <thread>
#include <QMutexLocker>
#include <QRect>
#include <QDateTime>
#include <QMessageBox>
#include <QDir>

static void mkdir(const QString &path)
{
    QDir dir(path);
    if(!dir.exists())//判断需要创建的文件夹是否存在
    {
        dir.mkdir(path); //创建文件夹
    }
}

DetectorWorker::DetectorWorker(QObject *parent) : QThread(parent)
{
    isrun=false;
    kind="";
}

DetectorWorker::~DetectorWorker()
{
    //qDebug()<<"DetectorWorker::~DetectorWorker()";
    stop();
}

void DetectorWorker::startdetect()
{
    Detector worker;
    for (auto i=0;i<filelist.count();i++)
    {
        QMutexLocker locker(&m_lock);
        result.carInfo.clear();
        filename=filelist.at(i);
        QString name=QFileInfo(filename).baseName();
        image=cv::imread((config.path_in(kind)+"/"+filename).toStdString());
        emit message(QString("detecting %1 ...").arg(filename));
        qDebug()<<"";
        qDebug()<<QString("--- [%1] Start detect %2").arg(i).arg(filename);

        worker.CarDetection(image,&result,0.45,modelname.toStdString(),score_threshold,max_num_detections,tiling_nms_threshold);

        if(result.carInfo.size()!=0)
        {
            alarmmsg();
            save();
        }
        emit message(QString("detecting %1 completed...").arg(filename));
        emit progress((float(i+1)/runcount)*100);
        if(!isrun){
            qDebug()<<"exit from tasks...";
            return;
        }
    }

}

void DetectorWorker::run()
{
    isrun=true;
    startdetect();
}

void DetectorWorker::alarmmsg()
{
    //test
//    AlarmMsg msg;
//    int index=sqlhandle.rowcount();
//    msg.id=++index;
//    msg.name = filename;
//    msg.path = config.path_in(kind);
//    msg.state = "ok";
//    msg.time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//    msg.type = ToTypeString(6);
//    sqlhandle.insertRow(msg.id,msg);
//    qDebug()<<QString("--- Insert {%1,%2,%3,%4,%5,%6} to database").arg(msg.id).arg(msg.path).arg(msg.name)\
//              .arg(msg.time).arg(msg.type).arg(msg.state);
//    cv::putText(image,msg.type.toStdString(),cv::Point(200,200),1, 3, cv::Scalar(0,255,0),3,8,false);
//    cv::Rect rect(200,200,1000,1000);
//    cv::rectangle(image,rect,cv::Scalar(0,255,0),3);
//    emit update(msg.id);

    AlarmMsg lmsg;
    std::vector<CarInfo> carinfo=result.carInfo;
    int index=sqlhandle.rowcount();
    for(auto i=carinfo.begin();i!=carinfo.end();i++)
    {
        AlarmMsg msg;
        //msg.id=++index;
        msg.name = filename;
        msg.path = config.path_in(kind);
        msg.state = "ok";
        msg.time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        msg.type = kind;
        cv::putText(image,msg.type.toStdString(),cv::Point(i->base.x,i->base.y),1, 5, cv::Scalar(0,255,0));
        cv::Rect rect(i->base.x,i->base.y,i->base.width,i->base.height);
        cv::rectangle(image,rect,cvScalar(0,255,0),5);
        lmsg=msg;
    }
    lmsg.id=++index;
    sqlhandle.insertRow(lmsg.id,lmsg);
    emit update(lmsg.id);
    qDebug()<<QString("--- Insert {%1,%2,%3,%4,%5,%6} to database").arg(lmsg.id).arg(lmsg.path).arg(lmsg.name)\
              .arg(lmsg.time).arg(lmsg.type).arg(lmsg.state);
}



void DetectorWorker::recieve(const QString &kind)
{
    this->kind=kind;
    modelname = config.frozen_graph_path(kind);
    path = config.path_out(kind);
    threshold=config.threshold(kind);
    score_threshold=config.score_threshold(kind);
    max_num_detections=config.max_num_detections(kind);
    tiling_nms_threshold=config.tiling_nms_threshold(kind);
}

void DetectorWorker::dowork(bool state)
{
    if(state)
    {
        if(kind.isEmpty())
            return;
        generateFilelist(kind);
        if(runcount<=0)
        {
            QMessageBox::critical(NULL,tr("输入错误"),tr("输入目录为空!"), QMessageBox::Yes);
            return;
        }
        sqlhandle.setdb("./data.db");
        sqlhandle.open();
        sqlhandle.createtable();
        start();
    }else
    {
        stop();
    }
}

void DetectorWorker::stop()
{
    if(isRunning())
    {
        isrun=false;
        this->quit();
        this->wait();
    }
}

void DetectorWorker::save()
{
    mkdir(path);
    QString savename=path+"/"+QFileInfo(filename).baseName()+"_result.jpg";
    cv::imwrite(savename.toStdString(),image);
}

void DetectorWorker::generateFilelist(const QString& kind)
{
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.JPG"<<"*.png"<<"*.jpeg"<<"*.JPEG";
    QStringList files=QDir(config.path_in(kind)).entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    if(files.isEmpty())
    {
        return;
    }
    filelist=files;
    runcount=filelist.count();
}


