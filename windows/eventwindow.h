#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
class EventWindow;
}

class EventWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EventWindow(QWidget *parent = nullptr);
    explicit EventWindow(QString name, QString task, QWidget *parent = nullptr);
    ~EventWindow() override;

    void closeEvent(QCloseEvent *event) override;

signals:
    void opened();
    void closed();

private:
    Ui::EventWindow *ui;
};

#endif // EVENTWINDOW_H
