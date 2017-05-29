#include "qpaintboard.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "QPaintEvent"
#include "qpoint.h"
#include <QDebug>
QPaintBoard::QPaintBoard(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("监控"));
}
int QPaintBoard::getPersent(){
    return persent;
}
void QPaintBoard::paintEvent(QPaintEvent *){
    startPoint = QPoint(20,30);
    A=startPoint;
    width = this->geometry().width()*2/3;
    height = this->geometry().height()*2/3;
    B=QPoint(A.x(),A.y()+height);
    C=QPoint(A.x()+width/3,B.y()+width/3);
    D=QPoint(C.x()+width/3,C.y());
    E=QPoint(A.x()+width,B.y());
    F=QPoint(E.x(),A.y());
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawLine(startPoint,QPoint(startPoint.x(),startPoint.y()+height));
    painter.drawLine(QPoint(startPoint.x()+width,startPoint.y()),QPoint(startPoint.x()+width,startPoint.y()+height));
    painter.drawEllipse(QPoint(startPoint.x()+width/2,startPoint.y()),width/2,width/8);
    QPainterPath path;
    QPoint c(startPoint.x(),startPoint.y()+height);
    QPoint d(startPoint.x()+width/3,startPoint.y()+height+width/3);
    QPoint e(startPoint.x()+width*2/3,startPoint.y()+height+width/3);
    QPoint f(startPoint.x()+width,startPoint.y()+height);
    path.moveTo(c);
    path.lineTo(d);
    path.lineTo(e);
    path.lineTo(f);
    path.lineTo(c);
    painter.setPen(Qt::blue);
    painter.drawPath(path);
    QBrush brush(QColor(40,150,200));
    painter.fillPath(path,brush);
    painter.drawPath(path);
    QPoint t1(A.x(),B.y()-height*persent/100);
    if(persent<=5){
        painter.setPen(QColor(255,0,0));
    }
    painter.fillRect(t1.x(),t1.y(),width,height*persent/100,brush);
    painter.setPen(QColor(255,0,0));

    double kedu =(double) height/10;
    for(int i=1;i<=10;i++){
        if(i%5==0){
            painter.drawLine(F.x(),F.y()+kedu*i,F.x()+width/5,F.y()+kedu*i);
        }
        else
            painter.drawLine(F.x(),F.y()+kedu*i,F.x()+width/10,F.y()+kedu*i);
    }
}
void QPaintBoard::setPersent(int persent){
    this->persent = persent;
    this->repaint();
}
QPaintBoard::QPaintBoard(int width,int height,int child_width,int child_height){
//    resize(800,600);
    setWindowTitle(tr("监控"));
    this->setFixedWidth(width);
    this->setFixedHeight(height);
    this->setHeight(child_height);
    this->setWidth(child_width);
    this->setAutoFillBackground(true);
}
void QPaintBoard::setHeight(int height){
    this->height = height;
}
void QPaintBoard::setWidth(int width){
    this->width = width;
}
