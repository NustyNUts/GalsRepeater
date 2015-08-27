#include "gals.h"

Gals::Gals(QObject *parent) :
    QObject(parent)
{
    m_points = new QVector<QPointF>;
    m_pointsPJ = new QVector<QString>;
}
