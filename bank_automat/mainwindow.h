#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QStandardItemModel>
#include "bank_automat_dll.h"
#include "networking.h"

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
    Bank_automat_dll *dllPtr;
    QTimer *timer;
    Networking *networking;

    QString password;
    QString cardNumber;
    QString currentNumPadKey;
    QString currentSideButton;
    QString withdrawAmount;
    QString balance;
    QJsonArray events;
    QStandardItemModel tableModel;
    short pinAttemptsLeft;
    int window;
    int seconds;
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
    void setTimer();
    void readCard();
    void handleReturnValueOnLogin();
    void handleReturnValueOnWithdraw();
    void handleEventReturn();
    void handleBalanceReturn();

private slots:
    void handleDLLSignal(QString);
    void numPadClickHandler();
    void sideButtonClickHandler();
    void timeout();

};
#endif // MAINWINDOW_H

