#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pinAttemptsLeft(3)
    , window(0)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    networking = new Networking(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::timeout);

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
    connect(ui->leftButton3, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton4, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);
    connect(ui->leftButton5, &QPushButton::clicked, this, &MainWindow::sideButtonClickHandler);

    connect (networking, &Networking::loginComplete, this, &MainWindow::handleReturnValueOnLogin);
    connect (networking, &Networking::withdrawComplete, this, &MainWindow::handleReturnValueOnWithdraw);
    connect (networking, &Networking::eventsComplete, this, &MainWindow::handleEventReturn);

    ui->lineEdit3->setEchoMode(QLineEdit::Password);
    hideElements();
    readCard();

    tableModel.setColumnCount(3);
    tableModel.setHorizontalHeaderLabels(QStringList() << "Type" << "Date" << "Amount");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete networking;
}

void MainWindow::handleDLLSignal(QString serial)
{
    if (window == 0) {
        cardNumber = serial;
        showLoginMenu();
    }
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
            networking->getEvents(accountID);
        }
    }

    // Withdraw-menu
    if (window == 3) {
        if (currentSideButton == "leftButton5") {
            ui->lineEdit2->setText("20");
            withdrawAmount = ui->lineEdit2->text();
            wasOtherChosen = false;
            networking->withdraw(accountID, withdrawAmount);
            ui->centerLabel2->hide();
            ui->lineEdit2->hide();
            setTimer();
        }
        if (currentSideButton == "leftButton4") {
            ui->lineEdit2->setText("40");
            withdrawAmount = ui->lineEdit2->text();
            wasOtherChosen = false;
            networking->withdraw(accountID, withdrawAmount);
            ui->centerLabel2->hide();
            ui->lineEdit2->hide();
            setTimer();
        }
        if (currentSideButton == "leftButton3") {
            ui->lineEdit2->setText("50");
            withdrawAmount = ui->lineEdit2->text();
            wasOtherChosen = false;
            networking->withdraw(accountID, withdrawAmount);
            ui->centerLabel2->hide();
            ui->lineEdit2->hide();
            setTimer();
        }
        if (currentSideButton == "leftButton2") {
            ui->lineEdit2->setText("100");
            withdrawAmount = ui->lineEdit2->text();
            wasOtherChosen = false;
            networking->withdraw(accountID, withdrawAmount);
            ui->centerLabel2->hide();
            ui->lineEdit2->hide();
            setTimer();
        }
        if (currentSideButton == "leftButton1") {
            wasOtherChosen = true;
            ui->centerLabel2->show();
            ui->centerLabel2->setText("Amount");
            ui->lineEdit2->show();
            ui->lineEdit2->clear();
            withdrawAmount.clear();
            ui->infoLabel->clear();
            setTimer();
        }
    }

    // Global
    if (currentSideButton == "rightButton1" && ui->rightLabel1->text() == "BACK") {
        showMenu();
    }
}

void MainWindow::handleReturnValueOnLogin()
{
    switch (networking->getReturnValue()) {
        case 0:
            showMenu();
            break;
        case 1:
            ui->infoLabel->setText("Invalid card number or password");
            ui->lineEdit3->clear();
            password.clear();
            pinAttemptsLeft--;
            if (pinAttemptsLeft == 0) {
                reset();
            }
            break;
        case 2:
            ui->infoLabel->setText("Database connection error");
            ui->lineEdit3->clear();
            password.clear();
            break;
    }

    accountID = networking->getAccountID();
}

void MainWindow::handleReturnValueOnWithdraw()
{
    switch (networking->getReturnValue()) {
        case 0:
            ui->infoLabel->setText("Withdrew " + withdrawAmount + " €");
            break;
        case 1:
            if (accountID == "1") {
                ui->infoLabel->setText("Insufficient funds");
            } else {
                ui->infoLabel->setText("Credit limit exceeded");
            }
            ui->lineEdit2->clear();
            withdrawAmount.clear();
            break;
        case 2:
            ui->infoLabel->setText("Database connection error");
            ui->lineEdit2->clear();
            withdrawAmount.clear();
            break;
        case 3:
            ui->infoLabel->setText("Authentication failed");
            break;
    }
}

void MainWindow::handleEventReturn()
{
    if (networking->getReturnValue() == 3) {
        ui->tableEvents->hide();
        ui->infoLabel->setText("Authentication failed");
    } else {
        events = networking->getEventArray();

        tableModel.removeRows(0, tableModel.rowCount());

        for (int i = 0; i < events.size(); ++i) {
            QJsonObject event = events[i].toObject();
            QString type = event["transaction_type"].toString();
            QString date = event["transaction_date"].toString();
            QString amount = event["amount"].toString();

            if (type == "credit_withdraw" || type == "debit_withdraw") {
                type = "Withdraw";
            }

            QDateTime rawDate = QDateTime::fromString(date, Qt::ISODate);
            rawDate = rawDate.toLocalTime();
            QString formattedDate = rawDate.toString("yyyy-MM-dd hh:mm:ss");

            QList<QStandardItem *> rowItems;
            rowItems << new QStandardItem(type) << new QStandardItem(formattedDate) << new QStandardItem(amount);
            tableModel.appendRow(rowItems);
        }
        ui->tableEvents->setModel(&tableModel);
        QHeaderView *header = ui->tableEvents->horizontalHeader();
        header->resizeSection(1, 170);
    }
}

void MainWindow::timeout()
{
    timer->start(1000);
    seconds--;
    //qDebug() << seconds;

    if (seconds == 0) {
        reset();
    }
}

void MainWindow::showLoginMenu()
{
    hideElements();
    clearLabels();
    window = 1;
    ui->titleLabel->setText("Insert PIN");
    ui->rightLabel1->setText("RESET");
    ui->lineEdit3->show();
    ui->centerLabel3->show();
    ui->centerLabel3->setText("PIN");
    setTimer();
}

void MainWindow::showMenu()
{
    hideElements();
    clearLabels();
    window = 2;
    ui->titleLabel->setText("Choose option");
    ui->leftLabel3->setText("WITHDRAW");
    ui->leftLabel2->setText("SHOW BALANCE");
    ui->leftLabel1->setText("SHOW EVENTS");
    ui->rightLabel1->setText("LOG OUT");
    setTimer();
}

void MainWindow::showWithdrawMenu()
{
    hideElements();
    clearLabels();
    window = 3;
    ui->titleLabel->setText("Select amount to withdraw");
    QTimer::singleShot(0, this, [this]() {
        ui->lineEdit2->clear();
        withdrawAmount.clear();
    });
    ui->leftLabel5->setText("20 €");
    ui->leftLabel4->setText("40 €");
    ui->leftLabel3->setText("50 €");
    ui->leftLabel2->setText("100 €");
    ui->leftLabel1->setText("OTHER");
    ui->rightLabel1->setText("BACK");
    setTimer();
}

void MainWindow::showBalanceMenu()
{
    hideElements();
    clearLabels();
    window = 4;
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
    setTimer();
}

void MainWindow::showEventMenu()
{
    hideElements();
    clearLabels();
    window = 5;
    ui->titleLabel->setText("Account Events");
    ui->rightLabel1->setText("BACK");
    ui->tableEvents->show();
    setTimer();
}

void MainWindow::fillLineEdit()
{
    if (window == 1) {
        if (currentNumPadKey == "CLR") {
            ui->lineEdit3->clear();
            password.clear();
            setTimer();
        } else if (currentNumPadKey == "OK") {
            networking->login(cardNumber, password);
            ui->infoLabel->clear();
            setTimer();
        } else {
            password = password + currentNumPadKey;
            ui->lineEdit3->setText(password);
            setTimer();
        }
    }

    if (window == 3 && wasOtherChosen == true) {
        if (currentNumPadKey == "CLR") {
            ui->lineEdit2->clear();
            withdrawAmount.clear();
            setTimer();
        } else if (currentNumPadKey == "OK") {
            networking->withdraw(accountID, withdrawAmount);
            setTimer();
        } else {
            withdrawAmount = withdrawAmount + currentNumPadKey;
            ui->lineEdit2->setText(withdrawAmount);
            setTimer();
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
    timer->stop();
    readCard();
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
        ui->tableEvents->hide();
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
        ui->tableEvents->hide();
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

void MainWindow::setTimer()
{
    timer->stop();
    seconds = 200;
    timeout();
}

void MainWindow::readCard()
{
    dllPtr = new Bank_automat_dll(this);
    connect(dllPtr, SIGNAL(sendCardToUi(QString)), this, SLOT(handleDLLSignal(QString)));
}
