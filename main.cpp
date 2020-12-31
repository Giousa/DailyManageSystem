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

//    FileUtil::setPropertiesConfig("isLogin","true");

//    QString username = FileUtil::getPropertiesConfig("isLogin");
//    qDebug() << username;

//    Login l;
//    Widget w;
//    if("true" == username){
//        qDebug() << "进入Login界面";
//        w.hide();
//        l.show();
//    }else{
//        qDebug() << "进入Main界面";
//        l.hide();
//        w.show();
//    }

    Login l;
    l.show();

    return a.exec();
}
