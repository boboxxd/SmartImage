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

QString Config::frozen_graph_path(const QString &kind)
{
    return setting->value(kind+"/frozen_graph_path").toString();
}

float Config::threshold(const QString& kind)
{
    return setting->value(kind+"/threshold").toFloat();
}

float Config::score_threshold(const QString& kind)
{
    return setting->value(kind+"/score_threshold").toFloat();
}

int Config::max_num_detections(const QString& kind)
{
    return setting->value(kind+"/max_num_detections").toInt();
}

float Config::tiling_nms_threshold(const QString& kind)
{
    return setting->value(kind+"/tiling_nms_threshold").toFloat();
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
//    int CarDetection(
//		cv::Mat &cv_img,
//		CarResult *car_result,
//		float threshold,
//		string frozen_graph_path,
//		float score_threshold,
//        int max_num_detections,
//        float tiling_nms_threshold);
    setting->setValue(kind+"/input","");
    setting->setValue(kind+"/output","");
    setting->setValue(kind+"/frozen_graph_path","");
    setting->setValue(kind+"/threshold",0.45);
    setting->setValue(kind+"/score_threshold",0.45);
    setting->setValue(kind+"/max_num_detections",5);
    setting->setValue(kind+"/tiling_nms_threshold",0.1);
}
