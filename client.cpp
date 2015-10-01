
#include "client.h"

Client::Client():
    m_hostAddr("192.168.1.25"),
    m_hostPort(12345)
{
    m_server = new QTcpServer(this);
    m_soket = new QTcpSocket();
    m_timer = new QTimer();
    m_timerCheckData = new QTimer();
    m_connectState = false;

    connect(m_timerCheckData,SIGNAL(timeout()),this,SLOT(noData()));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(openConnection()));
    connect(m_soket,SIGNAL(connected()),this,SLOT(connected()));
    //connect(m_soket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(m_server,SIGNAL(newConnection()),this,SLOT(newConnect()));
    m_server->listen(QHostAddress::Any,m_hostPort);
    m_timer->start(1000);
    m_timerCheckData->start(105);

}
void Client::newConnect()
{
    qDebug()<<"new connection";
    m_soket = m_server->nextPendingConnection();
    m_connectState = true;
    connect(m_soket,SIGNAL(readyRead()),this,SLOT(readHostMessage()));
    connect(m_soket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    m_timer->stop();
}

void Client::noData()
{
    if(!m_connectState)
        emit readFail("ПОДКЛЮЧЕНИЕ ОТСУТСТВУЕТ");
    else
        emit readFail("НЕТ КООРДИНАТ");
}

void Client::openConnection()
{
   //qDebug()<<m_soket->bytesAvailable()<<m_soket->readAll();
    //m_soket->connectToHost(m_hostAddr,m_hostPort,QIODevice::ReadOnly);
}

void Client::connected()
{
    qDebug()<<"connected to "<<m_hostAddr<<":"<<m_hostPort;
    m_connectState = true;
    m_timer->stop();
}

void Client::readHostMessage()
{
   // qDebug()<<"get msg";
    m_timerCheckData->start(50000);
    //qDebug()<<m_soket->readAll();
    emit messageFormed(m_soket->readAll());

}

void Client::disconnected()
{
    m_connectState = false;
    m_timerCheckData->stop();
    emit readFail("ПОДКЛЮЧЕНИЕ ОТСУТСТВУЕТ");
    qDebug()<<"client disconnected";
    m_timer->start(100);
}
