#include "wind.h"
class IOCContainer

{

    static int s_typeId;
public:
    //one typeid per type

    template<typename T>
    static int GetTypeID()
    {

        static int typeId = s_typeId++;
        return typeId;
    }

    /*
     Получение экземпляров объекта;

     Теперь, когда  есть идентификатор типа, мы должны иметь возможность хранить какой-то фабричный объект,
     чтобы показать тот факт, что мы не знаем, как создать объект.(так как мы не знаем как создать объект)

     Хранить все фабрики в одной коллекции, для этого выбираем абстрактный базовый класс,
     из которого будут производиться фабрики, и реализацию, которая захватывает функтор для последующего вызова.
     Можно использовать std :: map для хранения фабрик,та же можно рассмотреть  другие варианты для эффективности.

    */
    class FactoryBase

    {

    public:

        virtual ~FactoryBase() {}

    };

    //todo: consider sorted vector

    map<int, shared_ptr<FactoryBase>> factories;

    template<typename T>

    class CFactory : public FactoryBase

    {
        //std::function
        std::function<std::shared_ptr<T>()> functor;
    public:
        ~CFactory() {}

        CFactory(std::function<std::shared_ptr<T>()> functor)

            :functor(functor)

        {

        }

        std::shared_ptr<T> GetObject()
        {
            return functor();
        }

    };

    template<typename T>

    std::shared_ptr<T> GetObject()

    {

        auto typeId = GetTypeID<T>();
        auto factoryBase = factories[typeId];
        auto factory = std::static_pointer_cast<CFactory<T>>(factoryBase);
        return factory->GetObject();
    }

    /*
    Регистрация экземпляров
    */

    //Базовая реализация - регистрация функтора

    template<typename TInterface, typename ...TS>
    void RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)> functor)
    {
        factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>([=] {return functor(GetObject<TS>()...); });
    }

    //Регистрация экземпляра объекта
    template<typename TInterface>
    void RegisterInstance(std::shared_ptr<TInterface> t)
    {
        factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>([=] {return t; });
    }

    //Работаем с указателем на функцию
    template<typename TInterface, typename ...TS>
    void RegisterFunctor(std::shared_ptr<TInterface>(*functor)(std::shared_ptr<TS> ...ts))
    {
        RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)>(functor));
    }


    //Фабрика, которая будет вызывать необходимый конструктор для каждого экземпляра
    template<typename TInterface, typename TConcrete, typename ...TArguments>
    void RegisterFactory()
    {
        RegisterFunctor(
            std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments> ...ts)>(
                [](std::shared_ptr<TArguments>...arguments) -> std::shared_ptr<TInterface>
        {
            return std::make_shared<TConcrete>(std::forward<std::shared_ptr<TArguments>>(arguments)...);
        }));

    }



    //Фабрика, которая будет возвращать один экземпляр  объекта  для каждого вызова
    template<typename TInterface, typename TConcrete, typename ...TArguments>
    void RegisterInstance()
    {
        RegisterInstance<TInterface>(std::make_shared<TConcrete>(GetObject<TArguments>()...));
    }
    //Фабрика, которая будет возвращать один экземпляр  объекта  для каждого вызова
    template<typename TInterface1, typename TConcrete1,typename TInterface2, typename TConcrete2, typename ...TArguments>
    void RegisterInstance()
    {
        RegisterInstance<TInterface1>(std::make_shared<TConcrete1>(GetObject<TArguments>()...));
    }

};

IOCContainer gContainer;

//Иницализация не нулевым значением


int IOCContainer::s_typeId = 121;


class IRepository                                                                //интерфейс репозиториев
{
public:
    virtual ~IRepository (){};
    virtual void Print_Graph(Win*,Area&)=0;
    virtual void Get_Data(const string,QVariant&)=0;
    virtual void Get_Data(QVector<double>,QVector<double>)=0;
    virtual void Color_RGB(QRgb, QRgb, QRgb, QRgb)=0;
    virtual void GenerateException(string)=0;
};
class JsonFile : public IRepository                                              //Класс обработки Json файлов
{
private:
QVector<QRgb> Color;                                                             //Вектор цветов
  QVector<double> x;                                                             //Вектор данных Data
  QVector<double> y;                                                             //Вектор данных Value
 void  GenerateException(string index)                                           //Генерация исключений  на вход исключение типа string
  {
     if (index=="fromJson failed:")                                              //Файл не открылся
     {
       string str="File from Json do not open";
       throw str;
     }
     if(index=="JsonDocument not open")                                          //Документ Json не открывается
     {
         string str="JsonDocument do not open";
         throw str;
     }
  }
 void  Print_Graph(Win* s,Area& area)                                             //Функция рисования графика  на вход обьект наследника окна Win* и ссылка на сам объект вывода
   {
       //s->setGeometry(900,900,900,900);
       int siz=x.size();                                                          //Размер входных данных
       int sizeWindow=700;                                                       //Устанавливаем размер окна вывода 700
       area.AreaPrint( s,siz,x,y,sizeWindow,Color);                              //Выводим на окно график через функцию AreaPrint на вход обьект наследника окна Win* s,Устанавливаем размер окна вывода siz, входные данные графиков
   }

    void Get_Data(const string path, QVariant& document)                                //Функция  Получения данных на вход директрия файла и ссылка на прочитанные данные
    {
        QFile file( path.c_str() );                                               //Создаем объект типа QFile для чтения файла
        if( file.open( QIODevice::ReadOnly ) )                                    //Проверяем на открытие на чтение
        {
            QByteArray bytes = file.readAll();                                    //Считываем в bytes
            file.close();                                                         //Закрываем файл

            QJsonParseError jsonError;                                            //Создаем обьект на проверку синтаксиа записи
            document = QJsonDocument::fromJson( bytes, &jsonError );              //Записываем в прочитанные данные типа (QVariant)JsonDocument
            if(!document.isNull() && jsonError.error != QJsonParseError::NoError )//Проверк ан аошибки в синтаксие и запись в document
            {
                GenerateException("fromJson failed:");                            //Обрабатываем исключение
                cout << "fromJson failed: " << jsonError.errorString().toStdString() << endl;
                return ;
            }

        }
    }

    void Get_Data(QVector<double> x_axis,QVector<double> y_axis)                   //Функция для присваиваем значений из IType
    {
    x=x_axis;
    y=y_axis;
    }
    void Color_RGB(QRgb shade, QRgb color_x,QRgb color_y,QRgb color_z)             //Присвовение оттенков RGB: shade-оттенок цвета color_x-Red color_y-Green color_z-Blue
    {
    Color={shade, color_x, color_y, color_z};                                      //Задание вектора оттенков типа QRgb
    }
};


class Lite_Database_Repository : public IRepository                                //Класс обработки Lite database файлов
{
protected:
//QFrame *frame;
private:
QVector<QRgb> Color;                                                               //Вектор цветов
QSqlDatabase dbase;                                                                // Сам объект базы данных, с которым будет производиться работа
QVector<double> x;
QVector<double> y;
// TypeA *b;
//QSqlQuery query;
//QCustomPlot cPlot;
public:
virtual ~Lite_Database_Repository(){ dbase.close();}
void  GenerateException(string index)                                               //Обработчик иключений
 {
    if (index=="Lite_Database_Repository_Exeption_Open")                            //База данныйх не открылась
    {
      string str="The database date does not open";  
      throw str;
    }
    if(index=="File_Lite_Database_Repository_Exeption_Open")                        //Файл даты базы не открылся
    {
    string str="The file of database date does not open";
    throw str;
    }
    if(index=="Selection failed")                                                   //Выборка не правильная
    {
        string str="Selection failed";
        throw str;
    }
 }

   void Print_Graph(Win* s,Area& area)                                              //Функция рисования графика  на вход обьект наследника окна Win* и ссылка на сам объект вывода
    {
        //s->setGeometry(900,900,900,900);
        int siz=x.size();
        int sizeWindow=700;
        area.AreaPrint( s,siz,x,y,sizeWindow,Color);                                //Выводим на окно график через функцию AreaPrint на вход обьект наследника окна Win* s,Устанавливаем размер окна вывода siz, входные данные графиков

    }
void Get_Data(QVector<double> x_axis,QVector<double> y_axis)                         //Функция для присваиваем значений из IType
{
x=x_axis;
y=y_axis;
}
    void Get_Data(const string path, QVariant&  db)                                  //Функция  Получения данных на вход директрия файла и ссылка на прочитанные данные
    {

        QString pathToDB = QString(path.c_str());                                    //pathToDB путь к файлу типа QString
        dbase = QSqlDatabase::addDatabase("QSQLITE");                                //База данных открывается по заданному пути  и имени базы данных, если она существует
        dbase.setDatabaseName(pathToDB);
        QFileInfo checkFile(pathToDB);                                               //Проверяем на открытие файла
          if (checkFile.isFile())
          {

        if (!dbase.open())
        {
            GenerateException("Lite_Database_Repository_Exeption_Open");
            qDebug() << "Что-то не так с соединением!";
        }
        else
        {
        dbase.open();                                                                  //Открываем на чтение
        //b=new TypeA(query,s);
//     cPlot.setGeometry(300,300,300,300);
//         // генерируем данные

//         // создаем график и добавляем данные:
//         cPlot.addGraph();
//         cPlot.graph(0)->setData(x, y);
//        // QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
//        // cPlot.xAxis->setTicker(dateTimeTicker);
//        // dateTimeTicker->setTickCount(12);
//        // dateTimeTicker->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);
//         // задаем обозначения осей координат:
//         cPlot.xAxis->setLabel("x");
//         cPlot.yAxis->setLabel("y");
//       //  dateTimeTicker-> setDateTimeFormat ("dd.MM.yyyy  hh:mm");
//         // устанавливаем диапазоны отображения данных:
//         cPlot.xAxis->setRange(x[0], x[siz-1]);
//         cPlot.yAxis->setRange(0, max);
//         cPlot.replot();

//    //     frame = new QFrame(this);
//    //     frame->setFrameShadow(QFrame::Raised);
//    //     frame->setFrameShape(QFrame::Panel);
//         s->setGeometry(300,300,300,300);
//         //QVBoxLayout *vLayout1 = new QVBoxLayout(s);
//         //vLayout1->addWidget(&cPlot);
//         //vLayout1->addStretch();
//        //QVBoxLayout *vLayout2 = new QVBoxLayout();
//        //  vLayout2->addStretch();
//         QHBoxLayout *hLayout = new QHBoxLayout(s);
//         hLayout->addWidget(&cPlot);
//        // vLayout1->addLayout(hLayout);
//         s->setLayout(hLayout);

//         s->show();

        }
          }
          else
          {
          GenerateException("File_Lite_Database_Repository_Exeption_Open");               //Обработка исключения
          }
    }
    void Color_RGB(QRgb shade, QRgb color_x,QRgb color_y,QRgb color_z)                    //Присвовение оттенков RGB: shade-оттенок цвета color_x-Red color_y-Green color_z-Blue
    {
    Color={shade, color_x, color_y, color_z};
    }
};



class IType                                                                               //Интерфейс типов читаемых файлов
{
    public:
    virtual void Read_Data(const string,const string)=0;                                  //Функция чтения данных на вход дирректоия файла и название файла
    virtual ~IType(){};
};


class TypeJsonA:public IType                                                              //Обработчик типа Json обрабатывает data:(string)"yyyy.MM.dd hh:mm" value:double
{
private:
   std::shared_ptr<IRepository> items;                                                    //Умный указатель на репозиторий
public:
   TypeJsonA(std::shared_ptr<IRepository> thing) :items(thing){}                          // Конструктор для типа JsonA указатель items на репозиторий
   void Read_Data(const string path,const string s)                                       //Функция чтения файла path путь s- имя файла
   {
       QVector<double> x;
       QVector<double> y;
       QVariant document;
       items->Get_Data(path,document);                                                    //Получение данный в виде document
       QJsonDocument doc=(document.toJsonDocument());                                     //Преобразования из QVariant
       if( doc.isObject() )                                                               //Если объект существует
       {
       QJsonObject jsonObj =doc.object();
       QJsonValue value = (jsonObj).value(QString(s.c_str()));
       QJsonObject item = value.toObject();
       QJsonArray test = item["value"].toArray();
       for(auto key:test)                                                                 //Проход по массиву Value
       {
           if(key.toDouble())                                                             //Если конвертируется в doubl то записываем в y
           {
           y.push_back(key.toDouble());
           }
       }
       QJsonArray test_data = item["Data"].toArray();
       for(auto key:test_data)
       {
           if(key.isString())                                                              // Если конвертируется в string то записываем в x
           {
           QDateTime dateTime = QDateTime::fromString(key.toString(),"dd.MM.yyyy hh:mm");  // Конвертируем в дату строку
           //dateTime.setTimeSpec(Qt::LocalTime);
           uint ptr=dateTime.toTime_t();                                                   //Преобразуем в uint дату в диапазоне 1900~2100
           x.push_back(ptr);
           }
       }

   items->Get_Data(x,y);                                                                    //Записывем в репозиторий x y
   }
       else
       {
           items->GenerateException("JsonDocument not open");                               //Генерация исключения документ не открылся
       }
   }
   virtual ~TypeJsonA()
       {
       }
};
class TypeB: public IType                                                                   //Класс обрабатывающий выборку Data:(string) "yyyy.MM.dd  mm" Value:double
{
private:
   std::shared_ptr<IRepository> items;
public:
   TypeB(std::shared_ptr<IRepository> thing) :items(thing){}
   void Read_Data(const string path,const string s)
   {
       QVariant document;
       items->Get_Data(path,document);                                                       //Открываем sql файл
       QSqlQuery query;
       string Select_s="SELECT Value,Time from   ORDER BY 'YYYY.MM.DD mm'";                  //Выбоорка
       Select_s.insert(23, s);                                                               //Вставляем на место после from название sql таблицы
       query.exec(QString::fromStdString(Select_s));                                         //Выполняем выборку
       if(!query.exec())                                                                     //Проверка выполняется ли она
       {
        items->GenerateException("Selection failed");                                        //Генерация исключения
       }
       int numberOfRows = 0;                                                                 //Подсчет размера выборки количества x
       if(query.last())
       {
        numberOfRows =  query.at() + 1;
        query.first();
        query.previous();
       }
       int siz=numberOfRows;
       QVector<double> x;
       QVector<double> y;

       x=QVector<double>(siz);
       y=QVector<double>(siz);
       int i=0;
       QDateTime Time;
       while (query.next()) {                                                            //Проходимся по выборке
       double Value = query.value(0).toDouble();                                         //Конвертируем в double
       QVariant strTime =  query.value(1).toString();                                    //Конвертируем в String
      // QString time_format = "yyyy.MM.dd  mm";
       int pos = ((strTime.toString()).toStdString()).find(' ');                         //Первая позиция пробела
       QString s=QString::fromStdString(((strTime.toString()).toStdString()).substr(pos + 1)); //Копируем подстроку после pos
       int pp =s.toInt();                                                                      //ПРеобразуем в int число после пробела
       QString hour=QString::number(pp/60);                                                    //Разбиваем на часы и минуты
       QString minut=QString::number(pp%60);
       if(pp/60<10)
       {
        hour="0"+QString::number(pp/60);
       }
       if(pp/60==24)
       {
           hour="00";
       }
       if(pp%60<10)
       {
        minut="0"+QString::number(pp%60);
       }
       QString stp = hour+":"+minut;                                                              //Приводим к нужному формату

       QString newStr = (strTime.toString()).left((strTime.toString()).indexOf(' ')) + " "+stp;   //Конвертируем дату в число
       QDateTime dateTime = QDateTime::fromString(newStr,"dd.MM.yyyy hh:mm");
        //dateTime.setTimeSpec(Qt::LocalTime);
       uint ptr=dateTime.toTime_t();
       x[i]=ptr;
       y[i]=Value;
       i++;
       //qDebug()<<"Value";
       }
       items->Get_Data(x,y);                                                                       //Записываем в x, y

   }
   virtual ~TypeB()
       {
       }
};

class TypeA: public IType                                                              //Класс обрабатывающий выборку Data:(string) "yyyy.MM.dd  hh:mm" Value:double
{
private:
   std::shared_ptr<IRepository> items;
public:
     TypeA(std::shared_ptr<IRepository> thing) :items(thing)
    {


    }
    bool checkTime( QVariant time)                                                                    //Проверка корректности выборки параметра времени
    {
        string qs = (time.toString()).toStdString();                                                  //Преобразуем в строку
        std::string array[5];
        size_t position = 0;
        int day, month, year,hours,minut;
        int index = 0;
                     while ((position = qs.find('.')) != std::string::npos  )   //Проходимся по строке до определенных симвлов занося в массив array значения
                     {
                         std::string token = qs.substr(0, position);
                         array[index] = token;
                         qs.erase(0, position + 1);
                         index += 1;
                     }
                     while ((position = qs.find(' ')) != std::string::npos)
                     {
                         std::string token = qs.substr(0, position);
                         array[index] = token;
                         qs.erase(0, position + 1);
                         index += 1;
                     }
                     while ((position = qs.find(':')) != std::string::npos )
                     {
                         std::string token = qs.substr(0, position);
                         array[index] = token;
                         qs.erase(0, position + 1);
                         index += 1;
                     }
                       array[index]=qs;
                       day = atoi(array[0].c_str());
                       month = atoi(array[1].c_str());
                       year = atoi(array[2].c_str());
                       hours= atoi(array[3].c_str());
                       minut= atoi(array[4].c_str());
        if(day > 0 && day < 32 )                                                        //Проверка введной строки на коректность даты в противном случае вернет flase и обработка исключения ошибки выборки
        {
            if( month > 0 && month < 13)
            {
                if(year<2100&&year>=1900)
                {
                    if(hours>=0&&hours<=24)
                    {
                        if(minut>=0&&minut<=60)
                         {
                            return true;}
                        else{ return false;}//qDebug() << "Error Select: minut";}
                    }else{return false;}//qDebug() << "Error Select: hour";}
                }else{return false;}//qDebug() << "Error Select: year";}
            }else{return false;}//qDebug() << "Error Select: month";}
        }else{return false;}//qDebug() << "Error Select: day";}

    }
    void Read_Data(const string path,const string s)
    {
        QVariant document;
        items->Get_Data(path,document);                                                       //Функция открытия sql базы
        QSqlQuery query;
        string Select_s="SELECT Value,Time from   ORDER BY 'YYYY.MM.DD HH:MM'";
        Select_s.insert(23, s);
        query.exec(QString::fromStdString(Select_s));
        if(!query.exec())
        {
         items->GenerateException("Selection failed");                                        //Обработка исключения ошибки выборки

        }
        int numberOfRows = 0;
        if(query.last())
        {
         numberOfRows =  query.at() + 1;
         query.first();
         query.previous();
        }
        int siz=numberOfRows;
        QVector<double> x;
        QVector<double> y;

        x=QVector<double>(siz);
        y=QVector<double>(siz);
        uint tr;
        int i=0;
        QDateTime Time;
        while (query.next()) {                                                                    //Проход по выборке и запись значений в Value и strTime
        double Value = query.value(0).toDouble();
        QVariant strTime =  query.value(1).toString();
        if( !checkTime(strTime))
        {
        items->GenerateException("Selection failed");
        }
        QString time_format = "yyyy.MM.dd  hh:mm";
        QDateTime dateTime = QDateTime::fromString(strTime.toString(),"dd.MM.yyyy hh:mm");
         //dateTime.setTimeSpec(Qt::LocalTime);
        uint ptr=dateTime.toTime_t();

        x[i]=ptr;
        y[i]=Value;

        i++;
        //qDebug()<<"Value";
        }
        items->Get_Data(x,y);                                                                       //Заносим считанные данные в репозиторий

    }
virtual ~TypeA()
    {
    }
};

class Icolor
{
public:
   virtual ~Icolor(){};
   virtual void Paint_Grath()=0;

};
class Multicolor_Color:public Icolor
{
private:
     std::shared_ptr<IRepository> items;
public:
    Multicolor_Color(std::shared_ptr<IRepository> thing) :items(thing){}
    void Paint_Grath()
    {
    items->Color_RGB(qRgb(1,1,1),qRgb(1,0,0),qRgb(0,1,0),qRgb(0,0,1));   //qRgb(1,1,1)-оттенок,qRgb(1,0,0)-r,qRgb(0,1,0)-g,qRgb(0,0,1)-b Формирует цветное изображение на основе формулы

    }
    ~Multicolor_Color(){}
};


class Non_Colored:public Icolor
{
private:
     std::shared_ptr<IRepository> items;
public:
    Non_Colored(std::shared_ptr<IRepository> thing) :items(thing){}
    void Paint_Grath()
    {
    items->Color_RGB(qRgb(1, 1, 1),qRgb(1,1,1),qRgb(1,1,1),qRgb(1,1,1)); //qRgb(1,1,1)-оттенок,qRgb(1,0,0)-r,qRgb(0,1,0)-g,qRgb(0,0,1)-b Формирует черно-белое изображение на основе формулы
    }
  ~Non_Colored(){}
};


Win::Win(QWidget *parent):QWidget(parent)
{
    codec = QTextCodec::codecForName("UTF-8");
    this->setWindowTitle(codec->toUnicode("Обработка событий"));
 setWindowTitle(codec->toUnicode("График"));

//    gContainer.RegisterInstance<IRepository, Lite_Database_Repository>();
//    gContainer.RegisterFactory<IType ,TypeA , IRepository>();
  //   gContainer.GetObject<IAmAThing>()->TestThis();
    // gContainer.RegisterFactory<IAmTheOtherThing, TheOtherThing, IAmAThing>();
//gContainer.RegisterInstance<IRepository, Lite_Database_Repository>();
// gContainer.GetObject<IRepository>()->Get_Data();
//gContainer.GetObject<IRepository>()->Print_Graph(this);
//begin();
//this->setGeometry(400,400,400,400);

 frame = new QFrame(this);                                                                           //Рамка Графика
 frame->setFrameShadow(QFrame::Raised);
 frame->setFrameShape(QFrame::Panel);

 area = new Area( this,500);                                                                        //Установка первоначального окна размером 500
 fileButton = new QPushButton(codec->toUnicode("FILE"),
 this);
 MulticolorButton = new QPushButton(codec->toUnicode("Multicolor"),
 this);
 Non_coloredButton = new QPushButton(codec->toUnicode("Non-colored"),
 this);
 QVBoxLayout *vLayout2 = new QVBoxLayout(frame);
  vLayout2->addWidget( area);
  vLayout2->addWidget( MulticolorButton);
  vLayout2->addWidget( Non_coloredButton);
  vLayout2->addWidget( fileButton);
  vLayout2->addStretch();
 QHBoxLayout *hLayout = new QHBoxLayout(this);
 hLayout->addWidget(frame);
 hLayout->addStretch();
 hLayout->addLayout(vLayout2);

 area->setVisible(true);
 fileButton->setEnabled(true);
 fileButton->setDefault(true);
 Non_coloredButton->setEnabled(true);
 Non_coloredButton->setDefault(true);
  MulticolorButton->setEnabled(true);
  MulticolorButton->setDefault(true);
 fileButton->setFocus();
 connect(  Non_coloredButton,SIGNAL(clicked(bool)),
 this,SLOT( non_colored()));
 connect(  MulticolorButton,SIGNAL(clicked(bool)),
 this,SLOT( colored()));
 connect( fileButton,SIGNAL(clicked(bool)),
 this,SLOT( begin()));

}
void Win::GenerateException(string index) //Функция генерации исключения
{
  if (index=="FileFormatExeption")
  {
    throw index;
  }
}
void Win::Color_Paint()                                                            //Функция регистрации фабрики цветного или черно-белого цвета
{
    if(color=="Color")                                                             //Если на вход поступило Color то цветной(изначально стоит Color)
    {
        gContainer.RegisterFactory<Icolor ,Multicolor_Color , IRepository>();
    }
   else
    {
      gContainer.RegisterFactory<Icolor ,Non_Colored , IRepository>();
    }
}
void Win::ExeptionBlock(QString ext,QString str,string sop)   //Блок проверки типаB если типА не подходит по выборке
{
    try
    {
        gContainer.RegisterFactory<IType ,TypeB , IRepository>();
        gContainer.GetObject<IType>()->Read_Data(str.toStdString(),sop);
        Color_Paint();
        gContainer.GetObject<Icolor>()->Paint_Grath();
        gContainer.GetObject<IRepository>()->Print_Graph(this,*area);
    }
    catch(string FileFromatException)
    {
       qDebug() << "Error: " << FileFromatException.c_str() << endl;
    }
}
void Win::colored()
{
    color="Color";
}
void Win::non_colored()
{
  color="Non_Color";
}
void Win::begin()
{

    QString str = QFileDialog::getOpenFileName(0, "Выбор папки", "D:\\_Qt");          //Директория выбранного файла
    QFileInfo fi(str);
    QString s = fi.fileName();
    QString newStr = s.left(s.indexOf('.'));
    string sop=newStr.toStdString();                                                   //Имя файла без формата
    for(auto& c : sop)
    {
       c = tolower(c);
    }
    QString ext = fi.completeSuffix();                                                 //Тип файла
    try
    {
    if(ext=="json")                                                                    //Если файл типа json
    {
     gContainer.RegisterInstance<IRepository,JsonFile>();                             //Регистрация регистра в данном случае JsonFile
     gContainer.RegisterFactory<IType ,TypeJsonA , IRepository>();                    //Регистрация типа введеных данных графика
     gContainer.GetObject<IType>()->Read_Data(str.toStdString(),sop);                 //Читать данные типа TypeJsonA
     Color_Paint();                                                                   //Регистрация Цвета графика
     gContainer.GetObject<Icolor>()->Paint_Grath();                                   //Фиксирует стиль графика цветной или черно белый
     gContainer.GetObject<IRepository>()->Print_Graph(this,*area);                    //Рисует График
    }
    else if(ext=="sqlite")
    {
        gContainer.RegisterInstance<IRepository,Lite_Database_Repository>();
        gContainer.RegisterFactory<IType ,TypeA , IRepository>();
        gContainer.GetObject<IType>()->Read_Data(str.toStdString(),sop);
        Color_Paint();
        gContainer.GetObject<Icolor>()->Paint_Grath();
        gContainer.GetObject<IRepository>()->Print_Graph(this,*area);
    }
   else
   {
        GenerateException("FileFormatExeption");
   }
}
    catch (string FileFromatException) {  // ловим объект исключения
       if(FileFromatException=="Selection failed")
       {
           ExeptionBlock(ext,str,sop);
       }else
       {
           qDebug() << "Error: " << FileFromatException.c_str() << endl;
       }
         }
     area->update();
     fileButton->setDefault(true);
     fileButton->setEnabled(true);
     fileButton->setFocus();
}
