#ifndef SHIP_H
#define SHIP_H

#include <QObject>

class Ship : public QObject
{
    Q_OBJECT
    double m_course;
    double m_longitude;//dolgota
    QString m_lonP;
    double m_latitude;//shirota
    QString m_latJ;
    double m_speed;
public:
    explicit Ship(QObject *parent = 0);

    //--------------------------
    void setCourse(double course)
    {
        m_course = course;
    }
    double getCourse()
    {
        return m_course;
    }
    //--------------------------
    void setLatitude(double latitude,QString J)
    {
        m_latJ = J;
        m_latitude = latitude;

    }
    double getLatitude()
    {
        return m_latitude;
    }
    //--------------------------
    void setLongitude(double longitude,QString P)
    {
        m_longitude = longitude;
        m_lonP = P;
    }
    double getLongitude()
    {
        return m_longitude;
    }
    //-------------------------
    void setSpeed(double speed)
    {
        m_speed = speed;
    }
    double getSpeed()
    {
        return m_speed;
    }

signals:

public slots:

};

#endif // SHIP_H
