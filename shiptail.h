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
    bool m_dayNight;
public:
    ShipTail();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const
    {
        //qDebug()<<QRectF(m_minX*m_scale-10,m_minY*m_scale-10,m_maxX*m_scale-m_minX*m_scale+20,m_maxY*m_scale-m_minY*m_scale+20);
        return QRectF(m_minX*m_scale-10,-m_maxY*m_scale-10,m_maxX*m_scale-m_minX*m_scale+20,m_maxY*m_scale-m_minY*m_scale+20);
    }
    void addPoint(double lat,double lon, QString PJ);
    void setTailScale(double scale)
    {
        m_scale = scale;
    }

};

#endif // SHIPTAIL_H
