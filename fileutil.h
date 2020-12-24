#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QObject>

class FileUtil : public QObject
{
    Q_OBJECT
public:
    explicit FileUtil(QObject *parent = nullptr);

    //获取临时存储的账户
    static QString getPropertiesConfig(QString key);

    //存储数据
    static void setPropertiesConfig(QString key,QString value);

signals:

};

#endif // FILEUTIL_H
