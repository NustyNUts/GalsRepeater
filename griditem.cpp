#include "griditem.h"

GridItem::GridItem():
    m_scale(20000),
    m_shipX(0),
    m_shipY(0)
{
    m_dayNight = true;
}



void GridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    double tmpInt;
    double tmpFracPart;
    for(int i=((m_shipX-1000/2)/100)*100;i<((m_shipX+1000/2)/100)*100;i+=100)
    {
        if(m_dayNight)
            painter->setPen(QPen(QBrush("black"),0.2));
        else if(!m_dayNight)
            painter->setPen(QPen(QBrush("green"),0.2));
        painter->drawLine(i,-m_shipY+600/2,i,-m_shipY-600/2);
        tmpInt = (i/m_scale);
        tmpFracPart = ((i/(double)m_scale) - tmpInt )*60.0;
        if(i>m_shipX-700/2&&i<m_shipX+700)
        {
            if(m_dayNight)
                painter->setPen(QPen(QBrush("#F7BC22"),0.2));
            else if(!m_dayNight)
                painter->setPen(QPen(QBrush("green"),0.2));
            QChar tmpP;

            if(i<0)
                tmpP = 'W';
            else
                tmpP = 'E';
            QStaticText* text= new QStaticText;
            text->setText(QString::number(abs(tmpInt))+"°"+QString::number(fabs(tmpFracPart),'f',3)+tmpP+"'");
            painter->drawStaticText(i,-m_shipY-215,*text);
            painter->drawStaticText(i,-m_shipY+205,*text);
            delete text;
            painter->setPen("black");
        }
    }

    for(int i=((m_shipY-700/2)/100)*100;i<((m_shipY+700/2)/100)*100;i+=100)
    {
        if(m_dayNight)
            painter->setPen(QPen(QBrush("black"),0.2));
        else if(!m_dayNight)
            painter->setPen(QPen(QBrush("green"),0.2));
        painter->drawLine(((m_shipX-1000/2)/100)*100,-i,((m_shipX+1000/2)/100)*100,-i);
        tmpInt = (i/m_scale);
        tmpFracPart = ((i/(double)m_scale) - tmpInt )*60.0;
        if(i<m_shipY+200 && i>m_shipY-200)
        {
            QChar tmpJ;
            if(i<0)
                tmpJ = 'S';
            else
                tmpJ = 'N';
            QStaticText* text= new QStaticText;
            text->setText(QString::number(abs(tmpInt))+"°"+QString::number(fabs(tmpFracPart),'f',3)+tmpJ+"'");
            if(m_dayNight)
                painter->setPen(QPen(QBrush("#F7BC22"),0.2));
            else if(!m_dayNight)
                painter->setPen(QPen(QBrush("green"),0.2));
            painter->drawStaticText(m_shipX-360,-i-5,*text);
            painter->drawStaticText(m_shipX+320,-i+5,*text);
            painter->setPen("black");
            delete text;
        }
    }
    painter->setPen(QColor("red"));
    painter->drawRect(QRectF(m_shipX-1000, -m_shipY-1000,
                             2000, 2000));
    painter->setPen("black");
}

QRectF GridItem::boundingRect() const
{
    return QRectF(m_shipX-800, -m_shipY-600,
                  1600, 1600);
}
