#include "mainwindow.h"
#include <QApplication>
#include "dialog.h"
#include "QDebug"
#include "linkandtest.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog  dialog;
     MainWindow w;
     LinkANDTest link;



     switch (dialog.exec()) {
     case 3:
         w.show();
         break;
     case 2:
         link.show();
         break;
     default:
         qDebug()<<"sss";
         break;
     }

    qDebug()<<&dialog;
    link.getDialog(dialog);


    return a.exec();
}


