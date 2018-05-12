#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
namespace Ui {
class TableWidget;
}

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = 0);
    ~TableWidget();
    void initUI();
    void loadtosql(const QString& image);
    void closeEvent(QCloseEvent *event);

public slots:
    void reciecekind(const QString& kind);
    void addentry(int row);
    void recieceimage(const QString& image);
    void updatestatuslabel(const QString &str);
    void updateprogress(int present);
    void threadfinished();
signals:
    void sendimage1(const QString &image);
    void sendimage2(const QString &image);
private:
    Ui::TableWidget *ui;
    QStringList filelist;
    QString kind;
public:


};

#endif // TABLEWIDGET_H
