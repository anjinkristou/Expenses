#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <functional>

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(const QString &location, QObject *parent = nullptr);

    void forEachSheet(const std::function<void(int, const QString &, int)> &func) const;
    int addSheet(const QString &name, int status);

private:
    QSqlDatabase m_database;

    void createDatabase();
};

#endif // DATAMANAGER_H
