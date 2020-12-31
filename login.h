#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
//#include <QNetworkReply>
//#include <QNetworkRequest>
//#include <QNetworkAccessManager>
//#include <QDebug>
//#include <QJsonObject>
//#include <QJsonArray>
//#include <QJsonDocument>
#include "networkmanager.h"


namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    NetworkManager *manager;

private slots:
    void on_btnForget_clicked();

    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

    void responsePostResult(QJsonObject result);


private:
    Ui::Login *ui;
};

#endif // LOGIN_H
