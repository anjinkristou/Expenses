#include "datamanager.h"

#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include <QDir>

DataManager::DataManager(const QString &location, QObject *parent)
    : QObject(parent)
    , m_database(QSqlDatabase::addDatabase("QSQLITE"))
{
    QDir(location).mkdir(location);
    QString dbLocation = location + "/sheets.db";
    m_database.setDatabaseName(dbLocation);
    qCritical() << "Db:" << dbLocation;
    if(m_database.open()){
        createDatabase();
    } else {
        qDebug() << "Database error";
    }
}

void DataManager::forEachSheet(const std::function<void (int, const QString &, int)> &func) const
{
    QSqlQuery query(m_database);
    query.exec("SELECT id, name, status FROM sheets");
    while (query.next()) {
        func(query.value("id").toInt()
             , query.value("name").toString()
             , query.value("status").toInt());
    }
}

int DataManager::addSheet(const QString &name, int status)
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO sheets (name, status) "
                  "VALUES (:name, :status)");
    query.bindValue(":name", name);
    query.bindValue(":status", status);
    query.exec();
    return query.lastInsertId().toInt();
}

void DataManager::createDatabase()
{
    QSqlQuery query(m_database);

    query.exec("CREATE TABLE IF NOT EXISTS sheets (id INTEGER UNIQUE PRIMARY KEY, name VARCHAR(30), status INTEGER)");
}
