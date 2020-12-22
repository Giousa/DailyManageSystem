#include "dbengin.h"
#include <QDebug>


//需要进行初始化，不然关闭时，报异常
static QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");

QSqlDatabase DBEngine::getQSqlDatabase()
{
    qDebug() << "静态方法调用";

    if(!database.open()){
        qDebug() << "连接数据库：：：：：";
        database.setHostName("47.103.115.252");
        database.setPort(3306);
        database.setUserName("root");
        database.setPassword("h5s/X_7FLkzj");
        database.setDatabaseName("qt_db");
        database.open();
    }

    return database;

}

