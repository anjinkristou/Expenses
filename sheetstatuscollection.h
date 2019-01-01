#ifndef SHEETSTATUSCOLLECTION_H
#define SHEETSTATUSCOLLECTION_H

#include <QObject>
#include <QVector>

class DataManager;
class SheetStatus;

class SheetStatusCollection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataManager* dataManager READ dataManager WRITE setDataManager NOTIFY dataManagerChanged)
public:
    explicit SheetStatusCollection(DataManager *dataManager = nullptr, QObject *parent = nullptr);

    DataManager* dataManager() const;

    int sheetStatusCount() const;

    SheetStatus *sheetStatusAt(int index) const;

signals:
    void dataManagerChanged(DataManager* dataManager);
    void beginInsert(int first, int last);
    void endInsert();

    void beginRemove(int first, int last);
    void endRemove();

    void beginReset();
    void endReset();

    void sheetStatusChanged(int index);

public slots:
    void setDataManager(DataManager* dataManager);
    void addSheetStatus(SheetStatus *status);

private:
    DataManager* m_dataManager;
    QVector<SheetStatus *> m_statuses;

    void loadStatus();
};

#endif // SHEETSTATUSCOLLECTION_H
