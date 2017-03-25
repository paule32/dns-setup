#include "data.h"

DataManager::DataManager(const QString &path)
{
    db = QSqlDatabase::addDatabase(QSQLITE);
    db.setDatabaseName(path);
    
    if (!db.open()) {
        QḾessageBox::warning(0,"Open Connection Error","database connection fail.");
    }   else
    QMessageBox::information(0,"112112212","sssssssssssssssssssssssssssss");
}

bool DataManager::addPersonal(const QString &name)
{
    bool success = false;
    
    QSqlQuery query;
    query.prepare("INSERT INTO personal (name) VALUES (:name)");
    query.bindValue(":name", name);
    
    if (query.exec()) {
        success = true;
    }   else {
        QMessageBox::information(0,"Info","its okay");
    }
}
