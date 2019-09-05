#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QCloseEvent>

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

    void closeEvent(QCloseEvent *event) override;

signals:
    void showClientRegWindow();
};

#endif // CLIENTWINDOW_H
