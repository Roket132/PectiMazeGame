#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <serverregwindow.h>
#include <clientregwindow.h>
#include <settingswindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startServerButton_clicked();

    void on_startGameButton_clicked();

    void on_settingsButton_clicked();

private:
    Ui::MainWindow *ui;

    ClientRegWindow *clientRegWindow;
    ServerRegWindow *serverRegWindow;
    SettingsWindow *settingsWindow;
};

#endif // MAINWINDOW_H
