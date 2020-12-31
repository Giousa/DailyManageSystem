#include "login.h"
#include "ui_login.h"
#include "fileutil.h"
#include "widget.h"


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

    //登录

    QMap<QString,QString> params;
    params.insert("phone",username);
    params.insert("password",password);

    //NetworkManager::httpPost("user/loginUserByPassword",params);
    manager = new NetworkManager(this);
    manager->httpPost("user/loginUserByPassword",params);

    connect(manager,&NetworkManager::responsePost,this,&Login::responsePostResult);
//    connect(manager,&NetworkManager::getResult,[=](QJsonObject result){
//        qDebug() << "login2 请求结果：";
//        qDebug() << result;
//    });

}


void Login::responsePostResult(QJsonObject result)
{
    qDebug() << "login 请求结果：";
    qDebug() << result;
    if (!result.isEmpty())
    {
        QJsonValue codeVal = result.value("code");
        QJsonValue dataVal = result.value("data");
        QJsonValue msgVal = result.value("message");

        if (codeVal.toInt() == 0)
        {
            QJsonObject dataObj = dataVal.toObject();
            if(!dataObj.isEmpty()){
                qDebug() << "登录成功";
//                qDebug() << "id = " << dataObj.value("id").toString();
//                qDebug() << dataObj;
                //存储用户登录信息到本地
                FileUtil::setJsonObject("user",dataObj);
                //跳转到首页

                disconnect(manager,&NetworkManager::responsePost,this,&Login::responsePostResult);
                this->close();

                Widget *w = new Widget();
                w->show();


            }
        }else{
            qDebug() << msgVal;
        }
    }
}
