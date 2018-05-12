#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "detectorworker.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void closeEvent(QCloseEvent *event);
public slots:
    void onQThreadFinished();
    void ondowork(bool state);
private:
    Ui::Widget *ui;
    DetectorWorker *worker;
    void initUI();
};

#endif // WIDGET_H
