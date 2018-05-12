#ifndef DETECTORWORKER_H
#define DETECTORWORKER_H
#include "sqlhandle.h"
#include <QThread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <DangerousVehicle_detector.h>
#include <config.h>
#include <QMutex>

using namespace car;

class DetectorWorker : public QThread
{
    Q_OBJECT
public:
     DetectorWorker(QObject *parent = nullptr);
    void startdetect();
    void run();
    void alarmmsg();
signals:
    void update(int row);
    void message(const QString& msg);
    void progress(int present);
public slots:
    void recieve(const QString& kind);
    void dowork(bool state);
    void stop();
private:
    void save();
    void generateFilelist(const QString& kind);

private:
    cv::Mat image;
    CarResult result;
    QString kind;
    QString filename;
    QString path;
    QString modelname;
    Config config;
    QStringList filelist;
    QMutex m_lock;
    int runcount;
    SqlHandle sqlhandle;
public:
    bool isrun;
};

#endif // DETECTORWORKER_H
