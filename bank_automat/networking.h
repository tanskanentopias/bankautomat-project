#ifndef NETWORKING_H
#define NETWORKING_H

#include <QMainWindow>
#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class Networking : public QObject
{
    Q_OBJECT
public:
    explicit Networking(QObject *parent = nullptr);

    void login(QString &cardNumber, QString &password);
    void withdraw(QString &accountID, QString &withdrawAmount);
    void getEvents(QString &accountID);
    short getReturnValue();
    QJsonArray getEventArray();

public slots:
    void loginSlot(QNetworkReply *reply);
    void withdrawSlot(QNetworkReply *reply);
    void eventSlot(QNetworkReply *reply);

signals:
    void loginComplete();
    void withdrawComplete();
    void eventsComplete();

private:
    QNetworkReply *reply;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *withdrawManager;
    QNetworkAccessManager *eventManager;

    QString siteURL;
    QByteArray responseData;
    QByteArray webToken;
    QByteArray myToken;
    short returnValue;
    QJsonArray events;

    void authenticate(QNetworkRequest &request);
};

#endif // NETWORKING_H
