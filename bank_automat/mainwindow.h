#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    QString password;
    QString cardNumber;
    QString currentNumPadKey;
    QString currentSideButton;
    QString correctPassword = "1234";
    QString correctCardNumber = "4321";
    QString withdrawAmount;
    short pinAttemptsLeft;
    short state;
    int window;
    bool wasOtherChosen;

    void cardNumberAndPin();
    void showMenu();
    void showWithdrawMenu();
    void fillLineEdit();
    void reset();
    void hideElements();
    void clearLabels();
    void checkCardNumber();
    void checkPassword();

private slots:
    void numPadClickHandler();
    void sideButtonClickHandler();

};
#endif // MAINWINDOW_H

