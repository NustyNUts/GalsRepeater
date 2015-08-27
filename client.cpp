
#include "client.h"

Client::Client():
    m_hostAddr("192.168.1.25"),
    m_hostPort(12345)
{
    m_soket = new QTcpSocket();
    m_timer = new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(openConnection()));
    connect(m_soket,SIGNAL(connected()),this,SLOT(connected()));
    connect(m_soket,SIGNAL(readyRead()),this,SLOT(readHostMessage()));
    connect(m_soket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    m_timer->start(100);

}

void Client::openConnection()
{
    m_soket->connectToHost(m_hostAddr,m_hostPort);
}

void Client::connected()
{
    qDebug()<<"connected to "<<m_hostAddr<<":"<<m_hostPort;
    m_timer->stop();
}

void Client::readHostMessage()
{
    emit messageFormed(m_soket->readAll());
}

void Client::disconnected()
{
    m_timer->start(100);
}
