#include "widget.h"
#include <QApplication>
#include "dbengin.h"
#include <QDebug>
#include <fileutil.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QSqlDatabase db = DBEngine::getQSqlDatabase();
//    QSqlQuery query;
//    QString sql = "select * from ";
//    query.exec(sql);


    qDebug() << "main函数";


    FileUtil::setPropertiesConfig("username","13764503367");

    QString username = FileUtil::getPropertiesConfig("username");
    qDebug() << username;


    Widget w;
    w.show();
    return a.exec();
}
