#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include "mythread.h"
#include "qdebug.h"
#include <QTimer>
#include <QMultimedia>
#include <QMediaPlayer>
#include<QSound>
#include "waterline.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
     void timerEvent( QTimerEvent *event );
     void showSort(int p1,int p2);
    ~MainWindow();
private slots:

    void slotConnected();
    void dataReceived();
    void slotSend();

    void recive();
//    void timeout();
    void on_accept1_clicked();
    void on_stop1_clicked();
    void on_pushButton_clicked();

private:

    Ui::MainWindow *ui;
    int weight1_ago;
    int weight2_ago;
    int weight1;
    int weight2;
    MyThread mythread;
    QTcpSocket *tcpSocket;
    bool status;
    int port;
    QHostAddress *serverIP;
    int timer_id;

};

#endif // MAINWINDOW_H
