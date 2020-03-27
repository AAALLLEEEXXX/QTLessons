#include "widget.h"
#include <QFileDialog>

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
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.cpp *.h");
    QFile file(str);
    QString fileName;
    int i;
    for(i = str.length(); (str[i] != '\\') && (str[i] != '/') && i >= 0; --i);

    while (str[++i] != '\0')
        fileName += str[i];

    lblExchange->setText("request to send file:" + fileName);

    if(file.exists()){
        file.open(QFile::ReadOnly);
        lblFile->setText(fileName);
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

