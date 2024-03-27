#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pinAttemptsLeft(3)
    , state(1)
{
    ui->setupUi(this);

    connect(ui->numPad0, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);
    connect(ui->numPad1, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);
    connect(ui->numPad2, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);
    connect(ui->numPad3, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);
    connect(ui->numPad4, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);
    connect(ui->numPad5, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);
    connect(ui->numPad6, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);
    connect(ui->numPad7, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);
    connect(ui->numPad8, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);
    connect(ui->numPad9, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);
    connect(ui->numPadClear, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);
    connect(ui->numPadEnter, &QPushButton::clicked, this, &MainWindow::numPadClickHandler);

    connect(ui->rightButton1, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton1, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);

    //ui->pinLineEdit->setEchoMode(QLineEdit::Password);
    ui->cardNumLineEdit->hide();
    ui->pinLineEdit->hide();
    ui->cardNumberLabel->hide();
    ui->pinLabel->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cardNumberAndPin()
{
    ui->cardNumLineEdit->show();
    ui->pinLineEdit->show();
    ui->cardNumberLabel->show();
    ui->pinLabel->show();
}

void MainWindow::numPadClickHandler()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    currentNumPadKey = button->text();
    fillLineEdit();
}

void MainWindow::sideButtonClickHandler()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    currentSideButton = button->objectName();

    if (currentSideButton == "rightButton1") {
        cardNumberAndPin();
    }
    if (currentSideButton == "leftButton1") {
        reset();
    }
}

void MainWindow::fillLineEdit()
{
    switch (state) {
        case 1:
            if (currentNumPadKey == "CLR") {
                ui->cardNumLineEdit->clear();
                cardNumber.clear();
            } else if (currentNumPadKey == "OK" && cardNumber == correctCardNumber) {
                state = 2;
            } else if (currentNumPadKey != "OK") {
                cardNumber = cardNumber + currentNumPadKey;
                ui->cardNumLineEdit->setText(cardNumber);
            }
            break;
        case 2:
            if (currentNumPadKey == "CLR") {
                ui->pinLineEdit->clear();
                password.clear();
            } else if (currentNumPadKey == "OK" && password == correctPassword) {
                state = 0;
                ui->cardNumLineEdit->hide();
                ui->pinLineEdit->hide();
                ui->cardNumberLabel->hide();
                ui->pinLabel->hide();
            } else if (currentNumPadKey != "OK"){
                password = password + currentNumPadKey;
                ui->pinLineEdit->setText(password);
            }
            break;
        }
}

void MainWindow::reset()
{
    ui->cardNumLineEdit->hide();
    ui->cardNumLineEdit->clear();
    ui->pinLineEdit->hide();
    ui->pinLineEdit->clear();
    ui->cardNumberLabel->hide();
    ui->pinLabel->hide();
    state = 1;
    pinAttemptsLeft = 3;
    password.clear();
    cardNumber.clear();
    currentNumPadKey.clear();
    currentSideButton.clear();
}
