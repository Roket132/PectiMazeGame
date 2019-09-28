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
    explicit EventWindow(QWidget *parent = nullptr, QString name = "", size_t lvl = 1, QString mode = "enemy");
    explicit EventWindow(QString name, QString task, size_t lvl, QString mode, QWidget *parent = nullptr);
    ~EventWindow() override;

    void closeEvent(QCloseEvent *event) override;

signals:
    void opened();
    void closed();

private:
    Ui::EventWindow *ui;

    QString taskName;

    size_t taskLvl;

    QString taskMode;
};

#endif // EVENTWINDOW_H
