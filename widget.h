#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "networkmanager.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QString userId;

    NetworkManager *manager;

    NetworkManager *managerPic;


private slots:
    void on_btnSend_clicked();

    void responsePostResult(QJsonObject result);

    void responsePicResult(QPixmap *pix);

    void on_btnWork_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
