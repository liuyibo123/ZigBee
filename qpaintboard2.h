#ifndef QPAINTBOARD_H
#define QPAINTBOARD_H

#include <QWidget>

class QPaintBoard2 : public QWidget
{
    Q_OBJECT
public:
    explicit QPaintBoard2(QWidget *parent = 0);
    QPaintBoard2(int width,int height,int child_width,int child_height);
    void setStartPoint(QPoint start);
    void setWidth(int width);
    void setHeight(int height);
    void paintEvent(QPaintEvent *e);
    void setPersent(int persent);
    int weight;
private:
    QPainter *paint;
    QPoint startPoint;
    int width;
    int height;
    int persent;
    QPoint A;
    QPoint B;
    QPoint C;
    QPoint D;
    QPoint E;
    QPoint F;
signals:

public slots:
};

#endif // QPAINTBOARD_H
