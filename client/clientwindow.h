#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QLabel>
#include <vector>

#include "client/clientsettings.h"
#include "engine/engine.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private:
    Ui::ClientWindow *ui;
    //QLabel* scenes[30*30];
    std::vector<QLabel*> scenes;

    void closeEvent(QCloseEvent *event) override;

    void draw();

signals:
    void showClientRegWindow();
};

#endif // CLIENTWINDOW_H
