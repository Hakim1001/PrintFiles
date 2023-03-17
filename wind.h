#ifndef WIND_H
#define WIND_H
#include <iostream>
#include <string>
#include <QtSql>
#include <QFileDialog>
#include <QBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QValidator>
#include <QVariant>
#include <QWidget>
#include <QtGui>
#include "area.h"
#include <QString>
#include <QTextStream>
#include <QDate>
#include <QTime>
#include <locale>
#include <QPrinter>
using namespace std;
class Win: public QWidget
{
Q_OBJECT
protected:
QFrame *frame;
QTextCodec *codec;
Area* area;
QPushButton * MulticolorButton;   // кнопка Цветной график
QPushButton * Non_coloredButton;   // кнопка Цветной график
QPushButton *fileButton;          // кнопка Выбора директории файла
QString color="Color";

public:
Win(QWidget *parent = 0);
void GenerateException(string);
void ExeptionBlock(QString,QString,string);
void Color_Paint();
public slots:
void colored();
void non_colored();
void begin(); // метод начальной настройки интерфейса
};
#endif // WIND_H
