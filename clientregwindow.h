#ifndef CLIENTREGWINDOW_H
#define CLIENTREGWINDOW_H

#include <QWidget>

namespace Ui {
class ClientRegWindow;
}

class ClientRegWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientRegWindow(QWidget *parent = nullptr);
    ~ClientRegWindow();

private:
    Ui::ClientRegWindow *ui;

    void closeEvent(QCloseEvent *event) override;

signals:
    void showMainWindow();
};

#endif // CLIENTREGWINDOW_H
