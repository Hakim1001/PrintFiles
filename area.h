#ifndef AREA_H
#define AREA_H
#include <QWidget>
#include <QVector>
#include "figura.h"
class Area : public QWidget
{
QVector<QRgb> color;
int sizeArea;                                                                                                         //Размер графика
//int myTimer;
public:
Area(Area* t);
Area(QWidget *parent,int sizeWindow);
int RetSize();
void AreaPrint(QWidget *parent,int siz,QVector<double> &vertices,QVector<double> &verticesy,int sizeWindow,QVector<QRgb>); //Метод выводящий на печать график
~Area();
MyGraph *ptr;
protected:
void paintEvent(QPaintEvent *event);
//void timerEvent(QTimerEvent *event);
//void showEvent(QShowEvent *event);
//void hideEvent(QHideEvent *event);
};
#endif
