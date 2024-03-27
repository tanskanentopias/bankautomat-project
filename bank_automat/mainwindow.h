#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    short pinAttemptsLeft;
    short state;

    void cardNumberAndPin();
    void fillLineEdit();
    void reset();

private slots:
    void numPadClickHandler();
    void sideButtonClickHandler();

};
#endif // MAINWINDOW_H

