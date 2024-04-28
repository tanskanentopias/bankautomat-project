#ifndef NETWORKING_H
#define NETWORKING_H

#include <QMainWindow>
#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QString>

class Networking : public QObject
{
    Q_OBJECT

public:
    explicit Networking(QObject *parent = nullptr);

    QByteArray webToken;
    QString cardType;
    QString accountID;

    void login(QString &cardNumber, QString &password);
    void withdraw(QString &withdrawAmount);
    void getEvents();
    void getBalance();
    short getReturnValue();
    QJsonArray getEventArray();
    QString returnBalance();
    QString returnCardType();

public slots:
    void loginSlot(QNetworkReply *reply);
    void withdrawSlot(QNetworkReply *reply);
    void eventSlot(QNetworkReply *reply);
    void balanceSlot(QNetworkReply *reply);

signals:
    void loginComplete();
    void withdrawComplete();
    void eventsComplete();
    void balanceComplete();

private:
    QNetworkReply *reply;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *withdrawManager;
    QNetworkAccessManager *eventManager;
    QNetworkAccessManager *balanceManager;

    QString siteURL;
    QByteArray responseData;
    QByteArray myToken;
    short returnValue;
    QJsonArray events;
    QJsonArray loginArray;
    QString balance;

    void authenticate(QNetworkRequest &request);
};

#endif // NETWORKING_H
