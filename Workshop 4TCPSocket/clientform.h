#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include "ui_clientform.h"
#include <QTcpSocket>

class Clientform : public QWidget, private Ui::Clientform
{
    Q_OBJECT

public:
    explicit Clientform(QWidget *parent = nullptr);
    virtual ~Clientform();

private:
    QTcpSocket *pTcpSocket;
public slots:
    void readyRead();
};

#endif // CLIENTFORM_H
