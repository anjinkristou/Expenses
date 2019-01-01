#ifndef SHEET_H
#define SHEET_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QVector>

class Record;
class DataManager;

class Sheet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataManager* dataManager READ dataManager WRITE setDataManager NOTIFY dataManagerChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(int recordCount READ recordCount NOTIFY recordCountChanged)
    Q_PROPERTY(QDate submittedDate READ submittedDate WRITE setSubmittedDate NOTIFY submittedDateChanged)
    Q_PROPERTY(qreal totalAmount READ totalAmount NOTIFY totalAmountChanged)

public:
    explicit Sheet(QObject *parent = nullptr);

    inline QString name() const { return m_name; }
    inline int status() const { return m_status; }
    inline int recordCount() const { return m_records.count(); }
    inline QDate submittedDate() const { return m_submittedDate; }
    inline int id() const { return m_id; }

    qreal totalAmount() const;

    Q_INVOKABLE Record* recordAt(int index) const;

    DataManager* dataManager() const;
    Q_INVOKABLE Record *addRecord();

    static QString tableName() { return "sheets"; }

public slots:
    void setName(QString name);
    void setStatus(int status);
    void setSubmittedDate(const QDate &date);
    void addRecord(Record* record);
    void setId(int id);

    void setDataManager(DataManager* dataManager);

signals:
    void nameChanged(const QString &name);
    void statusChanged(int status);
    void recordCountChanged(int count);
    void submittedDateChanged(const QDate &date);
    void totalAmountChanged(qreal total);
    void changed();    
    void idChanged(int id);
    void recordChanged(int index);
    void beginInsert(int first, int last);
    void endInsert();

    void beginRemove(int first, int last);
    void endRemove();

    void beginReset();
    void endReset();

    void dataManagerChanged(DataManager* dataManager);

private:
    int m_id;
    QString m_name;
    int m_status;
    QDate m_submittedDate;
    QVector<Record *> m_records;
    DataManager* m_dataManager;

    void updateFields();
    void loadRecords();
};

#endif // SHEET_H
