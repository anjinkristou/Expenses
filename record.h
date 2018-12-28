#ifndef RECORD_H
#define RECORD_H

#include <QObject>
#include <QDate>

class Record : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int purpose READ purpose WRITE setPurpose NOTIFY purposeChanged)
    Q_PROPERTY(qreal amount READ amount WRITE setAmount NOTIFY amountChanged)
    Q_PROPERTY(QDate transactionDate READ transactionDate WRITE setTransactionDate NOTIFY transactionDateChanged)
    Q_PROPERTY(QString serviceProvider READ serviceProvider WRITE setServiceProvider NOTIFY serviceProviderChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    explicit Record(QObject *parent = nullptr);

    inline qreal amount() const { return m_amount; }
    inline int purpose() const { return m_purpose; }
    inline QDate transactionDate() const  { return m_transactionDate; }
    inline QString serviceProvider() const  { return m_serviceProvider; }
    inline QString description() const { return m_description; }

public slots:
    void setAmount(qreal amount);
    void setPurpose(int purpose);
    void setTransactionDate(const QDate &transactionDate);
    void setServiceProvider(const QString &serviceProvider);
    void setDescription(const QString &description);

signals:
    void amountChanged(qreal amount);
    void purposeChanged(int purpose);
    void transactionDateChanged(const QDate &transactionDate);
    void serviceProviderChanged(const QString &serviceProvider);
    void descriptionChanged(const QString &description);

private:
    qreal m_amount;
    int m_purpose;
    QDate m_transactionDate;
    QString m_serviceProvider;
    QString m_description;
};

#endif // RECORD_H
