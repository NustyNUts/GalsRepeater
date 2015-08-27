#include "griditem.h"

GridItem::GridItem():
    m_scale(500000),
    m_shipX(7),
    m_shipY(0)
{
}



void GridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    double tmpInt;
    double tmpFracPart;
    for(int i=((m_shipX-1000/2)/100)*100;i<((m_shipX+1000/2)/100)*100;i+=100)
    {
        painter->setPen(QPen(QBrush("black"),0.2));
        painter->drawLine(i,-m_shipY+600/2,i,-m_shipY-600/2);
        tmpInt = (i/m_scale);
        tmpFracPart = ((i/(double)m_scale) - tmpInt )*60.0;
        if(i>m_shipX-700/2&&i<m_shipX+700)
        {
            painter->setPen(QColor("#F7BC22"));
            painter->drawText(i,-m_shipY-200,QString::number(tmpInt)+","+QString::number(tmpFracPart,'f',3));
            painter->drawText(i,-m_shipY+220,QString::number(tmpInt)+","+QString::number(tmpFracPart,'f',3));
            painter->setPen("black");
        }
    }

    for(int i=((m_shipY-700/2)/100)*100;i<((m_shipY+700/2)/100)*100;i+=100)
    {
        painter->setPen(QPen(QBrush("black"),0.2));
        painter->drawLine(((m_shipX-1000/2)/100)*100,-i,((m_shipX+1000/2)/100)*100,-i);
        tmpInt = (i/m_scale);
        tmpFracPart = ((i/(double)m_scale) - tmpInt )*60.0;
        if(i<m_shipY+200 && i>m_shipY-200)
        {
            painter->setPen(QColor("#F7BC22"));
            painter->drawText(m_shipX-360,-i+20,QString::number(tmpInt)+","+QString::number(tmpFracPart,'f',3));
            painter->drawText(m_shipX+320,-i+20,QString::number(tmpInt)+","+QString::number(tmpFracPart,'f',3));
            painter->setPen("black");
        }
    }
}

QRectF GridItem::boundingRect() const
{
    return QRectF(m_shipX-800, -m_shipY-600,
                  1600, 1600);
}
