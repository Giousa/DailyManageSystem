#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    resize(800,600);
    setWindowTitle("登录界面");

}

Login::~Login()
{
    delete ui;
}
