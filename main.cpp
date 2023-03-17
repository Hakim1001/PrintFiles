
#include <QtSql>
#include <QTableView>
#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
//#include "win.h"
#include "wind.h"
#include <iostream>
#include <functional>
#include <cstdlib>
#include <memory>
#include <map>

using namespace std;
int main(int argc, char *argv[])
{
QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); //изменения
QApplication app(argc, argv);

Win win;
//cout<<siz;
win.show();
return app.exec();
}



//#include <QCoreApplication>
// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*

Получение кода типа;

Прежде чем мы сможем безопасно сохранить способ получения класса,
подписывающегося на определенный интерфейс, мы должны выделить для этого код типа.

В предложенной реализации  реализации контейнера IOC  есть статическая целочисленная переменная,
которая определяет идентификатор следующего типа, который будет выделен,
и экземпляр статической локальной переменной для каждого типа,
к которому можно обратиться, вызвав метод GetTypeID.
*/

//class IOCContainer

//{

//    static int s_typeId;
//public:
//    //one typeid per type

//    template<typename T>
//    static int GetTypeID()
//    {

//        static int typeId = s_typeId++;
//        return typeId;
//    }

//    /*
//     Получение экземпляров объекта;

//     Теперь, когда  есть идентификатор типа, мы должны иметь возможность хранить какой-то фабричный объект,
//     чтобы показать тот факт, что мы не знаем, как создать объект.(так как мы не знаем как создать объект)

//     Хранить все фабрики в одной коллекции, для этого выбираем абстрактный базовый класс,
//     из которого будут производиться фабрики, и реализацию, которая захватывает функтор для последующего вызова.
//     Можно использовать std :: map для хранения фабрик,та же можно рассмотреть  другие варианты для эффективности.

//    */
//    class FactoryBase

//    {

//    public:

//        virtual ~FactoryBase() {}

//    };

//    //todo: consider sorted vector

//    map<int, shared_ptr<FactoryBase>> factories;

//    template<typename T>

//    class CFactory : public FactoryBase

//    {
//        //std::function
//        std::function<std::shared_ptr<T>()> functor;
//    public:
//        ~CFactory() {}

//        CFactory(std::function<std::shared_ptr<T>()> functor)

//            :functor(functor)

//        {

//        }

//        std::shared_ptr<T> GetObject()
//        {
//            return functor();
//        }

//    };

//    template<typename T>

//    std::shared_ptr<T> GetObject()

//    {

//        auto typeId = GetTypeID<T>();
//        auto factoryBase = factories[typeId];
//        auto factory = std::static_pointer_cast<CFactory<T>>(factoryBase);
//        return factory->GetObject();
//    }

//    /*
//    Регистрация экземпляров
//    */

//    //Базовая реализация - регистрация функтора

//    template<typename TInterface, typename ...TS>
//    void RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)> functor)
//    {
//        factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>([=] {return functor(GetObject<TS>()...); });
//    }

//    //Регистрация экземпляра объекта
//    template<typename TInterface>
//    void RegisterInstance(std::shared_ptr<TInterface> t)
//    {
//        factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>([=] {return t; });
//    }

//    //Работаем с указателем на функцию
//    template<typename TInterface, typename ...TS>
//    void RegisterFunctor(std::shared_ptr<TInterface>(*functor)(std::shared_ptr<TS> ...ts))
//    {
//        RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)>(functor));
//    }


//    //Фабрика, которая будет вызывать необходимый конструктор для каждого экземпляра
//    template<typename TInterface, typename TConcrete, typename ...TArguments>
//    void RegisterFactory()
//    {
//        RegisterFunctor(
//            std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments> ...ts)>(
//                [](std::shared_ptr<TArguments>...arguments) -> std::shared_ptr<TInterface>
//        {
//            return std::make_shared<TConcrete>(std::forward<std::shared_ptr<TArguments>>(arguments)...);
//        }));

//    }


//    //Фабрика, которая будет возвращать один экземпляр  объекта  для каждого вызова
//    template<typename TInterface, typename TConcrete, typename ...TArguments>
//    void RegisterInstance()
//    {
//        RegisterInstance<TInterface>(std::make_shared<TConcrete>(GetObject<TArguments>()...));
//    }
//};

//IOCContainer gContainer;

////Иницализация не нулевым значением


//int IOCContainer::s_typeId = 121;


////Здесь, примеры различных интерфесов, классов

//class ISomeObjX

//{

//public:

//    virtual ~ISomeObjX() { }

//    virtual void TestMethodX() = 0;

//};



//class ObjX : public ISomeObjX

//{

//public:

//    ObjX()

//    {

//    }

//    void TestMethodX()

//    {

//        std::cout << "This is ObjX" << std::endl;

//    }

//};

//class IAmAThing

//{

//public:

//    virtual ~IAmAThing() { }

//    virtual void TestThis() = 0;

//};



//class IAmTheOtherThing

//{

//public:

//    virtual ~IAmTheOtherThing() { }

//    virtual void TheOtherTest() = 0;

//};



//class TheThing : public IAmAThing

//{

//public:

//    TheThing()

//    {

//    }

//    void TestThis()

//    {

//        std::cout << "A Thing" << std::endl;

//    }

//};

//class TheOtherThing : public IAmTheOtherThing
//{

//    std::shared_ptr<IAmAThing> m_thing;

//public:

//    TheOtherThing(std::shared_ptr<IAmAThing> thing) :m_thing(thing)

//    {

//    }

//    void TheOtherTest()

//    {

//        m_thing->TestThis();

//    }

//};

//class Icolor
//{
//public:
//   virtual ~Icolor(){};
//   virtual void Paint_Grath()=0;

//};
//class Multicolor_Color:public Icolor
//{
//public:
//    void Paint_Grath()
//    {


//    }

//};


//class Non_Colored:public Icolor
//{
//public:
//    void Paint_Grath()
//    {


//    }

//};








//class Graph
//{
//private:
//   IGraphView *graph;
//   Icolor *color;
//public:
//   Graph(IGraphView *a, Icolor *b)
//   {
//      graph=a;
//      color=b;
//   }
//   void PrintGraph()
//   {


//   }

//};

//class BuildGraph
//{
//public:
//    Graph Get_Graph()
//    {



//    }


//};

//class IType
//{
//    virtual void Read()=0;
//    ~IType(){};
//};


//class TypeA
//{
//private:
//    int siz;
//    string *time_ptr;
//    double *value;
//public:
//    TypeA(QSqlQuery ptr)
//    {

//        ptr.exec("SELECT Value,Time from humidity_moscow");
//        int numberOfRows = 0;
//        if(ptr.last())
//        {
//         numberOfRows =  ptr.at() + 1;
//         ptr.first();
//         ptr.previous();
//        }
//        siz=numberOfRows;
//        QVector<double> x(siz),y(siz);
//        uint tr;
//        int i=0;
//        QDateTime Time;
//        double max=0;
//        while (ptr.next()) {
//        double Value = ptr.value(0).toDouble();
//        QVariant strTime =  ptr.value(1).toString();
//        QString time_format = "dd.MM.yyyy  hh:mm";
//         QDateTime dateTime = QDateTime::fromString(strTime.toString(),"dd.MM.yyyy hh:mm");
//         //dateTime.setTimeSpec(Qt::LocalTime);
//     qDebug()<<strTime;
//     qDebug()<<dateTime;
//    tr=dateTime.toTime_t ();
//    uint ptr=dateTime.toTime_t();
//        x[i]=(uint)ptr;
//         qDebug()<<dateTime.toString();
//        //mlabel[i]=Time;
//        //time_ptr[i]=Time.toStdString();
//        y[i]=(uint)Value;
//        qDebug()<<y[i];
//       //qDebug()<<tr;
//        //qDebug()<<x[i];
//        if(i==0)
//        {
//            max=y[i];
//        }
//        if(max<y[i])
//        {
//         max=y[i];

//        }
//        i++;
//        //qDebug()<<"Value";
//        }
//     cPlot.setGeometry(300,300,300,300);
//         // генерируем данные

//         // создаем график и добавляем данные:
//         cPlot.addGraph();
//         cPlot.graph(0)->setData(x, y);
//         QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
//         cPlot.xAxis->setTicker(dateTimeTicker);
//         dateTimeTicker->setTickCount(12);
//         dateTimeTicker->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);
//         // задаем обозначения осей координат:
//         cPlot.xAxis->setLabel("x");
//         cPlot.yAxis->setLabel("y");
//         dateTimeTicker-> setDateTimeFormat ("dd.MM.yyyy  hh:mm");
//         // устанавливаем диапазоны отображения данных:
//         cPlot.xAxis->setRange(x[0], x[siz-1]);
//         cPlot.yAxis->setRange(0, max);
//         cPlot.replot();
//    //     frame = new QFrame(this);
//    //     frame->setFrameShadow(QFrame::Raised);
//    //     frame->setFrameShape(QFrame::Panel);
//         QVBoxLayout *vLayout1 = new QVBoxLayout();
//         vLayout1->addWidget(&cPlot);
//         vLayout1->addStretch();
//        //QVBoxLayout *vLayout2 = new QVBoxLayout();
//        //  vLayout2->addStretch();
//         QHBoxLayout *hLayout = new QHBoxLayout(this);
//         hLayout->addWidget(&cPlot);













//        ptr.exec("SELECT Value,Time from humidity_moscow");
//        int numberOfRows = 0;
//        if(ptr.last())
//        {
//            numberOfRows =  ptr.at() + 1;
//            ptr.first();
//            ptr.previous();
//        }
//        siz=numberOfRows;

//time_ptr=new string[numberOfRows];
//value=new double[numberOfRows];
//int i=0;
//        while (ptr.next()) {
//           double Value = ptr.value(0).toDouble();
//           QString Time = ptr.value(1).toString();
//           time_ptr[i]=Time.toStdString();
//           value[i]=Value;
//           i++;
//          }

//    }
//    void Read()
//    {
//        for(int i=0;i<siz-1;i++)
//        {

//            cout<<time_ptr[i];
//            cout<<value[i];
//        }

//    }
//~TypeA()
//    {
//    delete []time_ptr;
//    delete []value;
//    }
//};


//class IGraphView
//{
//public:
//    virtual ~IGraphView(){};
//    virtual void showfigure(QPainter *Painter,IType *p)=0;
//    virtual void Data_Type_function()=0;
//};

//class LineGraphType:public IGraphView
//{

//public:
//    void showfigure(QPainter *Painter,IType *p)
//    {
//       Draw(Painter);
//    }
//    void Draw(QPainter *Painter,IType *p)
//    {
//        // some print with type data


//    }

//    void Data_Type_function()
//{


//}


//};


//class IRepository
//{
//public:

//    virtual string Print_Graph()=0;
//    virtual void Get_Data(string)=0;
//    virtual void Color()=0;


//};

//class Lite_Database_Repository : public IRepository
//{
//private:
//     TypeA *b;
//     QSqlQuery query;
//     QCustomPlot cPlot;
//public:
//    string Print_Graph()
//    {


//        return "I am saving data to Database.";
//    }
//    void Get_Data(string p)
//    {
//        QString pathToDB = QDir::currentPath()+QString(p.c_str());
//        QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
//        dbase.setDatabaseName(pathToDB);
//        QFileInfo checkFile(pathToDB);
//          if (checkFile.isFile())
//          {
//        if (!dbase.open())
//        {


//            qDebug() << "Что-то не так с соединением!";
//        }
//        else
//        {
//        dbase.open();
//        b=new TypeA(query);
//        }
//          }
//    }
//    void Color()
//    {}
//};

//class TextRepository : public IRepository
//{
//public:
//    string Print_Graph()
//    {
//        return "I am saving data to TextFile.";
//    }
//};

//class PurchaseBl
//{
// private:
//      IRepository* _repository;
// public:
//     PurchaseBl(IRepository *repository)
//    {
//        _repository = repository;
//    }

//    string SavePurchaseOrder()
//    {
//        return _repository->Save();
//    }
//};


//int main()
//{

//  gContainer.RegisterFactory<IAmTheOtherThing, TheOtherThing, IAmAThing>();

//    //Создание зависимости
//    // IRepository *dbRepository = new Repository();

//  //Внедрение зависимости
//  // PurchaseBl purchaseBl(dbRepository);
//  // cout<<purchaseBl.SavePurchaseOrder()<<endl;

//  IRepository *textRepository = new Lite_Database_Repository();

//  //Внедрение зависимости
//  PurchaseBl purchaseBlT(textRepository);
//  cout<<purchaseBlT.SavePurchaseOrder()<<endl;



// // gContainer.RegisterInstance<IRepository, Repository>();
//  gContainer.RegisterInstance<IRepository, Lite_Database_Repository>();

//  cout<<"From Container"<<endl;
//  string ptr="C:\\HUMIDITY_MOSCOW.sqlite";
//  cout<<gContainer.GetObject<IRepository>()->Get_Data(ptr)<<endl;

//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
