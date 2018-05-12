#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
class Treewidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit Treewidget(QWidget *parent = nullptr);
    void initUI();
signals:
    void sendkind(const QString& kind);
public slots:
    void onpressed(QTreeWidgetItem *item);
private:
    QString todata(const QString& str);
};

#endif // TREEWIDGET_H
