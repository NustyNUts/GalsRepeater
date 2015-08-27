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
public:
    GalsItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setScale(int scale)
    {
        m_scale = scale;
    }
    void  setGals(QVector<Gals*>* gals);
};

#endif // GALSITEM_H
