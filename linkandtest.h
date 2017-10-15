#ifndef LINKANDTEST_H
#define LINKANDTEST_H

#include <QMainWindow>
#include <QLineEdit>
#include <QNetworkReply>
#include <datalevel.h>
#include <QTextEdit>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QList>
#include <QRadioButton>
#include <QGroupBox>
#include <QLayout>
#include <QTime>
#include <QCheckBox>
#include <QLineEdit>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkConfigurationManager>
#include <QNetworkConfiguration>
#include <dialog.h>

namespace Ui {
class LinkANDTest;
}

class LinkANDTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit LinkANDTest(QWidget *parent = 0);
    ~LinkANDTest();
    QList<CompileTest *> compTest;

    void getDialog(Dialog &g);

private:
    Ui::LinkANDTest *ui;

    Dialog *di;


    QTextEdit * codUser;
    QLineEdit * login;
    QLineEdit * password;
private slots:
    void start();
    void repeatStart();
    void backDialog();
    void replyFinished(QNetworkReply*r);
    void postCreatRecord();
    void postCheckRecord();
    void postTestCheck();
    void showListCompliteTest();
    void showCompliteTest();

};

#endif // LINKANDTEST_H
