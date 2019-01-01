#include "record.h"

#include <QVariantMap>

#include "datamanager.h"

Record::Record(QObject *parent)
    : QObject(parent)
    , m_id(-1)
    , m_amount(0)
    , m_purpose(0)
    , m_transactionDate(QDate::currentDate())
    , m_serviceProvider("No peovider")
    , m_description("No description")
    , m_dataManager(nullptr)
{
    connect(this, &Record::amountChanged, this, &Record::changed);
    connect(this, &Record::purposeChanged, this, &Record::changed);
}

DataManager *Record::dataManager() const
{
    return m_dataManager;
}

void Record::setAmount(qreal amount)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_amount, amount))
        return;

    m_amount = amount;

    if(m_dataManager){
        m_dataManager->setField(tableName(), m_id, "amount", m_amount);
    }

    emit amountChanged(m_amount);
}

void Record::setPurpose(int purpose)
{
    if (m_purpose == purpose)
        return;

    m_purpose = purpose;
    emit purposeChanged(m_purpose);
}

void Record::setTransactionDate(const QDate &transactionDate)
{
    if (m_transactionDate == transactionDate)
        return;

    m_transactionDate = transactionDate;
    emit transactionDateChanged(m_transactionDate);
}

void Record::setServiceProvider(const QString &serviceProvider)
{
    if (m_serviceProvider == serviceProvider)
        return;

    m_serviceProvider = serviceProvider;
    emit serviceProviderChanged(m_serviceProvider);
}

void Record::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged(m_description);
}

void Record::setDataManager(DataManager *dataManager)
{
    if (m_dataManager == dataManager)
        return;

    m_dataManager = dataManager;

    updateFields();

    emit dataManagerChanged(m_dataManager);
}

void Record::updateFields()
{
    if(m_dataManager){
        QStringList fileds;
        fileds << "amount";
        QVariantMap props = m_dataManager->fields(tableName(), m_id, fileds);

        m_amount = props["amount"].toReal();
    }
}

void Record::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}
