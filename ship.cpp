#include "ship.h"

Ship::Ship(QObject *parent) :
    QObject(parent),
    m_course(0.0),
    m_longitude(0.0),
    m_latitude(0.0),
    m_lonP(""),
    m_latJ("")
{
}

