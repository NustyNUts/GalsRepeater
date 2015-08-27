#include "shipitem.h"

ShipItem::ShipItem() :
    m_x(-1000),
    m_y(1000),
    m_scale(500000.0)
{
}

void ShipItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
         QWidget *widget)
{
    int k=20;
    painter->setPen(QPen(QBrush("#890C06"),2.0));
    painter->drawRect(m_x-k/2,-m_y-k/2,k,k);
    painter->drawLine(m_x-k/2,-m_y-k/2,m_x+k/2,-m_y+k/2);
    painter->drawLine(m_x-k/2,-m_y+k/2,m_x+k/2,-m_y-k/2);
    painter->drawLine(m_x,-m_y,m_x,-m_y-30);
    painter->drawLine(m_x,-m_y-30,m_x-k/2,-m_y-k/1.2);
    painter->drawLine(m_x,-m_y-30,m_x+k/2,-m_y-k/1.2);
    painter->drawLine(m_x,-m_y,m_x,-m_y+30);
}

QRectF ShipItem::boundingRect() const
{
    //qDebug()<<QRectF(m_x , -m_y-30 , 20, 60)<<"ship bound";
    return QRectF(m_x , -m_y-30 ,
                  20, 60);
}
void ShipItem::setPosition(double latitude,double longitude,QString PJ)
{
    m_PJ = PJ;
    if(m_PJ[0] == 'N')
        m_x = latitude * m_scale;
    else
        m_x = -latitude * m_scale;
    if(m_PJ[1] == 'E')
        m_y = longitude * m_scale;
    else
        m_y = -longitude * m_scale;
}
void ShipItem::setScale(double scale)
{
    m_scale = scale;
}
