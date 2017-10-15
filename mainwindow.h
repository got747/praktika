#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <linkandtest.h>
#include <QMainWindow>
#include <QLabel>
#include "datalevel.h"
#include <QMultiMap>
#include <QVector>

class ClickableLabel : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel( const QString& text="", QWidget* parent=0 );
    ~ClickableLabel();
    int lectionId;
    int testId;
    int topicId;
    int compTestId;
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event);
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //MainWindow *w;
    DataLevel * dl;    
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList <Test*> tests;
    QStringList otvet ;
    int currentIndex;
private:
    Ui::MainWindow *ui;
    void deletWidget(int i);
public slots:
    void checkAndNext();
    void lastQuestion();
    void checkAndNext2();
    void lastQuestion2();
private    slots:
    void showListTopics();
    void showTopics();
    void showTest();
    void showResult();
    void showQuestion(Test *poTestu);
    void jSON();
    void actionSelect();
    void returnShowLection();
    void returnShowListTopics();

};

#endif // MAINWINDOW_H
