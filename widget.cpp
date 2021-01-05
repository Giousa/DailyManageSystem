#include "widget.h"
#include "ui_widget.h"
#include "dbengin.h"
#include <QMessageBox>
#include "fileutil.h"
#include "workrecord.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "widget 构造方法";

    resize(800,600);
    setWindowTitle("管理系统");

    //获取临时文件中存储的账户信息
    QJsonObject result = FileUtil::getJsonObject("user");
    QString name = result.value("name").toString();
    int gender = result.value("gender").toInt();
    QString headImg = result.value("headImg").toString();
    QString phone = result.value("phone").toString();
    userId = result.value("id").toString();

    //显示
    ui->nameLabel->setText(name);
    QString genderStr;
    if(gender == NULL){
        genderStr = "未知";
    }else if(gender == 1){
        genderStr = "男";
    }else{
        genderStr = "女";
    }
    ui->genderLabel->setText(genderStr);
    ui->phoneLabel->setText(phone);


    managerPic = new NetworkManager(this);
    managerPic->loadUrlPic(headImg);

//    connect(manager,&NetworkManager::responsePic,[=](QPixmap *pix){
//        ui->headLabel->setPixmap(*pix);

//    });

    manager = new NetworkManager(this);

    connect(managerPic,&NetworkManager::responsePic,this,&Widget::responsePicResult);
    connect(manager,&NetworkManager::responsePost,this,&Widget::responsePostResult);
}

Widget::~Widget()
{

    delete ui;
}


void Widget::on_btnSend_clicked()
{
    QString content = ui->textEdit->toPlainText();
    if(content != NULL){

        QJsonObject jsonObject;
        jsonObject.insert("userId",userId);
        jsonObject.insert("content",content);

        manager->httpPostBody("daily-record/addQtDailyRecord",jsonObject);

    }
}

void Widget::responsePostResult(QJsonObject result)
{
    qDebug() << "widget 请求结果：";
    qDebug() << result;
    QMessageBox msgBox;
    if(!result.isEmpty()){
        QJsonValue codeVal = result.value("code");
        if(codeVal.toInt() == 0){
            //成功
            qDebug() << "发送成功";
            ui->textEdit->setText("");
            msgBox.setText("发送成功");
            msgBox.exec();
            return;
        }
    }

    msgBox.setText("发送失败");
    msgBox.exec();

}

void Widget::responsePicResult(QPixmap *pix)
{
    ui->headLabel->setPixmap(*pix);
    disconnect(managerPic,&NetworkManager::responsePic,this,&Widget::responsePicResult);

}

void Widget::on_btnWork_clicked()
{
    this->hide();
    WorkRecord *work = new WorkRecord();
    work->show();

}
