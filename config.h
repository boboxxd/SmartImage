#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>
class Config
{
public:
    explicit Config();
    ~Config();
    QString path_in(const QString& kind);
    QString path_out(const QString& kind);
    QString frozen_graph_path(const QString& kind);
    float threshold(const QString& kind);
    float score_threshold(const QString& kind);
    int max_num_detections(const QString& kind);
    float tiling_nms_threshold(const QString& kind);
private:
    QSettings *setting;
    void init();
    void add(const QString& kind);
};

#endif // CONFIG_H
