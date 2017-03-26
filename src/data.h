#include <QString>
#include <QSqlQuery>

#include "mainwindow.h"
class DataManager
{
public:
    explicit DataManager(const QString &path);
    ~DataManager();
    
    bool initData();
    bool initNameserverList(QListWidget *list);
    bool nameserverListDeleteRow(QString name);
    
    QString getDataFromField(QString data, QString field);
    bool    setDataFromField(QString data, QString field, QString text);
    
    bool    deleteTable(QString name);
    bool    createTable(QString name);
    
    bool    insertData(QString tab, int id, QString text);
    
private:
    bool addPersonal(const QString &name);
    
    QSqlDatabase db;
};

extern class DataManager *dataBase;
