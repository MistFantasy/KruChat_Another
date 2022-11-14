#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
Dialog::Dialog(QString * user, int * SyncMethod,
               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->SyncMethod = SyncMethod;
    *this->SyncMethod = 0;
    this->user = user;
}

//QString Dialog::getUser()
//{
//    return user;
//}

//void Dialog::setUser(QString str)
//{
//    user = str;
//}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    *user = ui->lineEdit->text();

    close();
}


void Dialog::on_comboBox_activated(int index)
{
    *SyncMethod = index;
}

