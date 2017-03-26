#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVariant>
#include <QFile>
#include <QSqlError>

#include "data.h"
#include "mainwindow.h"

class DataManager *dataBase = nullptr;

DataManager::DataManager(const QString &path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    
    if (!db.open()) {
        QMessageBox::critical(0,"Open Connection Error","database connection fail.");
    }
}

DataManager::~DataManager()
{
    db.close();
}

bool DataManager::deleteTable(QString name)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("DROP TABLE " + name + ";");
    if (query.exec())
    success = true;
    return success;
}

bool DataManager::createTable(QString name)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("CREATE TABLE " + name + " (id integer, name text);");
    if (query.exec())
    success = true;
    return success;
}

bool DataManager::insertData(QString tab, int id, QString text)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO " + tab + " (id, name) VALUES (:id, :name);");
    query.bindValue(QString(":id"), id);
    query.bindValue(QString(":name"), text);
    if (query.exec())
    success = true;
    return success;
}

bool DataManager::initData()
{
    bool success = false;
    QSqlQuery query;
    query.prepare(
        "CREATE TABLE personal (id integer primary key, name text, pass text);"
    );
    if (query.exec()) {
        query.prepare("CREATE TABLE server (id integer, host text, port text, proxy text);");
        if (query.exec())   {
            query.prepare("INSERT INTO server (id) VALUES(1);");
            query.exec();
            success = true; } else {
            success = false;
        }
    }   else {
        QFile f("./data/data.db");
        if (!f.exists()) {
            QMessageBox::warning(0,"Warning","data could not be init.");
            success = false;
        }   else success = true;
    }   return   success;
}

bool DataManager::addPersonal(const QString &name)
{
    bool success = false;
    QVariant _name(name);
    
    QSqlQuery query;
    query.prepare("INSERT INTO personal (name) VALUES (:name);");
    query.bindValue(QString(":name"), _name);
    
    if (query.exec()) {
        success = true;
    }   else {
        QMessageBox::information(0,"Info","its okay");
        success = false;
    }
    
    return success;
}

QString DataManager::getDataFromField(QString data, QString field)
{    
    QSqlQuery query;
    QString query_str =
        QString("SELECT ") + QString(field) +
        QString(" FROM ")  + QString(data ) +
        QString(";");
    query.prepare(query_str);
        
    if (query.exec()) {
        query.first();
        QString dat = query.value(0).toString();
        return  dat;
    }   return  QString("");
}

bool DataManager::setDataFromField(
    QString data,
    QString field,
    QString text)
{
    bool success = false;
    QSqlQuery query;
    QString query_str;
    
    if (data == "server") {
        query_str =
        QString("UPDATE server ") +
        QString("SET id=1, " + field + "='" + text + "' WHERE id=1;");  
        query.prepare(query_str);
    }
    if (query.exec()) {
        success = true;
        //query.prepare("COMMIT;");
        //if (!query.exec())
        //    success = false; else
        //    success = true;
    }   else {
        QMessageBox::warning(app_window,"Warning","Data could not be written.");
    }   return success;
}

bool DataManager::initNameserverList(QListWidget *list)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM nameserver;");
    if (query.exec()) {
        success = true;
        query.first();
        
        int num;
        QString str;
        
        while (query.next()) {
            num = query.value(0).toInt();
            str = query.value(1).toString();
            
            list->addItem(str);
        }
    }
    return success;
}

bool DataManager::nameserverListDeleteRow(QString name)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("SELECT name FROM nameserver WHERE name='" + name + "';");
    if (query.exec()) {
        query.prepare("DELETE FROM nameserver WHERE name='" + name + "';");
        query.exec();
        success = true;
    }   return success;
}
