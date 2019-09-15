#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow() override;

private:
    Ui::SettingsWindow *ui;

    void closeEvent(QCloseEvent *event) override;

signals:
    void showMainWindow();

private slots:
    void on_backBtn_clicked();
    void on_okButton_clicked();
};



#endif // SETTINGSWINDOW_H
