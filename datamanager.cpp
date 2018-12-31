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

DataManager::~DataManager()
{
    if(m_database.isOpen()) m_database.close();
}

void DataManager::forEach(const QString &table, const std::function<void(int)> &func) const
{
    QSqlQuery query(m_database);
    query.exec(QString("SELECT id FROM %0").arg(table));
    while (query.next()) {
        func(query.value("id").toInt());
    }
}

void DataManager::forEachDenpendent(const QString &table, const QString &field, const QVariant &value, const std::function<void (int)> &func) const
{
    QSqlQuery query(m_database);
    query.prepare(QString("SELECT id FROM %0 WHERE %1 = :value").arg(table).arg(field));
    query.bindValue(":value", value);
    query.exec();
    while (query.next()) {
        func(query.value("id").toInt());
    }
}

int DataManager::add(const QString &table)
{
    QSqlQuery query(m_database);
    query.prepare(QString("INSERT INTO %0 DEFAULT VALUES").arg(table));
    query.exec();
    return query.lastInsertId().toInt();
}

void DataManager::remove(const QString &table, int id)
{
    QSqlQuery query(m_database);
    query.prepare(QString("DELETE FROM %0 WHERE id = :id ").arg(table));
    query.bindValue(":id", id);
    query.exec();
}

QVariantMap DataManager::fields(const QString &table, int id, const QStringList &fields)
{
    QSqlQuery query(m_database);
    query.prepare(QString("SELECT * FROM %0 WHERE id = :id ").arg(table));
    query.bindValue(":id", id);
    query.exec();
    query.next();
    QVariantMap result;
    foreach (const QString &prop, fields) {
        result[prop] = query.value(prop);
    }

    return result;
}

void DataManager::setField(const QString &table, int id, const QString &field, const QVariant &value)
{
    QSqlQuery query(m_database);
    query.prepare(QString("UPDATE %0 SET %1 = :%1 WHERE id = :id").arg(table).arg(field));
    query.bindValue(":id", id);
    query.bindValue(QString(":%0").arg(field), value);
    query.exec();
}

void DataManager::createDatabase()
{
    QSqlQuery query(m_database);

    query.exec("CREATE TABLE IF NOT EXISTS sheets (id INTEGER UNIQUE PRIMARY KEY, name VARCHAR(30), status INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS records (id INTEGER UNIQUE PRIMARY KEY, amount REAL, sheet INTEGER, FOREIGN KEY(sheet) REFERENCES sheets(id))");

}
