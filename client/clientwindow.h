#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QLabel>

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
    QLabel* scenes[30*30];

    void closeEvent(QCloseEvent *event) override;

signals:
    void showClientRegWindow();
};

#endif // CLIENTWINDOW_H
