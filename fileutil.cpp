#include "fileutil.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QStandardPaths>


void createFile(QString filePath,QString fileName);

QJsonObject getJsonObjectFromString(const QString jsonString);
QString getStringFromJsonObject(const QJsonObject& jsonObject);


FileUtil::FileUtil(QObject *parent) : QObject(parent)
{

}

QString FileUtil::getPropertiesConfig(QString key)
{
    if(key == NULL){
        qDebug() << "设置数据不能为空";
        return NULL;
    }


    QString deskPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    qDebug() << "文件地址:" << deskPath;

    createFile(deskPath+"/temp/","account.properties");
    QString filePath = deskPath+"/temp/account.properties";
    QFile file(filePath);

    file.open(QIODevice::ReadOnly);

    if(!file.isOpen()){
        qDebug() << "创建文件： "<< filePath;
        file.setFileName(filePath);
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList s = line.split("=");
//         qDebug() << "分隔后:" << s;
//         qDebug() << "字段名称:" << s[0];
        if(s[0] == key){
            qDebug() << "查询到匹配字段";
            return s[1];
        }
    }

    return NULL;
}



void FileUtil::setPropertiesConfig(QString key,QString value)
{

    if(key == NULL){
        qDebug() << "设置数据不能为空";
        return;
    }


    QString deskPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    qDebug() << "文件地址:" << deskPath;

    createFile(deskPath+"/temp/","account.properties");
    QString filePath = deskPath+"/temp/account.properties";
    QFile file(filePath);

//    file.open(QIODevice::ReadWrite);
//    file.open(QIODevice::ReadOnly|QIODevice::WriteOnly);
    file.open(QIODevice::ReadOnly);

    if(!file.isOpen()){
        qDebug() << "创建文件： "<< filePath;
        file.setFileName(filePath);
    }
    //打开文件，查询文件目录，看看是否匹配

    QString newData = NULL;
    //判断key是否存在
    bool isExist = false;
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList s = line.split("=");
//         qDebug() << "分隔后:" << s;
//         qDebug() << "字段名称:" << s[0];
        if(s[0] == key){
            isExist = true;
            qDebug() << "查询到匹配字段";
            //修改字段value值
            QString newLine = QString("%1=%2").arg(key).arg(value);
            newData.append(newLine);
        }else{
           newData.append(line);
        }
        newData.append("\n");
    }

    if(!isExist){
        //插入新的
        QString newLine = QString("%1=%2").arg(key).arg(value);
        newData.append(newLine);
        newData.append("\n");
    }

    qDebug() << "新数据:" << newData;
    qDebug() << "存储数据";

    QFile file2(filePath);
    file2.open(QIODevice::WriteOnly);
    file2.write(newData.toUtf8());

    file.close();
}

void FileUtil::setJsonObject(QString fileName, QJsonObject value)
{

    if(fileName == NULL){
        qDebug() << "文件地址不能为空";
        return;
    }

    QString deskPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    createFile(deskPath+"/temp/",fileName+".json");
    QString filePath = deskPath+"/temp/"+fileName+".json";
    qDebug() << "json文件地址:" << filePath;

    QFile file(filePath);
    file.open(QIODevice::WriteOnly);


    file.write(getStringFromJsonObject(value).toUtf8());

    file.close();

}

QJsonObject FileUtil::getJsonObject(QString fileName)
{
    QJsonObject result;
    if(fileName == NULL){
        qDebug() << "文件地址不能为空";
        return result;
    }


    QString deskPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filePath = deskPath+"/temp/"+fileName+".json";
    qDebug() << "json文件地址:" << filePath;
    QFile file(filePath);

    file.open(QIODevice::ReadOnly);

    QByteArray array = file.readAll();
    result = getJsonObjectFromString(QString(array));

    return result;

}





void createFile(QString filePath,QString fileName)
{
    QDir tempDir;
    //临时保存程序当前路径
    QString currentDir = tempDir.currentPath();
    //如果filePath路径不存在，创建它
    if(!tempDir.exists(filePath))
    {
        qDebug()<<QObject::tr("不存在该路径")<<endl;
        tempDir.mkpath(filePath);
    }
    QFile *tempFile = new QFile;
    //将程序的执行路径设置到filePath下
    tempDir.setCurrent(filePath);
    qDebug()<<tempDir.currentPath();
    //检查filePath路径下是否存在文件fileName,如果停止操作。
    if(tempFile->exists(fileName))
    {
        qDebug()<<QObject::tr("文件存在");
        return ;
    }
    //此时，路径下没有fileName文件，使用下面代码在当前路径下创建文件
    tempFile->setFileName(fileName);
    if(!tempFile->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<QObject::tr("打开失败");
    }
    tempFile->close();
    //将程序当前路径设置为原来的路径
    tempDir.setCurrent(currentDir);
    qDebug()<<tempDir.currentPath();
}


// QString >> QJson
QJsonObject getJsonObjectFromString(const QString jsonString){
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
    if(jsonDocument.isNull() ){
        qDebug()<< "===> QString >> QJson "<< jsonString.toLocal8Bit().data();
    }
    QJsonObject jsonObject = jsonDocument.object();
    qDebug()<< "===> QString >> QJson ";
    return jsonObject;
}
// QJson >> QString
QString getStringFromJsonObject(const QJsonObject& jsonObject){
    qDebug()<< "===> QJson >> QString ";
    return QString(QJsonDocument(jsonObject).toJson());
}
