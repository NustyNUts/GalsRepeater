#include "galsitem.h"
#include <QVector>

GalsItem::GalsItem()
{
    m_gals = new QVector<Gals*>();
    m_scale = 500000;
}
void GalsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{

    for(int i=0;i<m_gals->size();i++)
    {
        QVector<QString>* tmpPJ;
        QVector<QPointF>* tmpPointVector;
        tmpPJ = m_gals->value(i)->getPJVector();
        tmpPointVector = m_gals->value(i)->getPointsVector();

        for(int j=0;j<(tmpPointVector->size()-1);j++)
        {
            //tmpPointVector->value(j)*=m_scale;
           // tmpPointVector->value(j+1)*=m_scale;
           // tmpPointVector->value(j).toPoint();
            //tmpPointVector->value(j+1).toPoint();
            painter->drawEllipse(tmpPointVector->value(j).rx(),-tmpPointVector->value(j).ry(),10,10);
            double x,y,x1,y1;
            x=tmpPointVector->value(j).rx()*m_scale;
            y=-tmpPointVector->value(j).ry()*m_scale;
            x1=tmpPointVector->value(j+1).rx()*m_scale;
            y1=-tmpPointVector->value(j+1).ry()*m_scale;
            qDebug()<<x<<y<<x1<<y1;
            painter->drawLine(x,y,x1,y1);
            painter->drawEllipse(x-5,y-5,10,10);
            painter->drawEllipse(x1-5,y1-5,10,10);

        }
    }
    qDebug()<<"draw gals";
}
void GalsItem::setGals(QVector<Gals *>* gals)
{
    int minX=INT_MAX;
    int minY=INT_MAX;
    int maxX=INT_MIN;
    int maxY=INT_MIN;
    m_gals = gals;
    for(int i=0;i<m_gals->size();i++)
    {
        QVector<QString>* tmpPJ;
        QVector<QPointF>* tmpPointVector;
        tmpPJ = m_gals->value(i)->getPJVector();
        tmpPointVector = m_gals->value(i)->getPointsVector();
        for(int j=0;j<tmpPointVector->size();j++)
        {
            QPointF tmpPoint;
            tmpPoint.setX(tmpPointVector->value(j).rx() * m_scale);
            tmpPoint.setY(tmpPointVector->value(j).ry() * m_scale);
            qDebug()<<tmpPoint<<"tmpPoint gals";
            if(tmpPoint.rx()<minX)
                minX=tmpPoint.rx();
            if(tmpPoint.ry()<minY)
                minY=tmpPoint.ry();

            if(tmpPoint.rx()>maxX)
                maxX=tmpPoint.rx();
            if(tmpPoint.ry()>maxY)
                maxY=tmpPoint.ry();
        }
    }
    m_boundRect.setRect(maxX,-maxY,maxX-minX,maxY-minY);
    qDebug()<<m_boundRect;
}
QRectF GalsItem::boundingRect() const
{
    qDebug()<<m_boundRect<<"gals bound";
    return m_boundRect;
}
