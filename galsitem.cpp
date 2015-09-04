#include "galsitem.h"
#include <QVector>

GalsItem::GalsItem()
{
    m_gals = new QVector<Gals*>();
    m_scale = 500000;
    minX=INT_MAX;
    minY=INT_MAX;
    maxX=INT_MIN;
    maxY=INT_MIN;
}
void GalsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    double x,y,x1,y1;
    painter->setPen(QPen(QBrush("#890C06"),1.5));
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


            if(tmpPJ->value(j)[0]=='N')
                x=tmpPointVector->value(j).rx()*m_scale;
            else
                x= -tmpPointVector->value(j).rx()*m_scale;
            if(tmpPJ->value(j)[1]=='E')
                y=-tmpPointVector->value(j).ry()*m_scale;
            else
                y=tmpPointVector->value(j).ry()*m_scale;

            if(tmpPJ->value(j+1)[0]=='N')
                x1=tmpPointVector->value(j+1).rx()*m_scale;
            else
                x1= -tmpPointVector->value(j+1).rx()*m_scale;
            if(tmpPJ->value(j+1)[1]=='E')
                y1=-tmpPointVector->value(j+1).ry()*m_scale;
            else
                y1=tmpPointVector->value(j+1).ry()*m_scale;
            //qDebug()<<x<<y<<x1<<y1;
            painter->drawLine(x,y,x1,y1);
            painter->drawEllipse(x-5,y-5,10,10);
            painter->drawEllipse(x1-5,y1-5,10,10);
//            qDebug()<<x<<y<<x1<<y1<<"x,y,x1,y1";

        }

    }
    //painter->drawRect(m_boundRect);
}
void GalsItem::setGals(QVector<Gals *>* gals)
{

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
            double x,y;
            if(tmpPJ->value(j)[0]=='N')
                x=tmpPointVector->value(j).rx()*m_scale;
            else
                x= -tmpPointVector->value(j).rx()*m_scale;
            if(tmpPJ->value(j)[1]=='E')
                y=-tmpPointVector->value(j).ry()*m_scale;
            else
                y=tmpPointVector->value(j).ry()*m_scale;

            tmpPoint.setX(x);
            tmpPoint.setY(y);
            qDebug()<<x<<y<<"tmpPoint gals";
            if(x<minX)
                minX=x;
            if(y<minY)
                minY=y;
            if(x>maxX)
                maxX=x;
            if(y>maxY)
                maxY=y;
        }
        m_boundRect.setRect(minX,minY,maxX-minX,maxY-minY);
    }




}
QRectF GalsItem::boundingRect() const
{
    //qDebug()<<m_boundRect<<"gals bound";
    return m_boundRect;
}
