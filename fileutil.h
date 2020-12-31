#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class FileUtil : public QObject
{
    Q_OBJECT
public:
    explicit FileUtil(QObject *parent = nullptr);

    //获取临时存储的账户
    static QString getPropertiesConfig(QString key);

    //存储数据
    static void setPropertiesConfig(QString key,QString value);



    //本地存储QJsonObject数据
    static void setJsonObject(QString fileName,QJsonObject value);


    //本地获取QJsonObject数据
    static QJsonObject getJsonObject(QString fileName);

signals:

};

#endif // FILEUTIL_H
