#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  <QPushButton>
#include <QDebug>
#include "datalevel.h"
#include "QLabel"
#include "QList"
#include "QRadioButton"
#include "QGroupBox"
#include "QLayout"
#include "QTime"
#include "QCheckBox"
#include "QtNetwork/QNetworkAccessManager"

ClickableLabel::ClickableLabel(const QString& text, QWidget* parent)
    : QLabel(parent)
{
    setText(text);
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    emit clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deletWidget(int i)
{
    QWidget * widget=ui->stackedWidget->widget(i);

    foreach (QObject * o,widget->children()) {
        if (! qobject_cast<QGridLayout*>(o)) o->deleteLater();//если не лаяут
    }

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dl =DataLevel::getInstance();
    //QMap<QString,QString>  lec,lec2;

    QMultiMap<int,QString> themes=dl->getLec();
    // qDebug()<<themes;
    ui->stackedWidget->setCurrentIndex(0);

    foreach (int id, themes.uniqueKeys()) {



        ClickableLabel* l=new ClickableLabel();
        ui->stackedWidget->widget(0)->layout()->addWidget(l);
        l->setText("<h1>"+themes.values(id).at(1)+"</h1>"+themes.values(id).at(0));
        //qDebug()<<themes;


        l->lectionId=id;
        // res2 id



        QObject::connect(l,SIGNAL(clicked()),this, SLOT(showListTopics()));
    }

}



void MainWindow::showListTopics()
{

    ClickableLabel* cl = qobject_cast<ClickableLabel*>(sender());
    dl =DataLevel::getInstance();
    ui->stackedWidget->setCurrentIndex(1);
    QWidget * widget=ui->stackedWidget->widget(1);

    deletWidget(1);
    QMultiMap<int,QString> top=dl->getListTop(cl->lectionId);

    //qDebug()<<top;
    foreach (int id,top.uniqueKeys()) {



        ClickableLabel* l=new ClickableLabel();
        widget->layout()->addWidget(l);
        l->setText("<h1>"+top.values(id).at(1)+"</h1>"/*+top.values(id).at(0)*/);
        qDebug()<<top;


        l->topicId=id;
        qDebug()<<id;
        // res2 id



        QObject::connect(l,SIGNAL(clicked()),this, SLOT(showTopics()));
    }
    //qDebug()<<cl->equal;
    //qDebug()<<Top;
}

void MainWindow::showTopics()
{

    ClickableLabel* l=qobject_cast<ClickableLabel*>(sender());

    dl =DataLevel::getInstance();
    QMultiMap<int,QString> top=dl->getTop(l->topicId);
    ui->stackedWidget->setCurrentIndex(2);
    QWidget * widget=ui->stackedWidget->widget(2);

    deletWidget(2);
    foreach (int id,top.uniqueKeys()) {





        //ClickableLabel* cl=new ClickableLabel();
        QLabel* cl=new QLabel();
        widget->layout()->addWidget(cl);
        cl->setText("<h1>"+top.values(id).at(1)+"</h1>"+top.values(id).at(0));
        QPushButton* goTest=new QPushButton();

        ui->stackedWidget->widget(2)->layout()->addWidget(goTest);
        goTest->setText("Закрепить материал");

        goTest->setProperty("test",QVariant(id));

        //l->testId=id;
        qDebug()<<l->testId;




        QObject::connect(goTest,SIGNAL(clicked()),this, SLOT(showTest()));

    }
}

void MainWindow::showTest()
{
    ui->stackedWidget->setCurrentIndex(3);


    QPushButton* l=qobject_cast<QPushButton*>(sender());
    dl =DataLevel::getInstance();
    tests =dl->getTest(l->property("test").toInt());
    currentIndex=0;
    showQuestion(tests.at(currentIndex));


}

void MainWindow::showResult()
{
    QWidget * widget=ui->stackedWidget->widget(3);

    deletWidget(3);
    QLabel* label=new QLabel();
    widget->layout()->addWidget(label);
    label->setText(otvet.join("\n"));
    otvet.clear();
    qDebug()<<otvet;
    QPushButton* go = new QPushButton("Дальше");
    ui->stackedWidget->widget(3)->layout()->addWidget(go);
    connect(go,SIGNAL(clicked()), this, SLOT(jSON()));
}

void MainWindow::showQuestion(Test *poTestu){



    QWidget * widget=ui->stackedWidget->widget(3);

    deletWidget(3);


    if (poTestu->type==1){
        QLabel* label=new QLabel();
        widget->layout()->addWidget(label);
        label->setText(poTestu->title+"\n"+poTestu->questions.at(0));
        QGroupBox* groupBox = new QGroupBox();
        QVBoxLayout* boxLayout = new QVBoxLayout;
        groupBox->setLayout(boxLayout);
        widget->layout()->addWidget(groupBox);
        for (int i = 1; i < poTestu->questions.size(); ++i) {
            QRadioButton* quest=new QRadioButton();
            quest->setText(poTestu->questions.at(i));
            groupBox->layout()->addWidget(quest);
            widget->layout()->addWidget(groupBox);

        }
        if(currentIndex<tests.count()-1){
            QPushButton* go = new QPushButton("Дальше");
            widget->layout()->addWidget(go);
            connect(go,SIGNAL(clicked()), this, SLOT(checkAndNext()));
        }else{
            QPushButton* go = new QPushButton("Закончить тест");
            widget->layout()->addWidget(go);
            connect(go,SIGNAL(clicked()), this, SLOT(lastQuestion()));
        }

    }
    if (poTestu->type==2){

        QLabel* label=new QLabel();
        widget->layout()->addWidget(label);
        label->setText(poTestu->title+"\n"+poTestu->questions.at(0));
        QGroupBox* groupBox = new QGroupBox();
        QVBoxLayout* boxLayout = new QVBoxLayout;
        groupBox->setLayout(boxLayout);
        widget->layout()->addWidget(groupBox);
        poTestu->questions.removeFirst();





        while(poTestu->questions.size()){
            srand(QTime::currentTime().msec());
            int i=rand()%poTestu->questions.size();
            //label->setText( label->text()+"\n"+poTestu->questions.at(i)+"\n");

           QCheckBox* quest=new QCheckBox();
            quest->setText(poTestu->questions.at(i));
            groupBox->layout()->addWidget(quest);
            widget->layout()->addWidget(groupBox);
            poTestu->questions.removeAt(i);

        }
        if(currentIndex<tests.count()-1){
            QPushButton* go = new QPushButton("Дальше");
            widget->layout()->addWidget(go);
            connect(go,SIGNAL(clicked()), this, SLOT(checkAndNext2()));
        }else{
            QPushButton* go = new QPushButton("Закончить тест");
            widget->layout()->addWidget(go);
            connect(go,SIGNAL(clicked()), this, SLOT(lastQuestion2()));
        }

    }

}

void MainWindow::jSON()
{
    actionSelect();
}

void MainWindow::actionSelect()
{
    deletWidget(4);
    ui->stackedWidget->setCurrentIndex(4);
    QWidget * widget=ui->stackedWidget->widget(4);
    QPushButton* lection=new QPushButton("Выбрать тему");
    widget->layout()->addWidget(lection);
    QPushButton* listTopics=new QPushButton("Вернуться к лекциям по выбранной теме");
    widget->layout()->addWidget(listTopics);


    connect(lection,SIGNAL(clicked()), this, SLOT(returnShowLection()));
    connect(listTopics,SIGNAL(clicked()), this, SLOT(returnShowListTopics()));
}

void MainWindow::returnShowLection()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::returnShowListTopics()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::checkAndNext()
{

    Test * poTestu = tests.at(currentIndex);
//    qDebug()<<tests.at(currentIndex);
    QWidget * widget=ui->stackedWidget->widget(3);
    QGroupBox* gb= widget->findChild<QGroupBox*>();
    foreach (QObject *proverka, gb->children()) {
        QRadioButton * pb = qobject_cast<QRadioButton*>(proverka);
        if(pb){

            if(pb->text()==poTestu->answer) { if (pb->isChecked()){

                    otvet.append("1");
                    //qDebug()<< otvet;
                } else
                    otvet.append("0");
            }
        }

    }
    currentIndex++;
    showQuestion(tests.at(currentIndex));

}

void MainWindow::lastQuestion()
{
    Test * poTestu = tests.at(currentIndex);
    //qDebug()<<tests.at(currentIndex);
    QWidget * widget=ui->stackedWidget->widget(3);
    QGroupBox* gb= widget->findChild<QGroupBox*>();
    foreach (QObject *proverka, gb->children()) {
        QRadioButton * pb = qobject_cast<QRadioButton*>(proverka);
        if(pb){
            if(pb->text()==poTestu->answer){ if (pb->isChecked()){
                otvet.append("1");
                //qDebug()<< otvet;
            } else
                otvet.append("0");
            }
        }
    }
    showResult();
}

void MainWindow::checkAndNext2()
{
    Test * poTestu = tests.at(currentIndex);
//    qDebug()<<tests.at(currentIndex);
    QString otvetUser;
    QWidget * widget=ui->stackedWidget->widget(3);
    QGroupBox* gb= widget->findChild<QGroupBox*>();
    foreach (QObject *proverka, gb->children()) {
        QCheckBox * pb = qobject_cast<QCheckBox*>(proverka);
        if(pb) if (pb->isChecked()) otvetUser+=pb->text().left(2);

    }
    QStringList listOtvetUser;
     listOtvetUser=otvetUser.split(')',QString::SkipEmptyParts);
     qSort(listOtvetUser);
     otvetUser=listOtvetUser.join(')');
     otvetUser+=')';
     qDebug()<<otvetUser;
     otvet.append( (otvetUser==poTestu->answer)?"1":"0");
     qDebug()<<otvet;
    currentIndex++;
    showQuestion(tests.at(currentIndex));
}

void MainWindow::lastQuestion2()
{
    Test * poTestu = tests.at(currentIndex);
//    qDebug()<<tests.at(currentIndex);
    QString otvetUser;
    QWidget * widget=ui->stackedWidget->widget(3);
    QGroupBox* gb= widget->findChild<QGroupBox*>();
    foreach (QObject *proverka, gb->children()) {
        QCheckBox * pb = qobject_cast<QCheckBox*>(proverka);
        if(pb) if (pb->isChecked()) otvetUser+=pb->text().left(2);

    }
    QStringList listOtvetUser;
     listOtvetUser=otvetUser.split(')',QString::SkipEmptyParts);
     qSort(listOtvetUser);
     otvetUser=listOtvetUser.join(')');
     otvetUser+=')';
     qDebug()<<otvetUser;
     otvet.append( (otvetUser==poTestu->answer)?"1":"0");
     qDebug()<<otvet;
    showResult();
}
