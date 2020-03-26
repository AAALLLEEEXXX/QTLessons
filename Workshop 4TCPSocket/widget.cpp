#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    setWindowTitle("Сервер");

    pTcpServer = new QTcpServer(this);
    pTcpSocket = nullptr;

    if(pTcpServer->listen(QHostAddress::LocalHost, 11111))
        lblServerState->setText("Listen");
    else
        lblServerState->setText("error");

    lblServerIP->setText(pTcpServer->serverAddress().toString());
    lblServerPort->setNum(pTcpServer->serverPort());

    connect(pTcpServer, &QTcpServer::newConnection,this,&Widget::progressingRequest);
}

void Widget::progressingRequest(){
    lblServerState->setText("connected");
    lblExchange->setText("request in process");
    pTcpSocket = pTcpServer->nextPendingConnection();
    connect(pTcpSocket,SIGNAL(readyRead()),SLOT(readyRead()));
    connect(pTcpSocket,&QTcpSocket::disconnected,pTcpSocket,&QTcpSocket::deleteLater);
}

void Widget::readyRead(){
    QByteArray ba;

    ba = pTcpSocket->readAll();
    lblExchange->setText("request to send file:" + ba);
    QFile file(ba);

    if(file.exists()){
        file.open(QFile::ReadOnly);
        lblFile->setText(ba);
        lblSize->setText(QString::number(file.size()));
        pTcpSocket->write(file.readAll());
        lblExchange->setText("file sended");
        file.close();
    }
    else
        lblExchange->setText("file doesn'nt exist");
}

Widget::~Widget()
{
}

