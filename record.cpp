#include "record.h"

Record::Record(QObject *parent)
    : QObject(parent)
    , m_amount(0)
    , m_purpose(0)
    , m_transactionDate(QDate::currentDate())
    , m_serviceProvider("No peovider")
    , m_description("No description")
{

}

void Record::setAmount(qreal amount)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_amount, amount))
        return;

    m_amount = amount;
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
