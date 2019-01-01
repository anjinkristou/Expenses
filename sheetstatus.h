#ifndef SHEETSTATUS_H
#define SHEETSTATUS_H

#include <QObject>

class DataManager;

class SheetStatus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataManager* dataManager READ dataManager WRITE setDataManager NOTIFY dataManagerChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit SheetStatus(QObject *parent = nullptr);

    DataManager* dataManager() const;

    static QString tableName() { return "statuses"; }

    inline int id() const { return m_id; }

    inline QString name() const { return m_name; }

signals:
    void dataManagerChanged(DataManager* dataManager);

    void idChanged(int id);
    void changed();

    void nameChanged(QString name);

public slots:
    void setDataManager(DataManager* dataManager);

    void setId(int id);

    void setName(QString name);

private:
    DataManager* m_dataManager;
    int m_id;
    QString m_name;
};

#endif // SHEETSTATUS_H
