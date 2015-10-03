/*
 * класс организует общение с пользователем, отрисовывает судно, текущий галс.
 *  Преобразует координаты из географических в реальные(используемые для отрисовки)
 */
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTextBlockFormat>
#include <QTextCursor>

#include "griditem.h"
#include "shipitem.h"
#include "galsitem.h"
#include "logic.h"
#include "shiptail.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
private:
    int m_scale;
    QString planeName;
    GridItem* m_gridItem;
    QGraphicsScene* m_scene;
    QGraphicsScene* m_sceneCap;
    Logic* m_logic;
    ShipTail* m_shiptail;
    ShipItem* m_shipItem;
    GalsItem* m_galsItem;
    bool m_dayNight;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

public slots:
    void setShipCoords();
    void setGals(int checkGals);
    void noData(QString msg);
    void setPlaneName(QString str);
    void setDeviation(double dev);



private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
