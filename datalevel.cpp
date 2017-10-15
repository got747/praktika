#include "datalevel.h"
#include <QtSql>
#include <QVector>
DataLevel* DataLevel::m_DataLevel=0;

DataLevel *DataLevel::getInstance()
{
//    QSqlQuery nami_tem("INSERT INTO `stat` () VALUES (); ");

    if(m_DataLevel==0)m_DataLevel=new DataLevel();
    return m_DataLevel;
}

QMultiMap<int,QString> DataLevel::getLec( )
{
    QSqlQuery nami_tem("SELECT * FROM Lecture");
    QMultiMap<int,QString>  lec;
    while (nami_tem.next()) {


              lec.insert(nami_tem.value("id").toInt(), nami_tem.value("title").toString());
              lec.insert(nami_tem.value("id").toInt(), nami_tem.value("body").toString());

    }
//    lec.insert(1,"tema");
//    lec.insert(1,"temahgk");
//    lec.insert(2,"tema2");
//    lec.insert(2,"tema35153");
//    lec.insert(3,"tema3");
//    lec.insert(3,"tema3335");

     return lec;
}

QMultiMap<int, QString> DataLevel::getListTop(int id)
{
    QSqlQuery nami_tem("SELECT * FROM Topic WHERE lecture_id="+QString::number(id));
    qDebug()<<"SELECT * FROM Topic WHERE lecture_id="+QString::number(id);
    QMultiMap<int, QString> top;
    while (nami_tem.next()) {
              top.insert( nami_tem.value("id").toInt(),  nami_tem.value("title").toString());
              top.insert( nami_tem.value("id").toInt(),  nami_tem.value("body").toString());

     }
    //qDebug()<<top;
     return top;

}

QMultiMap<int, QString> DataLevel::getTop(int id)
{
    QSqlQuery nami_tem("SELECT * FROM Topic WHERE id="+QString::number(id));
    qDebug()<<"SELECT * FROM Topic WHERE lecture_id="+QString::number(id);
    QMultiMap<int, QString> top;
    while (nami_tem.next()) {
              top.insert( nami_tem.value("id").toInt(),  nami_tem.value("title").toString());
              top.insert( nami_tem.value("id").toInt(),  nami_tem.value("body").toString());

     }
    //qDebug()<<top;
     return top;
}

QList<Test *> DataLevel::getTest(int id)
{
    QSqlQuery nami_tem("SELECT * FROM Test WHERE topic_id="+QString::number(id));
    qDebug()<<"SELECT * FROM Test WHERE topic_id="+QString::number(id);
    //qDebug()<<nami_tem();
    QList<Test *> test;



    while (nami_tem.next()) {
              Test * t= new Test();
              t->id=nami_tem.value("id").toInt();
              t->type=nami_tem.value("type").toInt();
              t->title=nami_tem.value("title").toString();
              t->answer=nami_tem.value("answer").toString();

              QString p=nami_tem.value("bodyJson").toString();
              t->questions=p.split(':',QString::SkipEmptyParts);
              qDebug()<<t;
              test.append(t);


     }
    qDebug()<<test.length();
    return test;
}

QList<CompileTest *> DataLevel::getCompileTest()
{
    QSqlQuery nami_tem("SELECT * FROM CompileTask");
    QList<CompileTest *> test;
    //qDebug()<<nami_tem();
    while (nami_tem.next()) {
        CompileTest* t =new CompileTest();
        t->id=nami_tem.value("id").toInt();
        t->bodyTask=nami_tem.value("bodyTask").toString();
        t->title=nami_tem.value("title").toString();
        test.append(t);

    }
    return test;
}

DataLevel::DataLevel(QObject *parent) : QObject(parent)
{
    QFile dfile("assets:/p.db");
    if (dfile.exists())
    {
         dfile.copy("./p.db");
         QFile::setPermissions("./p.db",QFile::WriteOwner | QFile::ReadOwner);
    }
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("p.db");

    if (!sdb.open()) {
          qDebug() << sdb.lastError().text();
    }
}
