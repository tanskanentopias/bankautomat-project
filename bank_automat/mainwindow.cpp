#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pinAttemptsLeft(3)
    , window(0)
    , accountID(1)
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
    connect(ui->rightButton4, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->rightButton5, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton1, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton2, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton3, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton4, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton5, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);

    ui->lineEdit3->setEchoMode(QLineEdit::Password);
    hideElements();

    dllPtr = new Bank_automat_dll(this);
    connect(dllPtr, SIGNAL(sendCardToUi(QString)), this, SLOT(handleDLLSignal(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLoginMenu()
{
    hideElements();
    clearLabels();
    ui->titleLabel->setText("Insert PIN");
    ui->rightLabel1->setText("RESET");
    ui->lineEdit3->show();
    ui->centerLabel3->show();
    ui->centerLabel3->setText("PIN");
    window = 1;
}

void MainWindow::showMenu()
{
    hideElements();
    clearLabels();
    ui->titleLabel->setText("Choose option");
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
            QTimer::singleShot(0, this, [this]() {
                showWithdrawMenu();
            });
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
            withdraw();
        }
        if (currentSideButton == "leftButton4") {
            ui->lineEdit1->setText("40");
            withdrawAmount = ui->lineEdit1->text();
            wasOtherChosen = false;
            withdraw();
        }
        if (currentSideButton == "leftButton3") {
            ui->lineEdit1->setText("50");
            withdrawAmount = ui->lineEdit1->text();
            wasOtherChosen = false;
            withdraw();
        }
        if (currentSideButton == "leftButton2") {
            ui->lineEdit1->setText("100");
            withdrawAmount = ui->lineEdit1->text();
            wasOtherChosen = false;
            withdraw();
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

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
    qDebug() << jsonObj;
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();
    qDebug() << responseData;
    webToken = responseData;

    if (responseData == "-4078" || responseData.length() == 0) {
        ui->infoLabel->setText("Database connection error");
        ui->lineEdit3->clear();
        password.clear();
    } else if (responseData != "false") {
        showMenu();
    } else {
        ui->infoLabel->setText("Invalid card number or password");
        ui->lineEdit3->clear();
        password.clear();
    }

    reply->deleteLater();
    loginManager->deleteLater();
}

void MainWindow::withdraw()
{
    QJsonObject withdrawObj;
    withdrawObj.insert("accountId", accountID);
    withdrawObj.insert("eventAmount", withdrawAmount);

    QString site_url = "http://localhost:3000/withdraw";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray myToken = "Bearer " + webToken;
    request.setRawHeader(QByteArray("Authorization"), (myToken));

    withdrawManager = new QNetworkAccessManager(this);
    connect(withdrawManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));

    reply = withdrawManager->post(request, QJsonDocument(withdrawObj).toJson());
    qDebug() << withdrawObj;
}

void MainWindow::withdrawSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();
    qDebug() << responseData;
    reply->deleteLater();
    withdrawManager->deleteLater();
}

void MainWindow::fillLineEdit()
{
    if (window == 1) {
        if (currentNumPadKey == "CLR") {
            ui->lineEdit3->clear();
            password.clear();
        } else if (currentNumPadKey == "OK") {
            //checkPassword();
            login();
            ui->infoLabel->clear();
        } else {
            password = password + currentNumPadKey;
            ui->lineEdit3->setText(password);
        }
    }

    if (window == 3 && wasOtherChosen == true) {
        if (currentNumPadKey == "CLR") {
            ui->lineEdit1->clear();
            withdrawAmount.clear();
        } else if (currentNumPadKey == "OK") {
            withdraw();
        } else {
            withdrawAmount = withdrawAmount + currentNumPadKey;
            ui->lineEdit1->setText(withdrawAmount);
        }
    }
}

void MainWindow::reset()
{
    hideElements();
    window = 0;
    pinAttemptsLeft = 3;
    currentNumPadKey.clear();
    currentSideButton.clear();
    clearLabels();
    ui->titleLabel->setText("Insert Card");
}

void MainWindow::hideElements()
{
    if (window == 0) {
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
        password.clear();
        withdrawAmount.clear();
    } else {
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
    ui->infoLabel->clear();
}

//void MainWindow::checkPassword()
//{
//    if (password == correctPassword) {
//        state = 0;
//        hideElements();
//        showMenu();
//    } else {
//        ui->lineEdit3->clear();
//        password.clear();
//        pinAttemptsLeft--;
//        if (pinAttemptsLeft == 0) {
//            MainWindow::close();    //Temporary
//        }
//        qDebug() << "Wrong PIN";
//        qDebug() << "Attempts left:" << pinAttemptsLeft;
//    }
//}

void MainWindow::handleDLLSignal(QString serial)
{
    cardNumber = serial;
    showLoginMenu();
}
