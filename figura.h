#ifndef figura_h
#define figura_h
#include <QtGui>
#include "matrix.h"
#include <array>
#include <vector>
#include <ranges>
#include <QString>
#include <QTextStream>
#include <QDate>
#include <QTime>
using namespace std;
class MyGraph
{
public:
    MyGraph(int siz,QVector<double> &vertices,QVector<double> &verticesy,int sizeWindow);
    void DrawAxis(QPainter *Painter,int y,int x);
    void showfigure(QPainter *Painter);
    void Draw(QPainter *Painter);
    void Translate(float x, float y);
    void Scaling(float x, float y);
    void Rotate(float ang,int sizeWindow);
    void scale(double factor);

private:
    double vertx;
    double verty;
    double min;
    double first;
    int sizeGraph;
    int sizePoint;
    matrix vertices_;
    QVector<double> AxisX;
    QVector<double> AxisY;
};


#endif
