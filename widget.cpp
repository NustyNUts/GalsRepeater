
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    m_scale = 400000;
    m_scene = new QGraphicsScene(-180*m_scale,-90*m_scale,180*m_scale*2,90*m_scale*2);
    m_sceneCap = new QGraphicsScene();
    m_gridItem = new GridItem();
    m_shipItem = new ShipItem();
    m_galsItem = new GalsItem();
    m_shiptail = new ShipTail();
    m_logic = new Logic();
    m_dayNight = true;//true -day, false-night;
    ui->setupUi(this);
    //ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setScene(m_scene);
    ui->comboBox->addItem("1:1 000");
    ui->comboBox->addItem("1:2 000");
    ui->comboBox->addItem("1:4 000");
    ui->comboBox->addItem("1:6 000");
    ui->comboBox->addItem("1:8 000");
    ui->comboBox->addItem("1:10 000");
    ui->comboBox->addItem("1:20 000");
    ui->comboBox->addItem("1:40 000");
    ui->comboBox->addItem("1:60 000");
    ui->comboBox->addItem("1:80 000");
    ui->comboBox->addItem("1:100 000");
    ui->comboBox->addItem("1:120 000");
    ui->comboBox->addItem("1:140 000");
    ui->comboBox->addItem("1:160 000");
    ui->comboBox->addItem("1:180 000");
    ui->comboBox->addItem("1:200 000");
    ui->comboBox->addItem("1:220 000");
    ui->comboBox->addItem("1:240 000");
    ui->comboBox->addItem("1:260 000");
    ui->comboBox->addItem("1:280 000");
    ui->comboBox->addItem("1:300 000");
    ui->comboBox->setCurrentIndex(6);
    ui->labelGalsGet->setText("Галс отсутствует");
    if(m_dayNight)
    {
        m_scene->setBackgroundBrush(QColor("#0A7AF5"));
        m_sceneCap->setBackgroundBrush(QColor("#0A7AF5"));
    }
    else if(!m_dayNight)
    {
        m_scene->setBackgroundBrush(QColor("#2D3839"));
        m_sceneCap->setBackgroundBrush(QColor("#2D3839"));
    }
    m_scene->addItem(m_shipItem);
    m_scene->addItem(m_gridItem);
    m_scene->addItem(m_galsItem);
    m_scene->addItem(m_shiptail);
    ui->graphicsView->centerOn(m_shipItem);
    m_shipItem->setScale(m_scale);
    m_galsItem->setScale(m_scale);
    m_shiptail->setTailScale(m_scale);
    m_scene->update(m_shipItem->boundingRect());
    m_scene->update(m_gridItem->boundingRect());
    m_scene->update(m_galsItem->boundingRect());

    QPalette Pal(palette());
    ui->gpsTimeLabel->hide();
    ui->label_6->hide();
    // set black background
    Pal.setColor(QPalette::Background, QColor("#DCE4E5"));
    setAutoFillBackground(true);
    setPalette(Pal);

    connect(m_logic,SIGNAL(updateShipPosition()),this,SLOT(setShipCoords()));
    connect(m_logic,SIGNAL(updateGals(int)),this,SLOT(setGals(int)));
    connect(m_logic->client,SIGNAL(readFail(QString)),this,SLOT(noData(QString)));
    connect(m_logic,SIGNAL(setPlaneName(QString)),this,SLOT(setPlaneName(QString)));
    connect(m_logic,SIGNAL(setDeviation(double)),this,SLOT(setDeviation(double)));

}

void Widget::setDeviation(double dev)
{
    m_galsItem->setDeviation(dev/60);
}

void Widget::setPlaneName(QString str)
{
    planeName = str;
    ui->labelPlan->setText(planeName);
}

void Widget::noData(QString msg)
{
    ui->graphicsView->setScene(m_sceneCap);
    static QGraphicsTextItem* textItem = new QGraphicsTextItem();

    m_sceneCap->removeItem(textItem);
    textItem->setPos(ui->graphicsView->width()/2+250,-ui->graphicsView->height()/2);
    textItem->setTextWidth(300);
    textItem->setFont(QFont("Times New Roman",18,2));
    textItem->setDefaultTextColor(QColor("#AD1F1F"));
    textItem->setPlainText(msg);
    //m_sceneCap->addRect(textItem->boundingRect());
    m_sceneCap->addItem(textItem);
    //ui->graphicsView->centerOn(textItem);
    m_sceneCap->update(textItem->boundingRect());
    ui->speedLabel->setText("xx.x");
    ui->courseLabel->setText("xxx.x");
    ui->latLabel->setText("xx°xx.xxx'");
    ui->lonLabel->setText("xxx°xx.xxx'");
    ui->gpsTimeLabel->setText("xx:xx:xx");

}

Widget::~Widget()
{
    delete m_logic;
    delete ui;
}
void Widget::setShipCoords()
{
    ui->graphicsView->setScene(m_scene);
    ui->speedLabel->setText(QString::number(m_logic->ship->getSpeed(),'f',1)+" уз.");
    ui->courseLabel->setText(QString::number(m_logic->ship->getCourse(),'f',1)+"°");
    int latInt;
    double latFracPart;
    int lonInt;
    double lonFracPart;
    latInt = m_logic->ship->getLatitude();
    latFracPart = (m_logic->ship->getLatitude()-latInt)*60;
    lonInt = m_logic->ship->getLongitude();
    lonFracPart = (m_logic->ship->getLongitude()-lonInt)*60;
    QString tmpLatStr;
    if(latInt/10<1)
        tmpLatStr = "0";
    else
        tmpLatStr = "";
    QString tmpLonStr;
    if(lonInt/100<1)
       tmpLonStr = "0";
    else if(lonInt/10<1)
        tmpLonStr = "00";
    else
        tmpLonStr = "";
    ui->latLabel->setText(tmpLatStr+QString::number(latInt)+"°"+QString::number(latFracPart,'f',3)+"'"+m_logic->ship->getPJ()[1]);
    ui->lonLabel->setText(tmpLonStr+QString::number(lonInt)+"°"+QString::number(lonFracPart,'f',3)+"'"+m_logic->ship->getPJ()[0]);
    ui->gpsTimeLabel->setText(m_logic->getGpsTime());


    m_scene->removeItem(m_galsItem);
    m_galsItem->setScale(m_scale);
    m_galsItem->setGals(m_logic->gals);
    m_scene->addItem(m_galsItem);
    m_scene->update(m_galsItem->boundingRect());
     m_scene->update();

    m_scene->removeItem(m_shipItem);
    m_shipItem->setPosition(m_logic->ship->getLatitude(),m_logic->ship->getLongitude(),m_logic->ship->getPJ());
    m_shipItem->setCourse(m_logic->ship->getCourse());
    m_scene->addItem(m_shipItem);
    ui->graphicsView->centerOn(m_shipItem);
    m_scene->update(m_shipItem->boundingRect());

    m_scene->removeItem(m_shiptail);
    m_shiptail->addPoint(m_logic->ship->getLatitude(),m_logic->ship->getLongitude(),m_logic->ship->getPJ());
    m_scene->addItem(m_shiptail);
    m_scene->update(m_shiptail->boundingRect());

    m_scene->removeItem(m_gridItem);
    m_gridItem->setShipCoords(m_shipItem->getX(),m_shipItem->getY(),m_logic->ship->getPJ());
    m_scene->addItem(m_gridItem);
    m_scene->update(m_gridItem->boundingRect());
    m_scene->update(m_galsItem->boundingRect());


}
void Widget::setGals(int checkGals)
{
    if(checkGals==1)
        ui->labelGalsGet->setText("Галс получен");
    if(checkGals == 0)
        ui->labelGalsGet->setText("Галс отсутствует");

    m_scene->removeItem(m_galsItem);
    m_galsItem->setGals(m_logic->gals);
    m_scene->addItem(m_galsItem);
    m_scene->update(m_galsItem->boundingRect());
    m_scene->update();

    m_scene->removeItem(m_shiptail);
    m_scene->addItem(m_shiptail);

    m_scene->removeItem(m_shipItem);
    m_scene->addItem(m_shipItem);
}

//$GPRMC,hhmmss.sss,A,GGMM.MM,P,gggmm.mm,J,v.v,b.b,ddmmyy,x.x,n,m*hh<CR><LF>

//(пробелов и переносов внутри строки нет).

//Значение полей:

//«GP» — идентификатор источника; в приведенном примере это GPS, «GL» - ГЛОНАСС, «GA» - Галилео, «GN» - ГЛОНАСС+GPS и т.п.
//«RMC» — «Recommended Minimum sentence C»
//«hhmmss.sss» — время фиксации местоположения по Всемирному координированному времени UTC: «hh» — часы, «mm» — минуты, «ss.sss» — секунды. Длина дробной части секунд варьируется. Лидирующие нули не опускаются.
//«A» — статус: «A» — данные достоверны, «V» — недостоверны.
//«GGMM.MM» — широта. 2 цифры градусов(«GG»), 2 цифры целых минут, точка и дробная часть минут переменной длины. Лидирующие нули не опускаются.
//«P» — «N» для северной или «S» для южной широты.
//«gggmm.mm» — долгота. 3 цифры градусов(«ggg»), 2 цифры целых минут, точка и дробная часть минут переменной длины. Лидирующие нули не опускаются.
//«J» — «E» для восточной или «W» для западной долготы.
//«v.v» — горизонтальная составляющая скорости относительно земли в узлах. Число с плавающей точкой. Целая и дробная части переменной длины.
//«b.b» — путевой угол (направление скорости) в градусах. Число с плавающей точкой. Целая и дробная части переменной длины. Значение равное 0 соответствует движению на север, 90 — восток, 180 — юг, 270 — запад.
//«ddmmyy» — дата: день месяца, месяц, последние 2 цифры года (ведущие нули обязательны).
//«x.x» — магнитное склонение в градусах (часто отсутствует), рассчитанное по некоторой модели. Число с плавающей точкой. Целая и дробная части переменной длины.
//«n» — направление магнитного склонения: для получения магнитного курса магнитное склонение необходимо «E» — вычесть, «W» — прибавить к истинному курсу.
//«m» — индикатор режима: «A» — автономный, «D» — дифференциальный, «E» — аппроксимация, «N» — недостоверные данные (часто отсутствует, данное поле включая запятую отсутствует в старых версиях NMEA).
//«hh» — контрольная сумма.
//<CR> — байт равен 0x0D.
//<LF> — байт равен 0x0A.

void Widget::on_pushButton_clicked()
{
    QPalette Pal(palette());
    QPalette PalCombo(ui->comboBox->palette());
    m_dayNight = !m_dayNight;
    m_shipItem->setDayNight(m_dayNight);
    m_galsItem->setDayNight(m_dayNight);
    m_gridItem->setDayNight(m_dayNight);
    if(m_dayNight)
    {
        m_scene->setBackgroundBrush(QColor("#0A7AF5"));
        m_sceneCap->setBackgroundBrush(QColor("#0A7AF5"));
        ui->pushButton->setText("День");
        Pal.setColor(QPalette::Background, QColor("#DCE4E5"));
        Pal.setColor(QPalette::WindowText,Qt::black);
        setPalette(Pal);
    }
    else if(!m_dayNight)
    {
        m_scene->setBackgroundBrush(QColor("#2D3839"));
        m_sceneCap->setBackgroundBrush(QColor("#2D3839"));
        ui->pushButton->setText("Ночь");
        Pal.setColor(QPalette::Background, QColor("#556668"));
        Pal.setColor(QPalette::WindowText,Qt::green);
        setPalette(Pal);
    }
    m_scene->update();
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    m_scale = ui->comboBox->currentText().split(':')[1].remove(' ').toInt();
    m_shipItem->setScale(m_scale);
    m_scene->removeItem(m_shipItem);
    m_shipItem->setPosition(m_logic->ship->getLatitude(),m_logic->ship->getLongitude(),m_logic->ship->getPJ());
    m_scene->addItem(m_shipItem);
    ui->graphicsView->centerOn(m_shipItem);

    m_scene->removeItem(m_gridItem);
    m_gridItem->setShipCoords(m_shipItem->getX(),m_shipItem->getY(),m_logic->ship->getPJ());
    m_gridItem->setScale(m_scale);
    m_scene->addItem(m_gridItem);
    m_scene->update(m_gridItem->boundingRect());

    m_scene->removeItem(m_galsItem);
    m_galsItem->setScale(m_scale);
    m_galsItem->setGals(m_logic->gals);
    m_scene->addItem(m_galsItem);
    m_scene->update(m_galsItem->boundingRect());
    m_scene->update();

    m_scene->removeItem(m_shiptail);
    m_shiptail->setTailScale(m_scale);
    m_scene->addItem(m_shiptail);
    m_scene->update(m_shiptail->boundingRect());



}

void Widget::on_pushButton_2_clicked()
{
    m_shiptail->clearTail();
}

void Widget::on_pushButton_3_clicked()
{
    m_galsItem->setdevShow();
}
