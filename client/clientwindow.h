#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QPushButton>
#include <QGridLayout>
#include <functional>
#include <QLabel>
#include <QThread>
#include <vector>

#include "client/clientsettings.h"
#include "windows/eventwindow.h"
#include "engine/engine.h"
#include "client.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow() override;

private:
    Ui::ClientWindow *ui;
    //QLabel* scenes[30*30];
    std::vector<QLabel*> scenes;
    std::vector<QPushButton*> invScenes;
    std::vector<QLabel*> infoInvScenes;

    std::vector<QGridLayout*> eventLayouts;

    Engine* eng;
    QThread* thread;

    void closeEvent(QCloseEvent *event) override;

    void blockMoving();
    void unlockMoving();
    void addEventLayout(QPixmap px, std::shared_ptr<Task> task, QString descriprion, std::function<void()> f_btn);
    void updateEventSettings();

    void arrowUsed();

    void setActions();
    std::map<QString, std::function<void()>> actions;

    EventWindow *eventWindow;
signals:
    void showClientRegWindow();

private slots:
    void slotAttack(int);
    void slotAnswerSuccessful(QString, QString);
    void slotAnswerIncorrect();

    void on_upButton_clicked();
    void on_rightButton_clicked();
    void on_downButton_clicked();
    void on_leftButton_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // CLIENTWINDOW_H
