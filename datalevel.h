#ifndef DATALEVEL_H
#define DATALEVEL_H
#include <QStringList>
#include <QObject>
#include <QMap>
#include <QMultiMap>
class Test {
public:
    QString title;
    QString answer;
    QStringList questions ;
    //QStringList otvet ;
    int type;
    int id;
};

class CompileTest{
public:
    int id;
    QString title, bodyTask;
};


class DataLevel : public QObject
{
    Q_OBJECT
public:
   static DataLevel * getInstance();
   QMultiMap<int,QString> getLec();
   QMultiMap<int, QString> getListTop(int id);
   QMultiMap<int, QString> getTop(int id);
   QList<Test * > getTest(int id);
   QList<CompileTest * > getCompileTest();

  // * Test parsingJson();



private:
     explicit DataLevel(QObject *parent = 0);

        static DataLevel* m_DataLevel;

signals:

public slots:
};

#endif // DATALEVEL_H
