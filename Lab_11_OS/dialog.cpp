#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}
QString Dialog::getUser(){
    return user;
}
void Dialog::setUser(QString str){
    user=str;
}
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    setUser(ui->lineEdit->text());
    close();
}

