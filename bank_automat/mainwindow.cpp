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

    //ui->lineEdit3->setEchoMode(QLineEdit::Password);
    hideElements();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLoginMenu()
{
    hideElements();
    clearLabels();
    state = 1;
    ui->titleLabel->setText("Insert card");
    ui->rightLabel1->setText("RESET");
    ui->lineEdit2->show();
    ui->lineEdit3->show();
    ui->centerLabel2->show();
    ui->centerLabel2->setText("Card Number");
    ui->centerLabel3->show();
    ui->centerLabel3->setText("PIN");
    window = 1;
}

void MainWindow::showMenu()
{
    hideElements();
    clearLabels();
    ui->titleLabel->setText("Welcome User");
    ui->leftLabel3->setText("WITHDRAW");
    ui->leftLabel2->setText("SHOW BALANCE");
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
        ui->lineEdit1->clear();
        withdrawAmount.clear();
    });
    ui->leftLabel5->setText("20 €");
    ui->leftLabel4->setText("40 €");
    ui->leftLabel3->setText("50 €");
    ui->leftLabel2->setText("100 €");
    ui->leftLabel1->setText("OTHER");
    ui->rightLabel1->setText("BACK");
    ui->centerLabel1->show();
    ui->centerLabel1->setText("Amount");
    ui->lineEdit1->show();
    window = 3;
}

void MainWindow::showBalanceMenu()
{
    hideElements();
    clearLabels();
    ui->titleLabel->setText("Account Balance");
    ui->rightLabel1->setText("BACK");
    ui->centerLabel1->show();
    ui->centerLabel1->setText("Balance");
    ui->centerLabel2->show();
    ui->centerLabel2->setText("Credit Limit");
    ui->lineEdit1->show();
    ui->lineEdit1->setText("66000 €");
    ui->lineEdit2->show();
    ui->lineEdit2->setText("5000 €");
    window = 4;
}

void MainWindow::showEventMenu()
{
    hideElements();
    clearLabels();
    ui->titleLabel->setText("Account Events");
    ui->rightLabel1->setText("BACK");
    ui->tableView->show();
    window = 5;
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

    // Alkunäkymä
    if (window == 0) {
        if (currentSideButton == "leftButton1") {
            showLoginMenu();
        }
    }

    // Login-ruutu
    if (window == 1) {
        if (currentSideButton == "rightButton1") {
            reset();
        }
    }

    // Menu
    if (window == 2) {
        if (currentSideButton == "rightButton1") {
            reset();
            //jotain token-reset juttua tähän jos tarvii (log out)
        }
        if (currentSideButton == "leftButton3") {
            showWithdrawMenu();
        }
        if (currentSideButton == "leftButton2") {
            showBalanceMenu();
        }
        if (currentSideButton == "leftButton1") {
            showEventMenu();
        }
    }

    // Withdraw-menu
    if (window == 3) {
        if (currentSideButton == "leftButton5") {
            ui->lineEdit1->setText("20");
            withdrawAmount = ui->lineEdit1->text();
            wasOtherChosen = false;
        }
        if (currentSideButton == "leftButton4") {
            ui->lineEdit1->setText("40");
            withdrawAmount = ui->lineEdit1->text();
            wasOtherChosen = false;
        }
        if (currentSideButton == "leftButton3") {
            ui->lineEdit1->setText("50");
            withdrawAmount = ui->lineEdit1->text();
            wasOtherChosen = false;
        }
        if (currentSideButton == "leftButton2") {
            ui->lineEdit1->setText("100");
            withdrawAmount = ui->lineEdit1->text();
            wasOtherChosen = false;
        }
        if (currentSideButton == "leftButton1") {
            wasOtherChosen = true;
            ui->lineEdit1->clear();
            withdrawAmount.clear();
        }
    }

    // Global
    if (currentSideButton == "rightButton1" && ui->rightLabel1->text() == "BACK") {
        showMenu();
    }

    // Testi
    if (currentSideButton == "rightButton5") {
        qDebug() << "window:" << window << "LEText:" << ui->lineEdit1->text() << "withdrawAmount:" << withdrawAmount;
    }
}

void MainWindow::login()
{
    QJsonObject jsonObj;
    jsonObj.insert("card_serial", cardNumber);
    jsonObj.insert("card_pin", password);

    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(loginSlot(QNetworkReply*)));
    reply = loginManager->get(request);
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();
    qDebug() << responseData;
    QMessageBox msgBox;
    if (responseData == "-4078") {

        msgBox.setText("Error with connecting to database");
            msgBox.exec();
    } else {
        if (responseData != "false") {
            msgBox.setText("OK");
            msgBox.exec();
        } else {
            msgBox.setText("Card number / password do not match");
            msgBox.exec();
        }
    }
}

void MainWindow::fillLineEdit()
{
    if (window == 1) {
        switch (state) {
            case 1:
                if (currentNumPadKey == "CLR") {                //Kortin numero tulee lukijalta, pitää muuttaa
                    ui->lineEdit2->clear();
                    cardNumber.clear();
                } else if (currentNumPadKey == "OK") {
                    //checkCardNumber();
                    state = 2;
                } else {
                    cardNumber = cardNumber + currentNumPadKey;
                    ui->lineEdit2->setText(cardNumber);
                }
                break;
            case 2:
                if (currentNumPadKey == "CLR") {
                    ui->lineEdit3->clear();
                    password.clear();
                } else if (currentNumPadKey == "OK") {
                    //checkPassword();
                    login();
                    showMenu();
                } else {
                    password = password + currentNumPadKey;
                    ui->lineEdit3->setText(password);
                }

                break;
            }
    }
    if (window == 3 && wasOtherChosen == true) {
        if (currentNumPadKey == "CLR") {
            ui->lineEdit1->clear();
            withdrawAmount.clear();
        } else if (currentNumPadKey == "OK") {
            //uus ikkuna, jossa esim "Nostit 20 e" jne tai vaan toiminto, jolla "raha" lähtee
            // toinen vaihtoehto laittaa toiminnot suoraan withdraw-menun sivunappeihin
        } else {
            withdrawAmount = withdrawAmount + currentNumPadKey;
            ui->lineEdit1->setText(withdrawAmount);
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
    ui->lineEdit1->hide();
    ui->lineEdit2->hide();
    ui->lineEdit3->hide();
    ui->lineEdit1->clear();
    ui->lineEdit2->clear();
    ui->lineEdit3->clear();
    ui->centerLabel1->hide();
    ui->centerLabel2->hide();
    ui->centerLabel3->hide();
    ui->tableView->hide();
    cardNumber.clear();
    password.clear();
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
    ui->centerLabel1->clear();
    ui->centerLabel2->clear();
    ui->centerLabel3->clear();
}

void MainWindow::checkCardNumber()
{
    if (cardNumber == correctCardNumber) {
        state = 2;
        qDebug() << "Card OK";
        ui->titleLabel->setText("Insert PIN");
    } else {
        ui->lineEdit2->clear();
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
        ui->lineEdit3->clear();
        password.clear();
        pinAttemptsLeft--;
        if (pinAttemptsLeft == 0) {
            MainWindow::close();    //Temporary
        }
        qDebug() << "Wrong PIN";
        qDebug() << "Attempts left:" << pinAttemptsLeft;
    }
}
