#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <math.h>

class GridItem : public QGraphicsItem
{
    int m_scale;
    int m_shipX;
    int m_shipY;
    QString m_PJ;
public:
    GridItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setScale(int scale)
    {
        m_scale = scale;
    }
    void setShipCoords(int x,int y,QString PJ)
    {
        m_PJ = PJ;
        m_shipX = x;
        m_shipY = y;
    }
};

#endif // GRIDITEM_H
