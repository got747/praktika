#include "dialog.h"
#include "ui_dialog.h"
#include "linkandtest.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_pushButton_clicked()
{
    qDebug()<<1;
    this->done(2);
}

void Dialog::on_pushButton_2_clicked()
{
    qDebug()<<2;
    this->done(3);
}

void Dialog::on_pushButton_3_clicked()
{
    qDebug()<<3;
    this->done(0);
}


