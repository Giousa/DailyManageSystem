#include "workrecord.h"
#include "ui_workrecord.h"
#include "widget.h"


WorkRecord::WorkRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkRecord)
{
    ui->setupUi(this);

    resize(800,600);
    setWindowTitle("工作日志");

    QJsonObject result = FileUtil::getJsonObject("user");
    QString userId = result.value("id").toString();

    manager = new NetworkManager();
    page = 1;
    size = 10;
    params.insert("userId",userId);
    params.insert("size",QString::number(size));

    requestRecordList();
    connect(manager,&NetworkManager::responseGet,this,&WorkRecord::responseGetResult);

    //表格自适应
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
//    ui->tableWidget->verticalHeader()->setVisible(false); // 隐藏水平header
//    ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection);//设置选中单个
//    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  // 可以选中多个


    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(tableDoubleClicked(int,int)));

}

WorkRecord::~WorkRecord()
{
    delete ui;
}


void WorkRecord::responseGetResult(QJsonObject result)
{
    qDebug() << "workrecord::";
//    qDebug() << result;
    if(!result.isEmpty()){
//        qDebug() << "1";
        QJsonObject data = result.value("data").toObject();
//        qDebug() << "2" << data;
        QJsonArray array = data.value("data").toArray();
//        qDebug() << "3" << array;
//        ui->listWidget->clear();
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject record = array[i].toObject();
            QJsonValue id = record.value("id");
            QJsonValue content = record.value("content");
            QJsonValue createTime = record.value("createTime");

            qDebug() << "id = " << id.toInt() << ",content = "<< content.toString() << ", createTime = " << createTime.toString();
//            QListWidgetItem *item = new QListWidgetItem();
//            ui->listWidget->setItemWidget()
//            QString item = QString("%1   %2").arg(content.toString()).arg(createTime.toString());
//            ui->listWidget->addItem(item);
            QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(id.toInt()));
            QTableWidgetItem *contentItem = new QTableWidgetItem(content.toString());
            QTableWidgetItem *timeItem = new QTableWidgetItem(createTime.toString());
            idItem->setFlags(idItem->flags() & (~Qt::ItemIsEditable));//禁止编辑
            contentItem->setFlags(contentItem->flags() & (~Qt::ItemIsEditable));//禁止编辑
            timeItem->setFlags(timeItem->flags() & (~Qt::ItemIsEditable));//禁止编辑

            ui->tableWidget->setItem(i, 0, idItem);
            ui->tableWidget->setItem(i, 1, contentItem);
            ui->tableWidget->setItem(i, 2, timeItem);


        }
    }

}

void WorkRecord::on_btnBack_clicked()
{
    this->close();
    Widget *w = new Widget();
    w->show();

}

void WorkRecord::on_btnSend_clicked()
{

}


void WorkRecord::on_btnFirst_clicked()
{
    page = 1;
    requestRecordList();

}

void WorkRecord::on_btnPre_clicked()
{
    page--;
    if(page == 0){
        page = 1;
    }
    requestRecordList();
}

void WorkRecord::on_btnNext_clicked()
{
    page++;
    requestRecordList();
}

void WorkRecord::requestRecordList(){
    params.insert("page",QString::number(page));
    manager->httpGet("daily-record/findQtDailyRecordListByPage",params);
}


void WorkRecord::tableDoubleClicked(int x, int y)
{
    qDebug() << "x = " << x << ", y = " << y;
    QTableWidgetItem *item = ui->tableWidget->item(x,0);
    qDebug() << item->text();
}

