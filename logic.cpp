#include "logic.h"

Logic::Logic(QObject *parent) :
    QObject(parent)
{
    client = new Client();
    ship = new Ship();
    gals = new QVector<Gals*>();
    connect(client,SIGNAL(messageFormed(QString)),this,SLOT(getMsg(QString)));
}

void Logic::getMsg(QString msg)
{
    QRegExp regExp;
    regExp.setPattern("(\\d\\d)(\\d\\d)(\\d\\d).....(\\D).(\\d\\d)(\\d\\d.\\d{0,10}).(\\D).(\\d\\d\\d)(\\d\\d.\\d{0,10}).(\\D).(\\d{0,4}.\\d{0,4}).(\\d{0,3}.\\d{0,5})");
    regExp.indexIn(msg);
    if(regExp.cap(0)!="")
    {
        m_gpsTime = regExp.cap(1)+":"+regExp.cap(2)+":"+regExp.cap(3);
        if(regExp.cap(4)=="A")//dostovernost'?
        {
            ship->setLongitude(regExp.cap(8).toDouble()+regExp.cap(9).toDouble()/60,regExp.cap(10));
            ship->setLatitude(regExp.cap(5).toDouble()+regExp.cap(6).toDouble()/60,regExp.cap(7));
            ship->setSpeed(regExp.cap(11).toDouble());
            ship->setCourse(regExp.cap(12).toDouble());
            emit updateShipPosition();
        }
    }
    else
    {
        QStringList strList;
        strList = msg.split(",");
        if(strList[0]=="$GL")
        {
            if(strList[1] == "0")
            {
                gals->clear();
                emit updateGals();
                return;
            }
            Gals* tmpGals= new Gals();
            tmpGals->setNumGals(strList[1].toInt());
            for(int i = 2;i<=strList.size()-4;i+=4)
            {
                QRegExp regExpLat;
                QRegExp regExpLon;
                regExpLat.setPattern("(\\d\\d)(\\d\\d.\\d{0,6})");
                regExpLon.setPattern("(\\d\\d\\d)(\\d\\d.\\d{0,6})");
                regExpLat.indexIn(" "+strList[i]);
                regExpLon.indexIn("d"+strList[i+2]);
                qDebug()<<strList[i+2];
                qDebug()<<regExpLon.cap(1)<<regExpLon.cap(2)<<"reg";//.toDouble()+regExpLat.cap(2).toDouble()/60<<regExpLon.cap(1).toDouble()+regExpLon.cap(2).toDouble()/60;
                tmpGals->addPoint(QPointF(regExpLon.cap(1).toDouble()+regExpLon.cap(2).toDouble()/60,regExpLat.cap(1).toDouble()+regExpLat.cap(2).toDouble()/60),strList[i+1]+strList[i+3]);// if degree.min
                //tmpGals->addPoint(QPointF(strList[i].toDouble(),strList[i+2].toDouble()),strList[i+1]+strList[i+3]); //if degree
            }
            gals->append(tmpGals);
            emit updateGals();
        }
    }

}
//("$GL", "1", "0560.221", "N", "01502.567", "J", "0560.221", "N", "01502.567", "J", "0560.221", "N", "01502.567", "J", "0560.221", "N", "01502.567", "J")
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
