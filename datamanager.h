#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <functional>
#include <QVariant>
#include <QVariantMap>
#include <QString>

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(const QString &location, QObject *parent = nullptr);
    virtual ~DataManager();

    void forEach(const QString &table, const std::function<void(int)> &func) const;
    void forEachDenpendent(const QString &table, const QString &field, const QVariant &value, const std::function<void(int)> &func) const;
    int add(const QString &table);
    void remove(const QString &table, int id);
    QVariantMap fields(const QString &table, int id, const QStringList &fields);
    void setField(const QString &table, int id, const QString &field, const QVariant &value);

private:
    QSqlDatabase m_database;

    void createDatabase();
};

#endif // DATAMANAGER_H
