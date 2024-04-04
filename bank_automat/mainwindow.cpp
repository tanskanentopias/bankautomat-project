#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pinAttemptsLeft(3)
    , state(0)
    , window(0)
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
    connect(ui->rightButton5, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton1, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton2, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton3, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton4, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton5, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);

    //ui->pinLineEdit->setEchoMode(QLineEdit::Password);
    hideElements();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cardNumberAndPin()
{
    state = 1;
    ui->titleLabel->setText("Insert card");
    ui->rightLabel1->setText("RESET");
    ui->cardNumLineEdit->show();
    ui->pinLineEdit->show();
    ui->cardNumberLabel->show();
    ui->pinLabel->show();
    window = 1;
}

void MainWindow::showMenu()
{
    hideElements();
    clearLabels();
    ui->titleLabel->setText("Welcome User");
    ui->leftLabel2->setText("WITHDRAW");
    ui->leftLabel1->setText("SHOW EVENTS");
    ui->rightLabel1->setText("LOG OUT");
    window = 2;
}

void MainWindow::showWithdrawMenu()
{
    hideElements();
    clearLabels();
    ui->titleLabel->setText("Select amount to withdraw");
    QTimer::singleShot(0, this, [this]() {
        ui->withdrawLineEdit->clear();
    });
    ui->leftLabel5->setText("20 €");
    ui->leftLabel4->setText("40 €");
    ui->leftLabel3->setText("50 €");
    ui->leftLabel2->setText("100 €");
    ui->leftLabel1->setText("OTHER");
    ui->rightLabel1->setText("BACK");
    ui->withdrawLabel->show();
    ui->withdrawLineEdit->show();
    window = 3;
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

    if (currentSideButton == "leftButton1" && window == 0) {
        cardNumberAndPin();
        ui->leftLabel1->setText("");
    }
    if (currentSideButton == "rightButton1" && window == 1) {
        reset();
    }
    if (currentSideButton == "rightButton1" && window == 2) {
        reset();
        //jotain token-reset juttua tähän jos tarvii
    }
    if (currentSideButton == "leftButton2" && window == 2) {
        clearLabels();
        showWithdrawMenu();
    }
    if (currentSideButton == "rightButton1" && window == 3) {
        clearLabels();
        showMenu();
    }
    if (currentSideButton == "leftButton5" && window == 3) {
        ui->withdrawLineEdit->setText("20");
        wasOtherChosen = false;
    }
    if (currentSideButton == "leftButton4" && window == 3) {
        ui->withdrawLineEdit->setText("40");
        wasOtherChosen = false;
    }
    if (currentSideButton == "leftButton3" && window == 3) {
        ui->withdrawLineEdit->setText("50");
        wasOtherChosen = false;
    }
    if (currentSideButton == "leftButton2" && window == 3) {
        ui->withdrawLineEdit->setText("100");
        wasOtherChosen = false;
    }
    if (currentSideButton == "leftButton1" && window == 3) {
        wasOtherChosen = true;
        ui->withdrawLineEdit->clear();
        withdrawAmount.clear();
    }
    if (currentSideButton == "rightButton5") {
        qDebug() << window << ui->withdrawLineEdit->text() << withdrawAmount;
    }
}

void MainWindow::fillLineEdit()
{
    if (window == 1) {
        switch (state) {
            case 1:
                if (currentNumPadKey == "CLR") {                //Kortin numero tulee lukijalta, pitää muuttaa
                    ui->cardNumLineEdit->clear();
                    cardNumber.clear();
                } else if (currentNumPadKey == "OK") {
                    checkCardNumber();
                } else {
                    cardNumber = cardNumber + currentNumPadKey;
                    ui->cardNumLineEdit->setText(cardNumber);
                }
                break;
            case 2:
                if (currentNumPadKey == "CLR") {
                    ui->pinLineEdit->clear();
                    password.clear();
                } else if (currentNumPadKey == "OK") {
                    checkPassword();
                } else {
                    password = password + currentNumPadKey;
                    ui->pinLineEdit->setText(password);
                }

                break;
            }
    }
    if (window == 3 && wasOtherChosen == true) {
        if (currentNumPadKey == "CLR") {
            ui->withdrawLineEdit->clear();
            withdrawAmount.clear();
        } else if (currentNumPadKey == "OK") {
            //uus ikkuna, jossa esim "Nostit 20 e" jne
        } else {
            withdrawAmount = withdrawAmount + currentNumPadKey;
            ui->withdrawLineEdit->setText(withdrawAmount);
            qDebug() << withdrawAmount;
        }
    }
}

void MainWindow::reset()
{
    hideElements();
    state = 0;
    window = 0;
    pinAttemptsLeft = 3;
    currentNumPadKey.clear();
    currentSideButton.clear();
    clearLabels();
    ui->leftLabel1->setText("INSERT CARD");
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
    withdrawAmount.clear();
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

void MainWindow::checkCardNumber()
{
    if (cardNumber == correctCardNumber) {
        state = 2;
        qDebug() << "Card OK";
        ui->titleLabel->setText("Insert PIN");
    } else {
        ui->cardNumLineEdit->clear();
        cardNumber.clear();
        qDebug() << "Incorrect card number";
    }
}

void MainWindow::checkPassword()
{
    if (password == correctPassword) {
        state = 0;
        hideElements();
        showMenu();
    } else {
        ui->pinLineEdit->clear();
        password.clear();
        pinAttemptsLeft--;
        if (pinAttemptsLeft == 0) {
            MainWindow::close();    //Temporary
        }
        qDebug() << "Wrong PIN";
        qDebug() << "Attempts left:" << pinAttemptsLeft;
    }
}
