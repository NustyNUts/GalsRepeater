#include "shiptail.h"

ShipTail::ShipTail()
{
    m_shipTail = new QVector<QPointF>;
    m_scale = 500000;
    m_minX=INT_MAX;
    m_minY=INT_MAX;
    m_maxX=INT_MIN;
    m_maxY=INT_MIN;
}
void ShipTail::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    painter->setPen(QPen(QBrush("#890C06"),1.0));
    if(m_shipTail->size()>=2)
        for(int i=1;i<m_shipTail->size();i++)
        {
            double x,y,x1,y1;
            x=m_shipTail->value(i-1).rx()*m_scale;
            y=m_shipTail->value(i-1).ry()*m_scale;
            x1=m_shipTail->value(i).rx()*m_scale;
            y1=m_shipTail->value(i).ry()*m_scale;
            painter->drawLine(x,-y,x1,-y1);

        }
}

void ShipTail::addPoint(QPointF point)
{
    if(point.rx()*m_scale<m_minX)
        m_minX = point.rx()*m_scale;
    if(point.rx()*m_scale>m_maxX)
        m_maxX = point.rx()*m_scale;
    if(point.ry()*m_scale<m_minY)
        m_minY = point.ry()*m_scale;
    if(point.ry()*m_scale>m_maxY)
        m_maxY = point.ry()*m_scale;
    m_boundRect = QRect(m_minX,-m_minY,m_maxX-m_minX+5,m_maxY-m_minY+5);
    if(m_shipTail->size()<=100)
        m_shipTail->push_front(point);
    else
    {
        m_shipTail->removeLast();
        m_shipTail->push_front(point);
    }
}
