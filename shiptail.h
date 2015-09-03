#ifndef SHIPTAIL_H
#define SHIPTAIL_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QVector>
#include <QPointF>
class ShipTail : public QGraphicsItem
{
    QVector<QPointF>* m_shipTail;
    QRect m_boundRect;
    int m_scale;
    int m_minX;
    int m_maxX;
    int m_maxY;
    int m_minY;
public:
    ShipTail();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const
    {
        return m_boundRect;
    }
    void addPoint(QPointF point);

};

#endif // SHIPTAIL_H
