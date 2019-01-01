#ifndef RECORD_H
#define RECORD_H

#include <QObject>
#include <QDate>

class DataManager;

class Record : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataManager* dataManager READ dataManager WRITE setDataManager NOTIFY dataManagerChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int purpose READ purpose WRITE setPurpose NOTIFY purposeChanged)
    Q_PROPERTY(qreal amount READ amount WRITE setAmount NOTIFY amountChanged)
    Q_PROPERTY(QDate transactionDate READ transactionDate WRITE setTransactionDate NOTIFY transactionDateChanged)
    Q_PROPERTY(QString serviceProvider READ serviceProvider WRITE setServiceProvider NOTIFY serviceProviderChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    explicit Record(QObject *parent = nullptr);

    inline int id() const { return m_id; }
    inline qreal amount() const { return m_amount; }
    inline int purpose() const { return m_purpose; }
    inline QDate transactionDate() const  { return m_transactionDate; }
    inline QString serviceProvider() const  { return m_serviceProvider; }
    inline QString description() const { return m_description; }

    DataManager* dataManager() const;

    static QString tableName() { return "records"; }


public slots:
    void setId(int id);
    void setAmount(qreal amount);
    void setPurpose(int purpose);
    void setTransactionDate(const QDate &transactionDate);
    void setServiceProvider(const QString &serviceProvider);
    void setDescription(const QString &description);

    void setDataManager(DataManager* dataManager);


signals:
    void amountChanged(qreal amount);
    void purposeChanged(int purpose);
    void transactionDateChanged(const QDate &transactionDate);
    void serviceProviderChanged(const QString &serviceProvider);
    void descriptionChanged(const QString &description);
    void changed();

    void dataManagerChanged(DataManager* dataManager);

    void idChanged(int id);

private:
    int m_id;
    qreal m_amount;
    int m_purpose;
    QDate m_transactionDate;
    QString m_serviceProvider;
    QString m_description;
    DataManager* m_dataManager;

    void updateFields();
};

#endif // RECORD_H
