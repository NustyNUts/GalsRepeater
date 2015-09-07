#ifndef GALSITEM_H
#define GALSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QRectF>
#include <QVector>
#include "gals.h"

class GalsItem : public QGraphicsItem
{
    int m_scale;
    QRectF m_boundRect;
    QVector<Gals*>* m_gals;
    int minX;
    int minY;
    int maxX;
    int maxY;
public:
    GalsItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setScale(int scale)
    {
        m_scale = scale;
        m_boundRect.setRect(minX*m_scale,minY*m_scale,maxX*m_scale-minX*m_scale,maxY*m_scale-minY*m_scale);
    }
    void  setGals(QVector<Gals*>* gals);
};

#endif // GALSITEM_H
