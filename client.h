/*
 * Класс принимает сообщения с внешнего источника и передает их далее
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QTimer>

class Client : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* m_soket;
    QString m_hostAddr;
    qint16 m_hostPort;
    QTimer* m_timer;
    QTimer* m_timerCheckData;
    bool m_connectState;

public:
    Client();
public slots:
    void openConnection();
    void connected();
    void readHostMessage();
    void disconnected();
    void noData();
signals:
    void messageFormed(QString msg);
    void readFail(QString msg);


};

#endif // CLIENT_H
