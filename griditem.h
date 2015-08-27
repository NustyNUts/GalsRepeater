#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDebug>

class GridItem : public QGraphicsItem
{
    int m_scale;
    int m_shipX;
    int m_shipY;
public:
    GridItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setScale(int scale)
    {
        m_scale = scale;
    }
    void setShipCoords(int x,int y)
    {
        m_shipX = x;
        m_shipY = y;
    }
};

#endif // GRIDITEM_H
