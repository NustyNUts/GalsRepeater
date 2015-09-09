#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QTime>
#include <QRegExp>
#include "client.h"
#include "gals.h"
#include "ship.h"

class Logic : public QObject
{
    Q_OBJECT
private:

    QTime m_sysTime;
    QString m_gpsTime;

    QTimer* timer;

public:
    explicit Logic(QObject *parent = 0);
    Ship* ship;
    QVector<Gals*>* gals;
    Client* client;
    QString getGpsTime()
    {
        return m_gpsTime;
    }

signals:
    void updateShipPosition();
    void updateGals(int i);
    void noData();
public slots:
    void getMsg(QString msg);

};

#endif // LOGIC_H
