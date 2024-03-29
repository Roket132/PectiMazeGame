 #include "eventwindow.h"
#include "ui_eventwindow.h"

#include <QMessageBox>
#include <QPushButton>
#include <QInputDialog>

#include "client/clientsettings.h"

EventWindow::EventWindow(QWidget *parent, QString name, size_t lvl, QString mode) :
    QWidget(parent),
    ui(new Ui::EventWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    emit opened();

    taskName = name;
    taskLvl = lvl;
    taskMode = mode;

    QPushButton *ansBtn = new QPushButton(this);
    ansBtn->setText("Ответить");
    ansBtn->setFixedSize(80, 30);

    ui->actionsLayout->addWidget(ansBtn);

    connect(ansBtn, &QPushButton::pressed, [this] {
        bool bOk;
        QString str = QInputDialog::getText( nullptr,
                                             "Ответ",
                                             "Введите ответ:",
                                             QLineEdit::Normal,
                                             "",
                                             &bOk
                                            );
        if (bOk) {
            ClientSettings &clientSetting = ClientSettings::getClientSettings();
            clientSetting.getClient()->sendToServer(QString("Answer %1 %2 %3$%4").arg(taskMode).arg(taskLvl).arg(taskName).arg(str));
        }

    });
}

namespace  {
QString createHTML(QString name, QString task) {
    QString res = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                          "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                           "p, li { white-space: pre-wrap; }"
                           "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
                           "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">%1</span></p>"
                           "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:16pt;\"><br /></p>").arg(name);

    QString newLine = "";
    for (auto it : task) {
        if (it == '\n') {
            newLine += ' ';
            res += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">%1</span></p>").arg(newLine);
            newLine = "";
        } else {
            newLine += it;
        }
    }
    res += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">%1</span></p>").arg(newLine);
    return res;
}
}

EventWindow::EventWindow(QString name, QString task, size_t lvl, QString mode, QWidget *parent) : EventWindow(parent, name, lvl, mode) {
    ui->textEdit->setHtml(createHTML(name, task));
}

EventWindow::~EventWindow()
{
    delete ui;
}

void EventWindow::closeEvent(QCloseEvent *event) {
/*
    int n = QMessageBox::warning(nullptr,
                                 "Выйти",
                                 "Вы действительно хотите закрыть окно события?",
                                 "ОК",
                                 "Отмена",
                                 QString(),
                                 0,
                                 1
                                );
    if (n) {
        event->ignore();
        return;
    }
*/
    emit closed();
    event->accept();
}
