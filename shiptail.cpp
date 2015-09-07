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
    painter->setPen(QPen(QBrush("#B7A110"),1.0));
    if(m_shipTail->size()>=2)
        for(int i=1;i<m_shipTail->size();i++)
        {
            double x,y,x1,y1;
            x=m_shipTail->value(i-1).rx()*m_scale;
            y=m_shipTail->value(i-1).ry()*m_scale;
            x1=m_shipTail->value(i).rx()*m_scale;
            y1=m_shipTail->value(i).ry()*m_scale;
            painter->drawLine(x,-y,x1,-y1);
            painter->drawRect(m_boundRect);

        }
   // painter->drawRect(m_boundRect);
}

void ShipTail::addPoint(double lat,double lon,QString PJ)
{
    QPointF tmpPoint;
    double x,y;
    if(PJ[1] == 'N')
        y = lat;
    if(PJ[1] == 'S')
        y = -lat;
    if(PJ[0] == 'E')
        x = lon;
    if(PJ[0] == 'W')
        x = -lon;
    if(x<m_minX)
        m_minX = x;
    if(x>m_maxX)
        m_maxX = x;
    if(y<m_minY)
        m_minY = y;
    if(y>m_maxY)
        m_maxY = y;
    tmpPoint.setX(x);
    tmpPoint.setY(y);
    m_boundRect.setRect(m_minX,-m_minY,m_maxX-m_minX,m_maxY-m_minY);
    qDebug()<<m_boundRect;
    m_shipTail->append(tmpPoint);
}
