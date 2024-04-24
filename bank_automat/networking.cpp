#include "networking.h"

Networking::Networking(QObject *parent)
    : QObject(parent)
{

}

void Networking::login(QString &cardNumber, QString &password)
{
    QJsonObject jsonObj;
    jsonObj.insert("card_serial", cardNumber);
    jsonObj.insert("card_pin", password);

    siteURL = "http://localhost:3000/login";
    QNetworkRequest request((siteURL));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void Networking::loginSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    webToken = jsonObj["token"].toString().toUtf8();
    int accountIDint = jsonObj["id_account"].toInt();

    accountID = QString::number(accountIDint);

    if (responseData == "-4078" || responseData.length() == 0) {
        returnValue = 2;
    } else if (responseData != "false") {
        returnValue = 0;
    } else {
        returnValue = 1;
    }

    reply->deleteLater();
    loginManager->deleteLater();

    emit loginComplete();
}

void Networking::withdraw(QString &accountID, QString &withdrawAmount)
{
    QJsonObject withdrawObj;
    withdrawObj.insert("accountId", accountID);
    withdrawObj.insert("eventAmount", withdrawAmount);

    if (accountID == "1") {
        siteURL = "http://localhost:3000/debit_withdraw";
    } else {
        siteURL = "http://localhost:3000/credit_withdraw";
    }

    QNetworkRequest request((siteURL));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    authenticate(request);

    withdrawManager = new QNetworkAccessManager(this);
    connect(withdrawManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));

    reply = withdrawManager->post(request, QJsonDocument(withdrawObj).toJson());
}

void Networking::withdrawSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();

    if (responseData == "-4078" || responseData.length() == 0) {
        returnValue = 2;
    } else if (responseData == "3819") {
        returnValue = 1;
    } else if (responseData == "Forbidden" || responseData == "Unauthorized") {
        returnValue = 3;
    } else {
        returnValue = 0;
    }

    reply->deleteLater();
    withdrawManager->deleteLater();

    emit withdrawComplete();
}

void Networking::getEvents(QString &accountID)
{
    siteURL = "http://localhost:3000/event/" + accountID;

    QNetworkRequest request((siteURL));

    authenticate(request);

    eventManager = new QNetworkAccessManager(this);
    connect(eventManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(eventSlot(QNetworkReply*)));

    reply = eventManager->get(request);
}

void Networking::eventSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();

    if (responseData == "Forbidden" || responseData == "Unauthorized") {
        returnValue = 3;
    } else {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        events = jsonDoc.array()[0].toArray();
    }

    reply->deleteLater();
    eventManager->deleteLater();

    emit eventsComplete();
}

void Networking::authenticate(QNetworkRequest &request)
{
    myToken = "Bearer " + webToken;
    request.setRawHeader(QByteArray("Authorization"), (myToken));
}

short Networking::getReturnValue()
{
    return returnValue;
}

QJsonArray Networking::getEventArray()
{
    return events;
}

QString Networking::getAccountID()
{
    return accountID;
}

