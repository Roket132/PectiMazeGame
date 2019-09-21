#include "avatarselection.h"
#include "ui_avatarselection.h"

#include <QPushButton>
#include <QCloseEvent>

#include "appsettings.h"

AvatarSelection::AvatarSelection(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::AvatarSelection)
{
   ui->setupUi(this);

   AppSettings &settings = AppSettings::getAppSettings();

   lastAvatar = settings.getAvatar();

   int row = 1, col = 1;
   for (size_t i = 0; i < settings.getAmoutnAvatarVariants(); i++) {
       QPushButton *btn = new QPushButton();
       btn->setFlat(true);
       btn->setFixedSize(80, 80);
       btn->setIcon(QPixmap(QStringLiteral(":/%1/src/avatars/%1/avatar_%2.jpg").arg(settings.getStyle()).arg(i)));
       btn->setIconSize(btn->size() - QSize(5, 5));

       connect(btn, &QPushButton::clicked, [btn, i]() {
           AppSettings &settings = AppSettings::getAppSettings();
           settings.setAvatar(i);
           btn->setDown(true);
       });

       ui->avatarsLayout->addWidget(btn, col, row);
       if ((i + 1) % 5 == 0) col++;
       row = (row % 5) + 1;
   }
}

AvatarSelection::~AvatarSelection() {
    delete ui;
}

void AvatarSelection::closeEvent(QCloseEvent *event) {
    emit showRegClientWindow();
    event->accept();
}

void AvatarSelection::on_pushButton_clicked() {
    AppSettings &settings = AppSettings::getAppSettings();
    settings.setAvatar(lastAvatar);
    this->close();
}

void AvatarSelection::on_pushButton_2_clicked() {
    this->close();
}
