#include "widget.h"
#include <QApplication>
#include "dbengin.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = DBEngine::getQSqlDatabase();

    qDebug() << "main函数";

    Widget w;
    w.show();
    return a.exec();
}
