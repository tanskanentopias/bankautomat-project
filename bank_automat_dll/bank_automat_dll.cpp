#include <QDebug>
#include "bank_automat_dll.h"
#include <QtSerialPort>


Bank_automat_dll::Bank_automat_dll(QWidget *parent)
    : QDialog(parent)

{
    serialPort = new QSerialPort(this);
    serialPort->setPortName("COM6");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->open(QIODevice::ReadWrite);


    connect(serialPort,SIGNAL(readyRead()),this,SLOT(Read_Data()));
}


void Bank_automat_dll::ignoreCharacters()
{
    serial = serial.simplified();
    serial = serial.remove("-");
    serial = serial.remove(" ");
    serial = serial.remove(">");

}

void Bank_automat_dll::Read_Data()
{
    if(serialPort->isOpen())
    {
        while (serialPort->bytesAvailable())
        {
            serial = serialPort->readAll();

            ignoreCharacters();

            qDebug()<<serial;
        }
    }
    emit sendCardToUi(serial);
}

