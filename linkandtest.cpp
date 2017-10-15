#include <linkandtest.h>
#include <ui_linkandtest.h>
#include <mainwindow.h>


LinkANDTest::LinkANDTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LinkANDTest)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);


    QNetworkConfigurationManager mgr;
    QList<QNetworkConfiguration> activeConfigs = mgr.allConfigurations(QNetworkConfiguration::Active);
    if (activeConfigs.count()){
        QLabel *disconnect=new QLabel();
        disconnect->setText("ERR_INTERNET_DISCONNECTED \n\n Извините ,но для прохождение тестов нужно \n обязательное подключение к интернету \n\n Проверьте свое подключение к интернету");
        ui->stackedWidget->widget(0)->layout()->addWidget(disconnect);

        QPushButton * repeat =new QPushButton();
        repeat->setText("Повторить");
        ui->stackedWidget->widget(0)->layout()->addWidget(repeat);

        QPushButton * back =new QPushButton();
        back->setText("Стартовый экран");
        ui->stackedWidget->widget(0)->layout()->addWidget(back);



        QObject::connect(back,SIGNAL(clicked()),this, SLOT(backDialog()));

    }
    else{


    }


}

void LinkANDTest::backDialog()
{
    MainWindow w;
    w.show();

    this->close();


//     LinkANDTest link;

//     switch ((*di).exec()) {
//     case 3:
//         w.show();
//         break;
//     case 2:
//         link.show();
//         break;
//     default:
//         break;
//     }

}

LinkANDTest::~LinkANDTest()
{
    delete ui;
}

void LinkANDTest::getDialog(Dialog &g)
{
    qDebug()<<&g;
    di=&g;
//    qDebug()<<&di;
}

void LinkANDTest::start()
{

    login=new QLineEdit();
    login->setPlaceholderText("пишем логин");
    ui->stackedWidget->widget(0)->layout()->addWidget(login);


    password=new QLineEdit();
    password->setPlaceholderText("пароль");
    password->setEchoMode(QLineEdit::Password);
    ui->stackedWidget->widget(0)->layout()->addWidget(password);



    QPushButton * notRecord=new QPushButton();
    notRecord->setText("Запись ");
    ui->stackedWidget->widget(0)->layout()->addWidget(notRecord);

    QPushButton * yesRecord=new QPushButton();
    yesRecord->setText("Войти");
    ui->stackedWidget->widget(0)->layout()->addWidget(yesRecord);


    QObject::connect(notRecord,SIGNAL(clicked()),this, SLOT(postCreatRecord()));
    QObject::connect(yesRecord,SIGNAL(clicked()),this, SLOT(postCheckRecord()));

}

void LinkANDTest::repeatStart()
{

}



void LinkANDTest::replyFinished(QNetworkReply *r)
{
    QString answerWeb = QString::fromUtf8(r->readAll());


    qDebug()<< answerWeb;
    switch (answerWeb.left(1).toInt()) {
    case 1:
        showListCompliteTest();
        break;
    case 2:
    {
        QLabel * oshibka=new QLabel();
        oshibka->setText("<b>Логин занят</b>");
        ui->stackedWidget->widget(0)->layout()->addWidget(oshibka);
    }
        break;
    case 3:
    {
        QLabel * oshibka=new QLabel();
        oshibka->setText("<b>Логин или пароль введен не верно</b>");
        ui->stackedWidget->widget(0)->layout()->addWidget(oshibka);
    }
        break;
    default:
        qDebug()<<"sksk";
        break;
    }



}



void LinkANDTest::postCreatRecord()
{

    QNetworkRequest request(QUrl("XXXXXXXXXXXXXX"));
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader,"application/x-www-form-urlencoded");
    QJsonDocument jd;



    QVariantMap config;
    config.insert("password",password->text());
    config.insert("login",login->text());
    config.insert("typet","record");

    jd.setObject(QJsonObject::fromVariantMap(config));
    qDebug()<<jd.toJson();



    QNetworkAccessManager * nam= new QNetworkAccessManager(this);

    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    nam->post(request,"data="+jd.toJson());
}

void LinkANDTest::postCheckRecord()
{
    //showListCompliteTest();
    QNetworkRequest request(QUrl("http://35.161.16.255/api.php"));
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader,"application/x-www-form-urlencoded");
    QJsonDocument jd;



    QVariantMap config;
    config.insert("password",password->text());
    config.insert("login",login->text());
    config.insert("typet","check");

    jd.setObject(QJsonObject::fromVariantMap(config));
    qDebug()<<jd.toJson();



    QNetworkAccessManager * nam= new QNetworkAccessManager(this);

    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    nam->post(request,"data="+jd.toJson());
}

void LinkANDTest::postTestCheck()
{

}

void LinkANDTest::showListCompliteTest()
{
    ui->stackedWidget->setCurrentIndex(1);

    MainWindow * j= new MainWindow();
    j->dl=DataLevel::getInstance();
    compTest = j->dl->getCompileTest();
    qDebug()<< compTest;
    for (int i = 0; i < compTest.size(); ++i) {

        ClickableLabel *nameTest= new ClickableLabel();
        nameTest->setText(compTest.at(i)->title);
        nameTest->compTestId=i;
        ui->stackedWidget->widget(1)->layout()->addWidget(nameTest);

        QObject::connect(nameTest,SIGNAL(clicked()),this, SLOT(showCompliteTest()));
    }
}

void LinkANDTest::showCompliteTest()
{
    ClickableLabel * thesTest=qobject_cast<ClickableLabel *>(sender());
    ui->stackedWidget->setCurrentIndex(2);

    QLabel * textTest = new QLabel();
    textTest->setText("<b><p>"+compTest.at(thesTest->compTestId)->title+"</b></p>"+compTest.at(thesTest->compTestId)->bodyTask);
    ui->stackedWidget->widget(2)->layout()->addWidget(textTest);

    codUser = new QTextEdit;
    ui->stackedWidget->widget(2)->layout()->addWidget(codUser);

    QPushButton * go = new QPushButton();
    go->setText("Отправить");
    ui->stackedWidget->widget(2)->layout()->addWidget(go);

    QObject::connect(go,SIGNAL(clicked()),this, SLOT(postTestCheck()));
}






