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
    ~ServerRegWindow() override;

private:
    Ui::ServerRegWindow *ui;
    ServerWindow* serverWindow;

    void closeEvent(QCloseEvent *event) override;

    std::set<QString>* enemyPaths;
    std::set<QString>* arrowPaths;

signals:
    void showMainWindow();

private slots:
    void on_choiseMazeButton_clicked();  //choice path for maze settings
    void on_startServerButton_clicked(); // start server with selected settings
    void on_backButton_clicked();
    void on_addFileButton_clicked();
    void on_deleteFileButton_clicked();
    void on_addFileButton_2_clicked();
    void on_deleteFileButton_2_clicked();
};

#endif // SERVERREGWINDOW_H
