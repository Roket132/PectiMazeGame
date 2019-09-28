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
    explicit EventWindow(QWidget *parent = nullptr, QString name = "", size_t lvl = 1);
    explicit EventWindow(QString name, QString task, size_t lvl, QWidget *parent = nullptr);
    ~EventWindow() override;

    void closeEvent(QCloseEvent *event) override;

signals:
    void opened();
    void closed();

private:
    Ui::EventWindow *ui;

    QString taskName;

    size_t taskLvl;
};

#endif // EVENTWINDOW_H
