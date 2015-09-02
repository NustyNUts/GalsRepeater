#ifndef SHIPITEM_H
#define SHIPITEM_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <math.h>

class ShipItem : public QGraphicsItem
{
    double m_x;
    double m_y;
    double m_lat;
    double m_lon;
    double m_scale;
    double m_angle;
    QRect m_boundrect;
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
    void setCourse(double course)
    {
        m_angle = course;
    }
};

#endif // SHIPITEM_H
