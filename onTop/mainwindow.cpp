#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <windows.h>
#include <QSettings>
//#include <QDesktopWidget>

QSettings setting("my.ini",QSettings::IniFormat);
int a,b;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->hide();
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    this->setWindowTitle("gun assistant");
    this->resize(48,48);

    //QDesktopWidget *desktop = QApplication::desktop();
    //this->move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);


    if(setting.contains(tr("AboutPos/a")) && setting.contains(tr("AboutPos/b")))
    {
        a = setting.value("AboutPos/a").toInt();
        b = setting.value("AboutPos/b").toInt();
    }else
    {
        setting.beginGroup(tr("AboutPos"));
        setting.setValue("a","659");
        setting.setValue("b","360");
        setting.endGroup();
        a = 659;
        b = 360;
    }

    this->move(a,b);

    this->show();

    pic = QPixmap(":/res/images/sight.png").scaled(48,48);
    mlabel = new QLabel(this);
    mlabel->setGeometry(0,0,48,48);
    mlabel->setPixmap(pic);
    mlabel->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        x1 = event->globalX();
        y1 = event->globalY();
    }
}


/*
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        x2 = event->x();
        y2 = event->y();

    }
}
*/

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    x2 = event->globalX();
    y2 = event->globalY();

    a = a+x2-x1;
    b = b+y2-y1;

    setting.beginGroup(tr("AboutPos"));
    setting.setValue("a",int(a));
    setting.setValue("b",int(b));
    setting.endGroup();

    this->move(a,b);
}
