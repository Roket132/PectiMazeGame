#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

    void draw();

private:
    Ui::ServerWindow *ui;
    QLabel* scenes[30*30];

};

#endif // SERVERWINDOW_H
