////#include <QMainWindow>
//#include "win.h"
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
//    //Фабрика, которая будет возвращать один экземпляр  объекта  для каждого вызова
//    template<typename TInterface1, typename TConcrete1,typename TInterface2, typename TConcrete2, typename ...TArguments>
//    void RegisterInstance()
//    {
//        RegisterInstance<TInterface1>(std::make_shared<TConcrete1>(GetObject<TArguments>()...));
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








////class Graph
////{
////private:
////   IGraphView *graph;
////   Icolor *color;
////public:
////   Graph(IGraphView *a, Icolor *b)
////   {
////      graph=a;
////      color=b;
////   }
////   void PrintGraph()
////   {


////   }

////};

////class BuildGraph
////{
////public:
////    Graph Get_Graph()
////    {



////    }


////};

//class IType
//{
//    public:
//    virtual void Read(QSqlQuery query)=0;
//    virtual ~IType(){};
//};


//class TypeA: public IType
//{
//public:
//    void Read(QSqlQuery query)
//    {

////        query.exec("SELECT Value,Time from humidity_moscow ORDER BY 'YYYY.MM.DD HH:MM'");
////        int numberOfRows = 0;
////        if(query.last())
////        {
////         numberOfRows =  query.at() + 1;
////         query.first();
////         query.previous();
////        }
////        siz=numberOfRows;


////        x=QVector<double>(siz);
////        y=QVector<double>(siz);
////        uint tr;
////        int i=0;
////        QDateTime Time;
////        double max=0;
////        while (query.next()) {
////        double Value = query.value(0).toDouble();
////        QVariant strTime =  query.value(1).toString();
////        QString time_format = "yyyy.MM.dd  hh:mm";
////         QDateTime dateTime = QDateTime::fromString(strTime.toString(),"dd.MM.yyyy hh:mm");
////         //dateTime.setTimeSpec(Qt::LocalTime);
////    tr=dateTime.toTime_t ();
////    uint ptr=dateTime.toTime_t();


////   //x[i]=((ptr-first_x)/(siz));
////        x[i]=ptr;
////        //mlabel[i]=Time;
////        //time_ptr[i]=Time.toStdString();
////        y[i]=(uint)Value;

////       qDebug()<<y[i];

////      // qDebug()<<x[i];
////       // qDebug()<<dateTime;
////        // qDebug()<<(x[0]/10000);
////        if(i==0)
////        {
////            max=y[i];
////        }
////        if(max<y[i])
////        {
////         max=y[i];

////        }
////        i++;
////        //qDebug()<<"Value";
////        }
//    }
//virtual ~TypeA()
//    {
//    }
//};


//class IGraphView
//{
//public:
//    virtual ~IGraphView(){};
//    virtual void showfigure(QPainter *Painter,IType *p)=0;
//    virtual void Data_Type_function()=0;
//};

////class LineGraphType:public IGraphView
////{

////public:
////    void showfigure(QPainter *Painter,IType *p)
////    {
////       Draw(Painter);
////    }
////    void Draw(QPainter *Painter,IType *p)
////    {
////        // some print with type data


////    }

////    void Data_Type_function()
////{


////}


////};


//class IRepository
//{
//public:

//    virtual void Print_Graph(Win*)=0;
//    virtual void Get_Data()=0;
//    virtual void Color()=0;


//};

//class Lite_Database_Repository : public IRepository
//{
//protected:
//QFrame *frame;
//private:
//QVector<double> x;
//QVector<double> y;
//    // TypeA *b;
//     //QSqlQuery query;
//      //QCustomPlot cPlot;
//public:
//    void  Print_Graph(Win* s)
//    {
//        s->setGeometry(900,900,900,900);
//        int siz=x.size();

//        frame = new QFrame(s);
//        frame->setFrameShadow(QFrame::Raised);
//        frame->setFrameShape(QFrame::Panel);
//        int sizeWindow=700;
//        Area * area = new Area( s,siz,x,y,sizeWindow);
//        QVBoxLayout *vLayout1 = new QVBoxLayout(frame);

//        vLayout1->addWidget(area);
//        vLayout1->addStretch();
//        QHBoxLayout *hLayout = new QHBoxLayout(s);
//        hLayout->addWidget(frame);
//        hLayout->addLayout(vLayout1);


//    }
//    void Get_Data()
//    {

//        QString pathToDB = QString("C:\\HUMIDITY_MOSCOW.sqlite");
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
//        int siz;
//               QSqlQuery query;
//        //b=new TypeA(query,s);

//        query.exec("SELECT Value,Time from humidity_moscow ORDER BY 'YYYY.MM.DD HH:MM'");
//        int numberOfRows = 0;
//        if(query.last())
//        {
//         numberOfRows =  query.at() + 1;
//         query.first();
//         query.previous();
//        }
//        siz=numberOfRows;


//        x=QVector<double>(siz);
//        y=QVector<double>(siz);
//        uint tr;
//        int i=0;
//        QDateTime Time;
//        double max=0;
//        while (query.next()) {
//        double Value = query.value(0).toDouble();
//        QVariant strTime =  query.value(1).toString();
//        QString time_format = "yyyy.MM.dd  hh:mm";
//         QDateTime dateTime = QDateTime::fromString(strTime.toString(),"dd.MM.yyyy hh:mm");
//         //dateTime.setTimeSpec(Qt::LocalTime);
//    tr=dateTime.toTime_t ();
//    uint ptr=dateTime.toTime_t();


//   //x[i]=((ptr-first_x)/(siz));
//        x[i]=ptr;
//        //mlabel[i]=Time;
//        //time_ptr[i]=Time.toStdString();
//        y[i]=(uint)Value;

//       qDebug()<<y[i];

//      // qDebug()<<x[i];
//       // qDebug()<<dateTime;
//        // qDebug()<<(x[0]/10000);
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


////     cPlot.setGeometry(300,300,300,300);
////         // генерируем данные

////         // создаем график и добавляем данные:
////         cPlot.addGraph();
////         cPlot.graph(0)->setData(x, y);
////        // QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
////        // cPlot.xAxis->setTicker(dateTimeTicker);
////        // dateTimeTicker->setTickCount(12);
////        // dateTimeTicker->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);
////         // задаем обозначения осей координат:
////         cPlot.xAxis->setLabel("x");
////         cPlot.yAxis->setLabel("y");
////       //  dateTimeTicker-> setDateTimeFormat ("dd.MM.yyyy  hh:mm");
////         // устанавливаем диапазоны отображения данных:
////         cPlot.xAxis->setRange(x[0], x[siz-1]);
////         cPlot.yAxis->setRange(0, max);
////         cPlot.replot();

////    //     frame = new QFrame(this);
////    //     frame->setFrameShadow(QFrame::Raised);
////    //     frame->setFrameShape(QFrame::Panel);
////         s->setGeometry(300,300,300,300);
////         //QVBoxLayout *vLayout1 = new QVBoxLayout(s);
////         //vLayout1->addWidget(&cPlot);
////         //vLayout1->addStretch();
////        //QVBoxLayout *vLayout2 = new QVBoxLayout();
////        //  vLayout2->addStretch();
////         QHBoxLayout *hLayout = new QHBoxLayout(s);
////         hLayout->addWidget(&cPlot);
////        // vLayout1->addLayout(hLayout);
////         s->setLayout(hLayout);

////         s->show();



//        }
//          }
//    }
//    void Color()
//    {}
//};

//class TextRepository : public IRepository
//{
//public:
//    void  Print_Graph(Win *)
//    {

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

////    string SavePurchaseOrder()
////    {
////        return _repository->Save();
////    }
//};
//Win::Win(QWidget *parent):QWidget(parent)
//{
////    codec = QTextCodec::codecForName("UTF-8");
////    this->setWindowTitle(codec->toUnicode("Обработка событий"));
////    setWindowTitle(codec->toUnicode("График"));
//////    gContainer.RegisterInstance<IRepository, Lite_Database_Repository>();
//////    gContainer.RegisterFactory<IType ,TypeA , IRepository>();
//////    gContainer.GetObject<IAmAThing>()->TestThis();
////   // gContainer.RegisterFactory<IAmTheOtherThing, TheOtherThing, IAmAThing>();

////      //Создание зависимости
////      // IRepository *dbRepository = new Repository();

////    //Внедрение зависимости
////    // PurchaseBl purchaseBl(dbRepository);
////    // cout<<purchaseBl.SavePurchaseOrder()<<endl;

////   // IRepository *textRepository = new Lite_Database_Repository();

////    //Внедрение зависимости
////    //PurchaseBl purchaseBlT(textRepository);
////    //cout<<purchaseBlT.SavePurchaseOrder()<<endl;



////   // gContainer.RegisterInstance<IRepository, Repository>();
//////    gContainer.RegisterInstance<IRepository, Lite_Database_Repository>();

////    //cout<<"From Container"<<endl;

////  // char * str=(char *)"C:\\\\HUMIDITY_MOSCOW.sqlite";
////    //char* str1 = "This is GeeksForGeeks";
//// // string s4(str);
////    //QString ptr = QString::fromUtf16((ushort*)(str));
////    //  cout << s4;
//// //cout<<gContainer.GetObject<IRepository>()->Print_Graph();

//////   gContainer.GetObject<IRepository>()->Get_Data();
//////   gContainer.GetObject<IRepository>()->Print_Graph(this);


//// //this->setGeometry(900,900,900,900);


//////   frame = new QFrame(this);
//////   frame->setFrameShadow(QFrame::Raised);
//////   frame->setFrameShape(QFrame::Panel);
//////   int sizeWindow=700;
//////   fileButton = new QPushButton(codec->toUnicode("FILE"),
//////   this);
//////   QVBoxLayout *vLayout1 = new QVBoxLayout();
//////   vLayout1->addWidget(fileButton);
//////   QHBoxLayout *hLayout = new QHBoxLayout(this);
//////   hLayout->addWidget(frame);
//////   hLayout->addLayout(vLayout1);


//////   connect(fileButton,SIGNAL(clicked(bool)),
//////   this,SLOT(begin()));


//////   fileButton = new QPushButton(codec->toUnicode("FILE"),
//////   this);
//////      QVBoxLayout *vLayout1 = new QVBoxLayout();
//////      vLayout1->addWidget(fileButton);




//////      connect(fileButton,SIGNAL(clicked(bool)),
//////      this,SLOT(begin()));

////      frame = new QFrame(this);
////      frame->setFrameShadow(QFrame::Raised);
////      frame->setFrameShape(QFrame::Panel);
////         //area = new Area( this,0);
////      fileButton = new QPushButton(codec->toUnicode("FILE"),
////      this);
////         QVBoxLayout *vLayout1 = new QVBoxLayout();
////         vLayout1->addWidget(fileButton);




////         connect(fileButton,SIGNAL(clicked(bool)),
////         this,SLOT(begin()));




//}

//void Win::begin()
//{
//    QString str = QFileDialog::getExistingDirectory(0, "Выбор папки", "D:\\_Qt", QFileDialog::ShowDirsOnly
//                                                    | QFileDialog::DontResolveSymlinks);
////    QString fileName = QFileDialog::getOpenFileName(this,
////        tr("Open Text file"), "", tr("Text Files (*.txt)"));
////qDebug()<<str;


//}
