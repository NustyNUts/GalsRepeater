#include "galsitem.h"
#include <QVector>

GalsItem::GalsItem()
{
    m_gals = new QVector<Gals*>();
    //m_scale = 20000;
    minX=INT_MAX;
    minY=INT_MAX;
    maxX=INT_MIN;
    maxY=INT_MIN;
    m_dayNight = true;
    showDev = true;
    deviation = 0.1/60;
}
void GalsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    double x,y,x1,y1;
    if(m_dayNight)
        painter->setPen(QPen(QBrush("#F7BC22"),1.5));
    else if(!m_dayNight)
        painter->setPen(QPen(QBrush("#F7BC22"),1.5));
    for(int i=0;i<m_gals->size();i++)
    {
        QVector<QString>* tmpPJ;
        QVector<QPointF>* tmpPointVector;
        tmpPJ = m_gals->value(i)->getPJVector();
        tmpPointVector = m_gals->value(i)->getPointsVector();

        for(int j=0;j<(tmpPointVector->size()-1);j++)
        {
            if(tmpPJ->value(j)[1]=='E')
                x=tmpPointVector->value(j).rx()*m_scale;
            if(tmpPJ->value(j)[1]=='W')
                x= -tmpPointVector->value(j).rx()*m_scale;
            if(tmpPJ->value(j)[0]=='N')
                y=-tmpPointVector->value(j).ry()*m_scale;
            if(tmpPJ->value(j)[0]=='S')
                y=tmpPointVector->value(j).ry()*m_scale;

            if(tmpPJ->value(j+1)[1]=='E')
                x1=tmpPointVector->value(j+1).rx()*m_scale;
            if(tmpPJ->value(j+1)[1]=='W')
                x1= -tmpPointVector->value(j+1).rx()*m_scale;
            if(tmpPJ->value(j+1)[0]=='N')
                y1=-tmpPointVector->value(j+1).ry()*m_scale;
            if(tmpPJ->value(j+1)[0] =='S')
                y1=tmpPointVector->value(j+1).ry()*m_scale;
            painter->drawLine(x,y,x1,y1);
            painter->setPen(QPen(QBrush("#F7BC22"),1.5,Qt::DashLine));
            if(showDev)
            {
                QPen pen;
                pen.setBrush(QBrush("#F7BC22"));
                pen.setStyle(Qt::DashLine);
                painter->setPen(pen);
                if(showDev)
                {
                    painter->drawLine(x+deviation*m_scale,y+deviation*m_scale,x1+deviation*m_scale,y1+deviation*m_scale);
                    painter->drawLine(x-deviation*m_scale,y-deviation*m_scale,x1-deviation*m_scale,y1-deviation*m_scale);
                }
            }
            painter->setPen(QPen(QBrush("#F7BC22"),1.5));
            painter->drawEllipse(x-5,y-5,10,10);
            painter->drawEllipse(x1-5,y1-5,10,10);
        }
    }
}
void GalsItem::setGals(QVector<Gals *>* gals)
{
    minX=INT_MAX;
    minY=INT_MAX;
    maxX=INT_MIN;
    maxY=INT_MIN;
    m_gals = gals;
    for(int i=0;i<m_gals->size();i++)
    {
        QVector<QString>* tmpPJ;
        QVector<QPointF>* tmpPointVector;
        tmpPJ = m_gals->value(i)->getPJVector();
        tmpPointVector = m_gals->value(i)->getPointsVector();
        for(int j=0;j<tmpPointVector->size();j++)
        {
            double x,y;
            if(tmpPJ->value(j)[1]=='E')
                x=tmpPointVector->value(j).rx();
            if(tmpPJ->value(j)[1]=='W')
                x= -tmpPointVector->value(j).rx();
            if(tmpPJ->value(j)[0]=='N')
                y=-tmpPointVector->value(j).ry();
            if(tmpPJ->value(j)[0]=='S')
                y=tmpPointVector->value(j).ry();
            if(x<minX)
                minX=x;
            if(y<minY)
                minY=y;
            if(x>maxX)
                maxX=x;
            if(y>maxY)
                maxY=y;
        }
        m_boundRect.setRect(minX*m_scale,minY*m_scale,maxX*m_scale-minX*m_scale,maxY*m_scale-minY*m_scale);
    }
}
QRectF GalsItem::boundingRect() const
{
    return m_boundRect;
}
