#include "widget.h"
#include "ui_widget.h"
#include "dbengin.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    resize(800,600);
    setWindowTitle("管理系统");

    QSqlDatabase db1 = DBEngine::getQSqlDatabase();


}

Widget::~Widget()
{

    delete ui;
}

