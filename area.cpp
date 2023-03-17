#include "area.h"
#include <QPrinter>
void Area::AreaPrint(QWidget *parent,int siz,QVector<double> &vertices,QVector<double> &verticesy,int sizeWindow,QVector<QRgb> Color)
{
color=Color;
sizeArea=sizeWindow-50;
setFixedSize(QSize(sizeWindow+150,sizeWindow+150));

ptr=new MyGraph(siz,vertices,verticesy,sizeWindow-50);
QPrinter printer;
QPainter painter;
painter.begin(&printer);
this->render(&painter);
painter.end();

}
Area::Area(QWidget *parent,int sizeWindow):QWidget(parent)
{
    setFixedSize(QSize(sizeWindow+150,sizeWindow+150));
    sizeArea=sizeWindow-50;
    ptr=nullptr;
}
Area::Area(Area* t)                                                                              //Конструктор с аргументом объекта
{
   sizeArea=t->sizeArea;
   ptr=t->ptr;
}
int Area::RetSize()
{

    return sizeArea;
}
//void Area::showEvent(QShowEvent *)
//{
//myTimer=startTimer(500);                       // создать таймер
//}
void Area::paintEvent(QPaintEvent *)           //Метод раскраски обьекта painter
{
QPainter painter(this);
double get_red=qRed(color.value(0));
double get_green=qGreen(color.value(0));
double get_blue=qBlue(color.value(0));
double red = get_red*qRed(color.value(1))*255+get_green*0*qGreen(color.value(1))+ get_blue*30*qBlue(color.value(1))/(qBlue(color.value(1))+qGreen(color.value(1))+qRed(color.value(1)));
double green = get_red*qRed(color.value(2))*255+get_green*0*qGreen(color.value(2))+get_blue*30*qBlue(color.value(2))/(qBlue(color.value(2))+qGreen(color.value(2))+qRed(color.value(2)));
double blue = get_red*qRed(color.value(3))*255+get_green*0*qGreen(color.value(3))+get_blue*30*qBlue(color.value(3))/(qBlue(color.value(3))+qGreen(color.value(3))+qRed(color.value(3)));
painter.setPen(qRgb(red,green,blue));
if(ptr)
{
ptr->DrawAxis(&painter,sizeArea,sizeArea);     //Рисование  осей
ptr->showfigure(&painter);                     //Рисование графика
}

}
//void Area::timerEvent(QTimerEvent *event)
//{
//if (event->timerId() == myTimer)      // если наш таймер
//{
//update();                            // обновить внешний вид
//}
//else
//QWidget::timerEvent(event);        // иначе передать для стандартной обработки
//}

//void Area::hideEvent(QHideEvent *)
//{
//killTimer(myTimer);                     // уничтожить таймер
//}
Area::~Area()
{
delete ptr;
}
