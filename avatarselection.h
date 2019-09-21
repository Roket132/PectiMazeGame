#ifndef AVATARSELECTION_H
#define AVATARSELECTION_H

#include <QDialog>

namespace Ui {
class avatarSelection;
}

class avatarSelection : public QDialog
{
    Q_OBJECT

public:
    explicit avatarSelection(QWidget *parent = nullptr);
    ~avatarSelection();

private:
    Ui::avatarSelection *ui;
};

#endif // AVATARSELECTION_H
