#ifndef GALS_H
#define GALS_H

#include <QObject>
#include <QVector>
#include <QPointF>

class Gals : public QObject
{
    Q_OBJECT
    int galsNum;
    QVector<QString>* m_pointsPJ;
    QVector<QPointF>* m_points;
public:
    explicit Gals(QObject *parent = 0);
    void addPoint(QPointF pt, QString PJ)
    {
        m_points->push_back(pt);
        m_pointsPJ->push_back(PJ);
    }

    void setNumGals(int num)
    {
        galsNum = num;
    }

    QVector<QString>* getPJVector()
    {
        return m_pointsPJ;
    }
    QVector<QPointF>* getPointsVector()
    {
        return m_points;
    }

signals:

public slots:

};

#endif // GALS_H
