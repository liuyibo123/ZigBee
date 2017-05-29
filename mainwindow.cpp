#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpaintboard.h"
#include "waterline.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);
    setWindowTitle(tr("智能医疗"));
    weight1_ago = 0;
    weight2_ago = 0;
    weight1 = 0;
    weight2 = 0;
    ui->listWidget->setPersent(0);
    ui->listWidget1->setPersent(0);
    showSort(0,0);
    status = false;
    port = 20000;
    serverIP = new QHostAddress("192.168.1.99");
}

MainWindow::~MainWindow()
{
    delete ui;

}

//void MainWindow::on_pushButton_clicked()
//{
//      tcpSocket = new QTcpSocket(this);

//      connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
//      connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
//      timer = new QTimer(this);
//      timer->setInterval(5000);
//      connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
//      tcpSocket->connectToHost(*serverIP,port);
//      status =true;


////    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
////    mythread.setPortnum("com3");
////    QByteArray byte;
////    connect(&this->mythread,SIGNAL(comRecive()),this,SLOT(recive()));
////    mythread.start();
//}
//void MainWindow::timeout(){
//        int temp1 = weight1;
//        int temp2 = weight2;
//        qDebug()<<weight2_ago;
//       if(weight1_ago!=0){
//           int resttime1 = temp1 * 5/(weight1_ago-temp1);
//           int min1 = resttime1/60;
//           int sec1 = resttime1%60;
//           QString time1 = min1+":"+sec1;
//           ui->time1->setText(time1);
//       }
//       if(weight2_ago!=0){
//           int resttime2 = temp2 * 5/(weight2_ago-temp2);
//           int min2 = resttime2/60;
//           int sec2 = resttime2%60;
//           QString time2 = QString::number(min2,10);
//           time2.append(":");
//           QString sec2_string = QString::number(sec2,10);
//           time2.append(sec2_string);

//           ui->time2->setText(time2);
//           int uiweight = weight2_ago;
//           qDebug()<<temp2;
//           qDebug()<<uiweight;
//           qDebug()<<resttime2;
//           qDebug()<<min2;
//           qDebug()<<sec2;
//           qDebug()<<time2;

//       }
////       weight1_ago = temp1;
//            weight2_ago = temp2;
//}
void MainWindow::timerEvent( QTimerEvent *event )

{

    int temp1 = weight1;
    int temp2 = weight2;
    qDebug()<<weight2_ago;
       if(weight1_ago!=0&&((weight1_ago-temp1)!=0)){
           int resttime1 = temp1 * 180/(weight1_ago-temp1);
           int min1 = resttime1/60;
           int sec1 = resttime1%60;
          QString time1 = min1+":"+sec1;
           ui->time1->setText(time1);
       }
   if(weight2_ago!=0&&((weight2_ago-temp2)!=0)){
       int resttime2 = temp2 * 180/(weight2_ago-temp2);
       int min2 = resttime2/60;
       int sec2 = resttime2%60;
       QString time2 = QString::number(min2,10);
       time2.append(":");
       QString sec2_string = QString::number(sec2,10);
       time2.append(sec2_string);

       ui->time2->setText(time2);
       int uiweight = weight2_ago;
       qDebug()<<temp2;
       qDebug()<<uiweight;
       qDebug()<<resttime2;
       qDebug()<<min2;
       qDebug()<<sec2;
       qDebug()<<time2;

   }
//       weight1_ago = temp1;
        weight2_ago = temp2;

}
/*
 * 串口的接收部分
*/
void MainWindow::recive(){
//    QString str;
//    char tmp[100];
//    char *buf;
//    char var;
//    str = tr(mythread.requestData.data());
//    qDebug()<<str;

//    int a = str.toInt();
//    qDebug()<<a;

//    int c = a%100;
//    qDebug()<<c;
//    ui->listWidget->setPersent(c);
//    mythread.requestData.clear();
}
void MainWindow::slotConnected(){
    ui->accept1->setEnabled(false);
    qDebug()<<"连接成功";
}
void MainWindow::slotSend(){

}
/*
 * 断开连接
*/
//void MainWindow::on_pushButton_2_clicked()
//{
//    tcpSocket->disconnectFromHost();
//    qDebug()<<"断开连接";
//    status = false;
//}
/*
 * socket数据接收
 * 刘宜博
*/
void MainWindow::dataReceived(){
    while (tcpSocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());
        tcpSocket->read(datagram.data(),datagram.size());
        QString msg = datagram.data();
        int msg_int = msg.toInt();
        int id = msg_int/1000000000;
        int state = msg_int/100000000%10;
        int persent = msg_int/100000%1000;
        int weight = msg_int/10%10000;
        int warning = msg_int%10;
        qDebug()<<msg_int;
        qDebug()<<id;
        qDebug()<<state;
        qDebug()<<persent;
        qDebug()<<weight;
        if(state==1)
            return;
        switch (id) {
            case 1:
                ui->listWidget1->setPersent(persent);
                showSort(persent,ui->listWidget->getPersent());
                if(persent<=5){
                        QMediaPlayer *player = new QMediaPlayer;
                        player->setMedia(QUrl("qrc:/Sound/warning.mp3"));
                       player->setVolume(30);
                       player->play();
                }
                if(warning ==1){
                    QMediaPlayer *player = new QMediaPlayer;
                    player->setMedia(QUrl("qrc:/Sound/warning.mp3"));
                    player->setVolume(30);
                    player->play();
                    QMessageBox::warning(this,"警报",QString::number(id).append("号病人呼叫"));
                }
                weight1 = weight;
                break;
            case 2:
                ui->listWidget->setPersent(persent);
                showSort(persent,ui->listWidget1->getPersent());
                if(persent<=5){
                        QMediaPlayer *player = new QMediaPlayer;
                      player->setMedia(QUrl("qrc:/Sound/warning.mp3"));
                       player->setVolume(30);
                       player->play();
                }
                if(warning ==1){
                    QMediaPlayer *player = new QMediaPlayer;
                    player->setMedia(QUrl("qrc:/Sound/warning.mp3"));
                   player->setVolume(30);
                   player->play();
                    QMessageBox::warning(this,"警报",QString::number(id).append("号病人呼叫"));

                }
                weight2 = weight;
                break;
        }

    }
}


void MainWindow::on_accept1_clicked()
{
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));

//      connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
    tcpSocket->connectToHost(*serverIP,port);
    timer_id=startTimer(3*60*1000);
    status =true;
}

void MainWindow::on_stop1_clicked()
{
    tcpSocket->disconnectFromHost();
    killTimer(timer_id);
    qDebug()<<"断开连接";
    status = false;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::warning(this,"警报",QString::number(1).append("号病人呼叫"));
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/Sound/warning.mp3"));
   player->setVolume(30);
   player->play();
}
void MainWindow::showSort(int p1,int p2){
    if(p1<=p2){
        ui->id1->setText("1");
        ui->id2->setText("2");
        ui->p1->setText(QString::number(p1).append("%"));

        ui->p2->setText(QString::number(p2).append("%"));
    }
    else if(p1>p2){
        ui->id1->setText("2");
        ui->id2->setText("1");
        ui->p1->setText(QString::number(p2).append("%"));
        ui->p2->setText(QString::number(p1).append("%"));
    }

}
