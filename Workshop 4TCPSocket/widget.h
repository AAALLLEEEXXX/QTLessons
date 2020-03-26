#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include "ui_widget.h"


class Widget : public QWidget, private Ui::Widget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    virtual ~Widget();

    QTcpServer *pTcpServer;

    QTcpSocket *pTcpSocket;

public slots:
    void progressingRequest();
    void readyRead();
};
#endif // WIDGET_H
