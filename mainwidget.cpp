#include "mainwidget.h"
#include "qpaintboard.h"
MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    resize(1200,800);
    this->setWindowTitle(tr("点滴监控系统"));

}

