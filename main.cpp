#include "widget.h"
#include <QApplication>
#include "dbengin.h"
#include <QDebug>
#include <fileutil.h>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QSqlDatabase db = DBEngine::getQSqlDatabase();
//    QSqlQuery query;
//    QString sql = "select * from ";
//    query.exec(sql);

    FileUtil::setPropertiesConfig("isLogin","true");

    QString username = FileUtil::getPropertiesConfig("isLogin");
    qDebug() << username;

//    if("true" == username){
//        qDebug() << "进入Login界面";
//        Login l;
//        l.show();
//    }else{
//        qDebug() << "进入Main界面";
//        Widget w;
//        w.show();
//    }


    Login l;
    l.show();

    return a.exec();
}
