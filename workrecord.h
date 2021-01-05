#ifndef WORKRECORD_H
#define WORKRECORD_H

#include <QWidget>
#include "fileutil.h"
#include "networkmanager.h"

namespace Ui {
class WorkRecord;
}

class WorkRecord : public QWidget
{
    Q_OBJECT

public:
    explicit WorkRecord(QWidget *parent = nullptr);
    ~WorkRecord();

    NetworkManager *manager;

    QMap<QString,QString> params;

    int page;

    int size;

    void requestRecordList();


private slots:
    void on_btnSend_clicked();

    void responseGetResult(QJsonObject result);

    void on_btnBack_clicked();

    void on_btnFirst_clicked();

    void on_btnPre_clicked();

    void on_btnNext_clicked();

    void tableDoubleClicked(int x,int y);

private:
    Ui::WorkRecord *ui;
};

#endif // WORKRECORD_H
