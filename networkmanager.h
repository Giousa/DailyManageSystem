#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QtDebug>
#include <QPixmap>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

//    QNetworkAccessManager *manager;

    void httpGet(QString url,QMap<QString,QString> params);

    void httpPost(QString url,QMap<QString,QString> params);

    void httpPostBody(QString url,QJsonObject jsonObject);

    void loadUrlPic(QString url);




signals:

    void responseGet(QJsonObject result);

    void responsePost(QJsonObject result);

    void responsePic(QPixmap *pix);

};

#endif // NETWORKMANAGER_H
