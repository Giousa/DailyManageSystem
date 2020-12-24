#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include "fileutil.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    resize(800,600);
    setWindowTitle("登录界面");

    QString isRem = FileUtil::getPropertiesConfig("isRem");
    if("true" == isRem){
        QString username = FileUtil::getPropertiesConfig("username");
        QString password = FileUtil::getPropertiesConfig("password");

        ui->editUsername->setText(username);
        ui->editPassword->setText(password);
        ui->checkBoxRem->setChecked(true);
    }



}

Login::~Login()
{
    delete ui;
}

void Login::on_btnForget_clicked()
{
    qDebug() << "忘记密码";
}

void Login::on_btnRegister_clicked()
{
    qDebug() << "注册用户";
}

void Login::on_btnLogin_clicked()
{
    qDebug() << "点击登录";
    QString username = ui->editUsername->text();
    QString password = ui->editPassword->text();
    bool isRem = ui->checkBoxRem->isChecked();
    qDebug() << "username = " << username;
    qDebug() << "password = " << password;
    qDebug() << "isRem = " << isRem;

    if(username == NULL || username == ""){
        return;
    }

    if(password == NULL || password == ""){
        return;
    }

    if(isRem){
        FileUtil::setPropertiesConfig("username",username);
        FileUtil::setPropertiesConfig("password",password);
        FileUtil::setPropertiesConfig("isRem","true");
    }else{
        FileUtil::setPropertiesConfig("username",NULL);
        FileUtil::setPropertiesConfig("password",NULL);
        FileUtil::setPropertiesConfig("isRem","false");
    }

}
