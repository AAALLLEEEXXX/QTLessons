#include "clientform.h"
#include <QHostAddress>

Clientform::Clientform(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    setWindowTitle("Клиент");
    pTcpSocket = new QTcpSocket(this);
    if(pTcpSocket->bind(QHostAddress::LocalHost))
        lblSocketState->setText("binded");



    connect(btnReceiveFile, &QToolButton::clicked,[=](){
        pTcpSocket->connectToHost(QHostAddress::LocalHost, 11111);
    });

    connect(pTcpSocket, &QTcpSocket::connected,this,[&](){
        lblSocketState->setText("connected");
        QByteArray ba("ui_clientform.h");
        pTcpSocket->write(ba);
        lblExchange->setText("filename sender");
    });

    connect(pTcpSocket, SIGNAL(readyRead()),SLOT(readyRead()));
}

Clientform::~Clientform()
{
    pTcpSocket->close();
}

void Clientform::readyRead(){
    textBrowser->setText(pTcpSocket->readAll());
    lblExchange->setText("file received");
    pTcpSocket->close();
}
