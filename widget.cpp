
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    m_scale = 1000000;
    m_scene = new QGraphicsScene(-180*m_scale,-90*m_scale,180*m_scale*2,90*m_scale*2);
    m_sceneCap = new QGraphicsScene();
    m_gridItem = new GridItem();
    m_shipItem = new ShipItem();
    m_galsItem = new GalsItem();
    m_shiptail = new ShipTail();
    m_logic = new Logic();
    ui->setupUi(this);
    //ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setScene(m_sceneCap);
    ui->comboBox->addItem("1:100 000");
    ui->comboBox->addItem("1:200 000");
    ui->comboBox->addItem("1:300 000");
    ui->comboBox->addItem("1:400 000");
    ui->comboBox->addItem("1:500 000");
    ui->comboBox->addItem("1:600 000");
    ui->comboBox->addItem("1:700 000");
    ui->comboBox->addItem("1:800 000");
    ui->comboBox->addItem("1:900 000");
    ui->comboBox->addItem("1:1 000 000");
    ui->comboBox->setCurrentIndex(4);
    m_scale = 500000;
    m_scene->setBackgroundBrush(QColor("#0A7AF5"));
    m_sceneCap->setBackgroundBrush(QColor("#0A7AF5"));
    m_scene->addItem(m_shipItem);
    m_scene->addItem(m_gridItem);
    m_scene->addItem(m_galsItem);
    m_scene->addItem(m_shiptail);
    ui->graphicsView->centerOn(m_shipItem);
    m_shipItem->setScale(m_scale);
    m_galsItem->setScale(m_scale);
    m_scene->update(m_shipItem->boundingRect());
    m_scene->update(m_gridItem->boundingRect());
    m_scene->update(m_galsItem->boundingRect());
    connect(m_logic,SIGNAL(updateShipPosition()),this,SLOT(setShipCoords()));
    connect(m_logic,SIGNAL(updateGals()),this,SLOT(setGals()));
    connect(m_logic->client,SIGNAL(readFail(QString)),this,SLOT(noData(QString)));
}
void Widget::noData(QString msg)
{
    ui->graphicsView->setScene(m_sceneCap);
    static QGraphicsTextItem* textItem = new QGraphicsTextItem();

    m_sceneCap->removeItem(textItem);
    textItem->setPos(ui->graphicsView->width()/2,ui->graphicsView->height()/2);
    textItem->setTextWidth(300);
    textItem->setFont(QFont("Times New Roman",18,2));
    textItem->setDefaultTextColor(QColor("#AD1F1F"));
    textItem->setPlainText(msg);
    m_sceneCap->addItem(textItem);
    ui->graphicsView->centerOn(textItem);
    m_sceneCap->update(textItem->boundingRect());
    ui->speedLabel->setText("");
    ui->courseLabel->setText("");
    ui->latLabel->setText("");
    ui->lonLabel->setText("");
    ui->gpsTimeLabel->setText("");
}

Widget::~Widget()
{
    delete m_logic;
    delete ui;
}
void Widget::setShipCoords()
{
    ui->graphicsView->setScene(m_scene);
    ui->speedLabel->setText(QString::number(m_logic->ship->getSpeed()));
    ui->courseLabel->setText(QString::number(m_logic->ship->getCourse()));
    int latInt;
    double latFracPart;
    int lonInt;
    double lonFracPart;
    latInt = m_logic->ship->getLatitude();
    latFracPart = (m_logic->ship->getLatitude()-latInt)*60;
    lonInt = m_logic->ship->getLongitude();
    lonFracPart = (m_logic->ship->getLongitude()-lonInt)*60;
    ui->latLabel->setText(QString::number(latInt)+","+QString::number(latFracPart,'f',5));
    ui->lonLabel->setText(QString::number(lonInt)+","+QString::number(lonFracPart,'f',5));
    ui->gpsTimeLabel->setText(m_logic->getGpsTime());


    m_scene->removeItem(m_shipItem);
    m_shipItem->setPosition(m_logic->ship->getLatitude(),m_logic->ship->getLongitude(),m_logic->ship->getPJ());
    m_shipItem->setCourse(m_logic->ship->getCourse());
    m_scene->addItem(m_shipItem);
    ui->graphicsView->centerOn(m_shipItem);
    m_scene->update(m_shipItem->boundingRect());

    m_scene->removeItem(m_shiptail);
    m_shiptail->addPoint(QPointF(m_logic->ship->getLatitude(),m_logic->ship->getLongitude()));
    m_scene->addItem(m_shiptail);
    m_scene->update(m_shiptail->boundingRect());
    m_scene->removeItem(m_gridItem);
    m_gridItem->setShipCoords(m_shipItem->getX(),m_shipItem->getY(),m_logic->ship->getPJ());
    m_scene->addItem(m_gridItem);
    m_scene->update(m_gridItem->boundingRect());
    m_scene->update(m_galsItem->boundingRect());

    m_scene->removeItem(m_galsItem);
    m_galsItem->setScale(m_scale);
    m_galsItem->setGals(m_logic->gals);
    m_scene->addItem(m_galsItem);
    m_scene->update(m_galsItem->boundingRect());
     m_scene->update();
}
void Widget::setGals()
{
    m_scene->removeItem(m_galsItem);
    m_galsItem->setGals(m_logic->gals);
    m_scene->addItem(m_galsItem);
    m_scene->update(m_galsItem->boundingRect());
    m_scene->update();
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
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    m_scale = (index+1) * 100000;
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

}
