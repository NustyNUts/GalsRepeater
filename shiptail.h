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
    QRectF m_boundRect;
    int m_scale;
    double m_minX;
    double m_maxX;
    double m_maxY;
    double m_minY;
public:
    ShipTail();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const
    {
        return QRectF(m_minX*m_scale,-m_minY*m_scale,m_maxX*m_scale-m_minX*m_scale,m_maxY*m_scale-m_minY*m_scale);
    }
    void addPoint(double lat,double lon, QString PJ);

};

#endif // SHIPTAIL_H
