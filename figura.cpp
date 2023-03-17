
#include <math.h>
#include <array>
#include <vector>
#include <ranges>
#include "figura.h"
#include <QRect>

MyGraph::MyGraph(int siz,QVector<double> &vertices,QVector<double> &verticesy,int sizeWindow):vertices_(siz,3)
{
    sizeGraph=sizeWindow;
    AxisX=(vertices);
    AxisY=(verticesy);
    sizePoint=siz;
    first=vertices[0];
    double max=verticesy[0];
    min=verticesy[0];
    for (int j = 0; j < siz; j++)                                                                                          //Заполнение
    {
  if(max<verticesy[j])
  {
  max=verticesy[j];
  }
    if(min>verticesy[j])
    {
        min=verticesy[j];
    }
    }

    vertx=(vertices[sizePoint-1]-vertices[0])/sizeWindow;
    verty=(max-min)/sizeWindow;

    for (int j = 0; j < siz; j++)        //Заполнение
    {
        vertices_[j][0] = ((vertices[j]-first)/vertx);
        vertices_[j][1] = ((verticesy[j]-min)/verty);
        vertices_[j][2] = 1;
    }
    // Translate(-50,-50);
     Translate(0, sizeWindow);
     Rotate(180,sizeWindow);

    // Scaling(1,1);
    // scale((double)(sizePoint/700));
     Translate(0,-50);
//     for (int j = 0; j < siz; j++)        //Заполнение
//     {
//         vertices_[j][0] =vertices_[j][0]/7;
//         vertices_[j][1] =vertices_[j][1]/7 ;
//         vertices_[j][2] = 1;
//     }
}
void MyGraph::scale(double factor)
{
    std::array<float, 3> c{};
    matrix &v = vertices_;
    for (uint8_t i = 0; i < 3; i++)                //calculating the mass center
    {
        for (auto &row : vertices_)
        {
            c[i] += row[i];
        }

        c[i] /= v.size();
    }


  for(int i = 0; i < vertices_.size(); i++)
  {
    //this is a vector that leads from mass center to current vertex

    vertices_[i][0] = c[0] + factor * (vertices_[i][0]-c[0]);
    vertices_[i][1] = c[1] + factor * (vertices_[i][1]-c[1]);

}
}
void MyGraph::Draw(QPainter *Painter)                                                     //Метод рисования обьекта и данных на графике по осям
{
    QDateTime time = QDateTime::fromTime_t(AxisX[0]);
    QString t=time.toString();
    int i=0;
    for(int j = 0; j<= sizeGraph;j=j+t.length()*5)
    {

      QRect r = QRect(j, sizeGraph+40, 80, 80);
      QDateTime timeX = QDateTime::fromTime_t(j*vertx+first);
      QString t_X=timeX.toString();
      QRect r_y = QRect(0, 50+sizeGraph-(i), 80, 80);
      Painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, t_X);
      Painter->drawLine(50+j,50+sizeGraph,50+j,40+sizeGraph);
      Painter->drawText(r_y, Qt::AlignLeft | Qt::TextWordWrap,QString::number(i*verty+min) );
      Painter->drawLine(50,50+sizeGraph-i,60,50+sizeGraph-i);
      i=i+t.length()*5;
    }

    for (int j = 0; j+1 < sizePoint; j++)        //Заполнение
    {

        Painter->drawLine(vertices_[j][0],vertices_[j][1], vertices_[j+1][0], vertices_[j+1][1]);
    }


//Painter->drawText ( 20, 50, 10, 5,Qt::AlignHCenter, " 100" );
//     qDebug()<<AxisX[1];
//QDateTime time = QDateTime::fromTime_t(AxisX[1]);
//QString t=time.toString();
// qDebug()<<"t.length():";
// qDebug()<<sizeGraph/(t.length()*5);
//QRect r = QRect(0, 200, 80, 80);
//Painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, t);


}
void MyGraph::DrawAxis(QPainter *Painter,int y,int x)                                   //Рисование осей
{
     //Painter->drawLine(50,50,x+50,50);//Верхняя ось OX
       Painter->drawLine(50+0,0+50,50+0,y+50);                                //Ось OY и стрелки
       Painter->drawLine(50+x,y-20+50,50+ x+50, y+50);
       Painter->drawLine(50+x,y+50,50+ x+50, y+50);
       Painter->drawLine(50+x,y+20+50,50+x+50, y+50);
       Painter->drawLine(50+0,y+50,50+ x, y+50);                              //Нижняя ось OX и стрелки
       Painter->drawLine(30,50,50,0);
       Painter->drawLine(50,0,50,50);
       Painter->drawLine(50,0,50+20,50);

}
void MyGraph::showfigure(QPainter *Painter)
{
Draw(Painter);
}
void MyGraph::Translate(float x, float y)                                     //Матрица преобразования транспонирования
{
    matrix translation
    {
        { 1, 0, 0 },
        { 0, 1, 0 },
        { x, y, 1 },
    };
    vertices_ = vertices_ * translation;

}
void MyGraph::Scaling(float x, float y)                                       //Матрица преобразования транспонирования

{
    matrix translation
    {
        { x, 0, 0 },
        { 0, y, 0 },
        { 0, 0, 1 },
    };
    vertices_ = vertices_ * translation;

}
void MyGraph::Rotate(float ang,int sizeWindow)                                //Матрица поворота координат на угол ang
{
    ang *=3.14159265 / 180;

    float s = sin(ang);
    float c = cos(ang);

    matrix rotation
    {
        { c, s, 0 },
        { -s, c, 0 },
        { 0, 0, 1 },
    };
    float offset_x = (sizeWindow+50)/2;//(int)(50+vertices_[sizePoint-1][0]-vertices_[0][0])/2;
    float offset_y = sizeWindow+50;
    Translate(-offset_x, -offset_y);
    vertices_ = vertices_ * rotation;
    Translate(offset_x, offset_y);
}

