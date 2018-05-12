#ifndef TABLESUBWIDGET_H
#define TABLESUBWIDGET_H

#include <QTableWidget>
#include "sqlhandle.h"
class TableSubWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableSubWidget(QWidget *parent = nullptr);
    void initUI();
    void resizeEvent(QResizeEvent *event);

signals:
    void sendimage(const QString& name);
public slots:
    void onPressed(QTableWidgetItem *item);
    void addentry(int row);
    void loadhistory(const QString& kind);
private:
    SqlHandle sqlhandle;
};

#endif // TABLESUBWIDGET_H
