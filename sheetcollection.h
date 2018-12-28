#ifndef SHEETCOLLECTION_H
#define SHEETCOLLECTION_H

#include <QObject>
#include <QVector>
#include <QPointer>

class Sheet;
class DataManager;

class SheetCollection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataManager* dataManager READ dataManager WRITE setDataManager NOTIFY dataManagerChanged)
public:
    explicit SheetCollection(DataManager *dataManager = nullptr, QObject *parent = nullptr);
    void addSheet(Sheet *sheet, bool persist = true);

    int sheetCount() const;
    Q_INVOKABLE Sheet *sheetAt(int index) const;

    Q_INVOKABLE Sheet *addSheet();

    DataManager* dataManager() const;

signals:
    void dataManagerChanged(DataManager* dataManager);
    void sheetChanged(int index);
    void beginInsert(int first, int last);
    void endInsert();

    void beginRemove(int first, int last);
    void endRemove();

    void beginReset();
    void endReset();


public slots:
    void removeAt(int index);
    void setDataManager(DataManager* dataManager);

private:
    QVector<Sheet *> m_sheets;
    QPointer<DataManager> m_dataManager;

    void loadSheets();
};

#endif // SHEETCOLLECTION_H
