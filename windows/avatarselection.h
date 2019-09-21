#ifndef AVATARSELECTION_H
#define AVATARSELECTION_H

#include <vector>
#include <QDialog>

namespace Ui {
class AvatarSelection;
}

class AvatarSelection : public QDialog
{
    Q_OBJECT

public:
    explicit AvatarSelection(QWidget *parent = nullptr);
    ~AvatarSelection() override;


private:
    Ui::AvatarSelection *ui;
    size_t lastAvatar;

    void closeEvent(QCloseEvent *event) override;

signals:
    void showRegClientWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // AVATARSELECTION_H
