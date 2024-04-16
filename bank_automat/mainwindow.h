#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMessageBox>

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
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray responseData;
    QString password;
    QString cardNumber;
    QByteArray webToken;
    QString currentNumPadKey;
    QString currentSideButton;
    QString correctPassword = "1234";
    QString correctCardNumber = "4321";
    QString withdrawAmount;
    short pinAttemptsLeft;
    short state;
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
    void checkCardNumber();
    void checkPassword();

private slots:
    void numPadClickHandler();
    void sideButtonClickHandler();
    void login();
    void loginSlot(QNetworkReply *reply);

};
#endif // MAINWINDOW_H

