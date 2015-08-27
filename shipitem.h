#ifndef SHIPITEM_H
#define SHIPITEM_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDebug>

class ShipItem : public QGraphicsItem
{
    int m_x;
    int m_y;
    double m_lat;
    double m_lon;
    double m_scale;
    QString m_PJ;
public:
    ShipItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setPosition(double latitude,double longitude,QString PJ);
    void setScale(double scale);
    double getX()
    {
        return m_x;
    }

    double getY()
    {
        return m_y;
    }

};

#endif // SHIPITEM_H
