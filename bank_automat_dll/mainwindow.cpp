#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->nappi1,SIGNAL(clicked(bool)),
            this,SLOT(handleInserCardClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleInserCardClick()
{
    qDebug()<<"handleInsertCardClick funktiossa";
    bankPtr = new Bank_automat_dll(this);
    connect(bankPtr,SIGNAL(sendCardNumToMain(short)),
            this,SLOT(handleCardNumberRead(short)));
    bankPtr->show();



}

void MainWindow::handleCardNumberRead(short n)
{
    qDebug()<<"MainWindow handleCardNumberRead funktiossa";
    qDebug()<<"numero on = "<<n;
    cardNumber = n;
    ui->CurrentCardNumLineEdit->setText(QString::number(n));
    delete bankPtr;
}

void MainWindow::handlePinNumberRead(short)
{

}

