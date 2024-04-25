#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QStandardItemModel>
#include "bank_automat_dll.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QNetworkReply *reply;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *withdrawManager;
    QNetworkAccessManager *eventManager;
    Bank_automat_dll *dllPtr;

    QByteArray responseData;
    QByteArray webToken;
    QByteArray myToken;
    QString site_url;
    QString password;
    QString cardNumber;
    QString currentNumPadKey;
    QString currentSideButton;
    QString withdrawAmount;
    QString accountID;
    QStandardItemModel tableModel;
    short pinAttemptsLeft;
    int window;
    bool wasOtherChosen;

    void showLoginMenu();
    void showMenu();
    void showWithdrawMenu();
    void showBalanceMenu();
    void showEventMenu();
    void fillLineEdit();
    void reset();
    void hideElements();
    void clearLabels();
    void checkPassword();

private slots:
    void handleDLLSignal(QString);
    void numPadClickHandler();
    void sideButtonClickHandler();
    void login();
    void loginSlot(QNetworkReply *reply);
    void withdraw();
    void withdrawSlot(QNetworkReply *reply);
    void getEvents();
    void eventSlot(QNetworkReply *reply);

};
#endif // MAINWINDOW_H

