#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QTime>
#include <QRegExp>
#include <QNmeaPositionInfoSource>
#include <QGeoPositionInfo>
#include <QGeoCoordinate>
#include "client.h"
#include "gals.h"
#include "ship.h"

class Logic : public QObject
{
    Q_OBJECT
private:

    QTime m_sysTime;
    QString m_gpsTime;
    Client* m_client;

public:
    explicit Logic(QObject *parent = 0);
    Ship* ship;
    QVector<Gals*>* gals;

    QString getGpsTime()
    {
        return m_gpsTime;
    }

signals:
    void updateShipPosition();
    void updateGals();
public slots:
    void getMsg(QString msg);

};

#endif // LOGIC_H
