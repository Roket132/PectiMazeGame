#include "avatarselection.h"
#include "ui_avatarselection.h"

avatarSelection::avatarSelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::avatarSelection)
{
    ui->setupUi(this);



}

avatarSelection::~avatarSelection()
{
    delete ui;
}
