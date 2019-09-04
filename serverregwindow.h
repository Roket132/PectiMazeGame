#ifndef SERVERREGWINDOW_H
#define SERVERREGWINDOW_H

#include "server/serverwindow.h"

#include <QWidget>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace Ui {
class ServerRegWindow;
}

class ServerRegWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerRegWindow(QWidget *parent = nullptr);
    ~ServerRegWindow();

private:
    Ui::ServerRegWindow *ui;
    ServerWindow* serverWindow;

    void closeEvent(QCloseEvent *event) override;

signals:
    void showMainWindow();

private slots:
    void on_choiseMazeButton_clicked();  //choice path for maze settings
    void on_startServerButton_clicked(); // start server with selected settings
};

#endif // SERVERREGWINDOW_H
