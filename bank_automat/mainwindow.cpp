#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pinAttemptsLeft(3)
    , state(0)
    , window(0)
    , withdrawAmount(0)
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
    connect(ui->leftButton2, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);

    //ui->pinLineEdit->setEchoMode(QLineEdit::Password);
    hideElements();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cardNumberAndPin()
{
    window = 1;
    state = 1;
    ui->titleLabel->setText("Insert card");
    ui->cardNumLineEdit->show();
    ui->pinLineEdit->show();
    ui->cardNumberLabel->show();
    ui->pinLabel->show();
}

void MainWindow::showMenu()
{
    window = 2;
    hideElements();
    clearLabels();
    ui->titleLabel->setText("Welcome User");
    ui->leftLabel2->setText("WITHDRAW");
    ui->leftLabel1->setText("SHOW EVENTS");
    ui->rightLabel1->setText("LOG OUT");
}

void MainWindow::showWithdrawMenu()
{
    window = 3;
    hideElements();
    clearLabels();
    ui->titleLabel->setText("Select amount to withdraw");
    ui->leftLabel5->setText("20 €");
    ui->leftLabel4->setText("40 €");
    ui->leftLabel3->setText("50 €");
    ui->leftLabel2->setText("100 €");
    ui->leftLabel1->setText("OTHER");
    ui->rightLabel1->setText("BACK");
    ui->withdrawLabel->show();
    ui->withdrawLineEdit->show();
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

    if (currentSideButton == "leftButton1" && ui->leftLabel1->text() == "INSERT CARD") {
        cardNumberAndPin();
        ui->leftLabel1->setText("");
    }
    if (currentSideButton == "rightButton1" && ui->rightLabel1->text() == "RESET") {
        reset();
    }
    if (currentSideButton == "rightButton1" && ui->rightLabel1->text() == "LOG OUT") {
        reset();
        //jotain token-reset juttua tähän jos tarvii
    }
    if (currentSideButton == "leftButton2" && ui->leftLabel2->text() == "WITHDRAW") {
        clearLabels();
        showWithdrawMenu();
    }
    if (currentSideButton == "rightButton1" && ui->rightLabel1->text() == "BACK" && window == 3) {
        clearLabels();
        showMenu();
    }
}

void MainWindow::fillLineEdit()
{
    switch (state) {
        case 1:
            if (currentNumPadKey == "CLR") {                //Kortin numero tulee lukijalta
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
            } else if (currentNumPadKey != "OK"){
                password = password + currentNumPadKey;
                ui->pinLineEdit->setText(password);
            }
            if (currentNumPadKey == "OK" && password != correctPassword) {
                pinAttemptsLeft --;
                ui->pinLineEdit->clear();
                password.clear();
                qDebug() << pinAttemptsLeft;
                if (pinAttemptsLeft == 0) {
                    //Tähän joku ikkuna, jossa kerrotaan että tuuhioit salasanan ja lockout
                }
            } else if (currentNumPadKey == "OK" && password == correctPassword) {
                state = 0;
                hideElements();
                showMenu();
            }
            break;
        }
}

void MainWindow::reset()
{
    hideElements();
    state = 0;
    pinAttemptsLeft = 3;
    currentNumPadKey.clear();
    currentSideButton.clear();
    clearLabels();
    ui->leftLabel1->setText("INSERT CARD");
    ui->rightLabel1->setText("RESET");
    ui->titleLabel->setText("Pankkiautomaatti");
}

void MainWindow::hideElements()
{
    ui->cardNumLineEdit->hide();
    ui->pinLineEdit->hide();
    ui->cardNumberLabel->hide();
    ui->pinLabel->hide();
    ui->cardNumLineEdit->clear();
    cardNumber.clear();
    ui->pinLineEdit->clear();
    password.clear();
    ui->withdrawLineEdit->hide();
    ui->withdrawLineEdit->clear();
    ui->withdrawLabel->hide();
}

void MainWindow::clearLabels()
{
    ui->leftLabel1->clear();
    ui->leftLabel2->clear();
    ui->leftLabel3->clear();
    ui->leftLabel4->clear();
    ui->leftLabel5->clear();
    ui->rightLabel1->clear();
    ui->rightLabel2->clear();
    ui->rightLabel3->clear();
    ui->rightLabel4->clear();
    ui->rightLabel5->clear();
    ui->titleLabel->clear();
}
