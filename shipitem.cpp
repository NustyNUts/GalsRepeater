#include "shipitem.h"

ShipItem::ShipItem() :
    m_x(-1000),
    m_y(1000),
    m_scale(20000.0),
    m_angle(0)
{
}

void ShipItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
         QWidget *widget)
{
//    m_x=30;
//    m_y=30;
    int k=20;
//    double angle;
//    angle =45;
//    angle=angle*(M_PI/180);
    painter->setPen(QPen(QBrush("#890C06"),2.0));
//    painter->save();
//    qDebug()<<m_x<<m_y<<"m_x and m_y";
//   // painter->drawRect(m_x-k/2,-m_y-k/2,k,k);
//    //painter->drawLine(m_x-k/2,-m_y-k/2,m_x+k/2,-m_y+k/2);
//    //painter->drawLine(m_x-k/2,-m_y+k/2,m_x+k/2,-m_y-k/2);
//    double x,y;
//    qDebug()<<cos(angle);
//    m_y=-m_y;
//    x=m_x*cos(angle)-(m_y-30)*sin(angle);
//    y=m_x*sin(angle)+(m_y-30)*cos(angle);
//    qDebug()<<x<<y<<"x and y";
//    painter->drawLine(m_x,m_y, x,y);
//    painter->drawLine(m_x,m_y,m_x,m_y-30);
    painter->drawEllipse(m_x-k/2,-m_y-k/2,k,k);
    painter->drawLine(m_x-k/2,-m_y,m_x+k/2,-m_y);
    painter->drawLine(m_x,-m_y-k/2,m_x,-m_y+k/2);
    double angle,angle1;
    double z;
    int j;

        angle = (m_angle-90)*(M_PI/180);
        angle1 = (m_angle+90)*(M_PI/180);
        painter->drawLine(m_x,-m_y,m_x + cos(-angle)*30,-m_y-sin(-angle)*30);
        painter->drawLine(m_x,-m_y,m_x + cos(-angle1)*30,-m_y-sin(-angle1)*30);
        painter->drawLine(m_x + cos(-angle)*30,-m_y-sin(-angle)*30,m_x + cos(-angle-M_PI/6)*15,-m_y-sin(-angle-M_PI/6)*15);
        painter->drawLine(m_x + cos(-angle)*30,-m_y-sin(-angle)*30,m_x + cos(-angle+M_PI/6)*15,-m_y-sin(-angle+M_PI/6)*15);

//    painter->drawLine(m_x,-m_y,m_x,-m_y-30);
//    painter->drawLine(m_x,-m_y-30,m_x-k/2,-m_y-k/1.2);
//    painter->drawLine(m_x,-m_y-30,m_x+k/2,-m_y-k/1.2);
//    painter->drawLine(m_x,-m_y,m_x,-m_y+30);
//    qDebug()<<m_x<<m_y<<"m_x,m_y";
}
//x' = x \cos \theta \mp y \sin \theta\,,
//y' = \pm x \sin \theta + y \cos \theta\,.

QRectF ShipItem::boundingRect() const
{
    //qDebug()<<QRectF(m_x , -m_y-30 , 20, 60)<<"ship bound";
//    return QRectF(m_x , -m_y,
//                  0, 0);
    return m_boundrect;
}
void ShipItem::setPosition(double latitude,double longitude,QString PJ)
{
    m_PJ = PJ;
    if(m_PJ[1] == 'N')
        m_y = latitude * m_scale;
    if(m_PJ[1]=='S')
        m_y = -latitude * m_scale;
    if(m_PJ[0] == 'E')
        m_x = longitude * m_scale;
    if(m_PJ[0] == 'W')
        m_x = -longitude * m_scale;
       // qDebug()<<m_x<<m_y<<"ship coords";
     m_boundrect.setRect(m_x-10,-m_y-30,20,60);
}
void ShipItem::setScale(double scale)
{
    m_scale = scale;
}
