#ifndef BANK_AUTOMAT_DLL_H
#define BANK_AUTOMAT_DLL_H

#include "bank_automat_dll_global.h"
#include <QDialog>
#include <QByteArray>
#include <QSerialPort>

namespace Ui {
class Bank_automat_dll;
}

class BANK_AUTOMAT_DLL_EXPORT Bank_automat_dll : public QDialog
{
    Q_OBJECT

public:
    explicit Bank_automat_dll(QWidget *parent = nullptr);

    void ignoreCharacters();

signals:
    void sendCardToUi(QString);

private slots:
    void Read_Data();

private:
    QSerialPort *serialPort;
    QString serial;
};

#endif // BANK_AUTOMAT_DLL_H
